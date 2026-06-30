// ESP32 Air Quality LoRa Transmitter
// Hardware:
// MICS-6814, GP2Y1010AU0F, BMP280, NEO-6M GPS, SX1278 LoRa

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>

Adafruit_BMP280 bmp;
TinyGPSPlus gps;

// GP2Y1010
int measurePin = 36;
int ledPower = 2;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

// MICS-6814
#define MICS_CO_PIN 34
#define MICS_NH3_PIN 35
#define MICS_NO2_PIN 32

// GPS
HardwareSerial GPSSerial(1);
#define GPS_RX 16
#define GPS_TX 17

// BMP280
#define SDA_PIN 21
#define SCL_PIN 22

// LoRa
#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26
#define LORA_BAND 433E6

void setup() {
  Serial.begin(9600);

  pinMode(ledPower, OUTPUT);
  pinMode(MICS_CO_PIN, INPUT);
  pinMode(MICS_NH3_PIN, INPUT);
  pinMode(MICS_NO2_PIN, INPUT);

  Wire.begin(SDA_PIN,SCL_PIN);
  if(!bmp.begin(0x76)){
    Serial.println("BMP280 not found!");
  }

  GPSSerial.begin(9600,SERIAL_8N1,GPS_RX,GPS_TX);

  SPI.begin(LORA_SCK,LORA_MISO,LORA_MOSI,LORA_SS);
  LoRa.setPins(LORA_SS,LORA_RST,LORA_DIO0);

  if(!LoRa.begin(LORA_BAND)){
    Serial.println("LoRa init failed");
    while(1);
  }

  Serial.println("LoRa Transmitter Started");
}

void loop() {

  while(GPSSerial.available()){
    gps.encode(GPSSerial.read());
  }

  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  float voMeasured=analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  float calcVoltage=voMeasured*(5.0/1024.0);
  float dustDensity=170*calcVoltage-0.1;
  if(dustDensity<0)dustDensity=0;

  int rawCO=analogRead(MICS_CO_PIN);
  int rawNH3=analogRead(MICS_NH3_PIN);
  int rawNO2=analogRead(MICS_NO2_PIN);

  float co=map(rawCO,4095,0,0,100);
  float nh3=map(rawNH3,4095,0,0,100);
  float no2=map(rawNO2,4095,0,0,100);

  float temperature=bmp.readTemperature();
  float pressure=bmp.readPressure()/100.0;

  double lat=0,lon=0;
  if(gps.location.isValid()){
    lat=gps.location.lat();
    lon=gps.location.lng();
  }

  String payload=
  "LAT:"+String(lat,6)+
  ",LON:"+String(lon,6)+
  ",TEMP:"+String(temperature,2)+
  ",PRESS:"+String(pressure,2)+
  ",PM25:"+String(dustDensity,2)+
  ",CO:"+String(co,2)+
  ",NH3:"+String(nh3,2)+
  ",NO2:"+String(no2,2);

  Serial.println(payload);

  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();

  delay(5000);
}
