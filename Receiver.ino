#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <LoRa.h>

//=========================
// WiFi
//=========================
const char* ssid = "IITT";
const char* password = "user@123";

// Firebase URL
const String firebase_url =
"https://ecology-55107-default-rtdb.asia-southeast1.firebasedatabase.app/.json";

//=========================
// LoRa Pins
//=========================
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  26

//=========================
// WiFi Connection
//=========================
void connectWiFi()
{
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
}

//=========================
// Upload Firebase
//=========================
void sendDataToFirebase(float latitude,
                        float longitude,
                        float co,
                        float nh3,
                        float no2,
                        float pm25,
                        float temp,
                        float pressure)
{

  if(WiFi.status()!=WL_CONNECTED)
  {
    connectWiFi();
  }

  HTTPClient http;

  http.begin(firebase_url);
  http.addHeader("Content-Type","application/json");

  DynamicJsonDocument doc(2048);

  //================ CO =================

  JsonObject CO = doc.createNestedObject("CO");

  JsonObject COLOC = CO.createNestedObject("Location");

  COLOC["lat"]=latitude;
  COLOC["long"]=longitude;

  CO["value"]=co;

  //================ NH3 =================

  JsonObject NH3 = doc.createNestedObject("NH3");

  JsonObject NH3LOC = NH3.createNestedObject("Location");

  NH3LOC["lat"]=latitude;
  NH3LOC["long"]=longitude;

  NH3["value"]=nh3;

  //================ NO =================

  JsonObject NO = doc.createNestedObject("NO");

  JsonObject NOLOC = NO.createNestedObject("Location");

  NOLOC["lat"]=latitude;
  NOLOC["long"]=longitude;

  NO["value"]=no2;

  //================ PM2 =================

  JsonObject PM2 = doc.createNestedObject("PM2");

  JsonObject PMLOC = PM2.createNestedObject("Location");

  PMLOC["lat"]=latitude;
  PMLOC["long"]=longitude;

  PM2["value"]=pm25;

  //================ Temperature =================

  JsonObject TEMP = doc.createNestedObject("Temperature");

  JsonObject TEMPLOC = TEMP.createNestedObject("Location");

  TEMPLOC["lat"]=latitude;
  TEMPLOC["long"]=longitude;

  TEMP["value"]=temp;

  //================ Pressure =================

  JsonObject PRESS = doc.createNestedObject("Pressure");

  JsonObject PRESSLOC = PRESS.createNestedObject("Location");

  PRESSLOC["lat"]=latitude;
  PRESSLOC["long"]=longitude;

  PRESS["value"]=pressure;

  //================ Common Location =================

  JsonObject LOC = doc.createNestedObject("Location");

  LOC["lat"]=latitude;
  LOC["long"]=longitude;

  String json;

  serializeJsonPretty(doc,json);

  Serial.println();
  Serial.println("Uploading to Firebase");
  Serial.println(json);

  int code=http.PUT(json);

  if(code>0)
  {
    Serial.print("HTTP Response : ");
    Serial.println(code);

    Serial.println(http.getString());
  }
  else
  {
    Serial.print("Firebase Error : ");
    Serial.println(http.errorToString(code));
  }

  http.end();

}

//=========================
// Setup
//=========================
void setup()
{

  Serial.begin(115200);

  connectWiFi();

  SPI.begin(LORA_SCK,
            LORA_MISO,
            LORA_MOSI,
            LORA_SS);

  LoRa.setPins(LORA_SS,
               LORA_RST,
               LORA_DIO0);

  if(!LoRa.begin(433E6))
  {
    Serial.println("LoRa Init Failed");

    while(1);
  }

  Serial.println("LoRa Receiver Ready");

}

//=========================
// Loop
//=========================
void loop()
{

  int packetSize=LoRa.parsePacket();

  if(packetSize)
  {

    String received="";

    while(LoRa.available())
    {
      received+=(char)LoRa.read();
    }

    Serial.println();
    Serial.println("=========== PACKET RECEIVED ===========");
    Serial.println(received);

    Serial.print("RSSI : ");
    Serial.println(LoRa.packetRssi());

    float lat=0;
    float lon=0;
    float temp=0;
    float pressure=0;
    float pm25=0;
    float co=0;
    float nh3=0;
    float no2=0;

    int matched = sscanf(received.c_str(),
      "LAT:%f,LON:%f,TEMP:%f,PRESS:%f,PM25:%f,CO:%f,NH3:%f,NO2:%f",
      &lat,
      &lon,
      &temp,
      &pressure,
      &pm25,
      &co,
      &nh3,
      &no2);

    if(matched!=8)
    {
      Serial.println("Packet Parse Failed!");
      return;
    }

    Serial.println();
    Serial.println("Decoded Values");

    Serial.print("Latitude : ");
    Serial.println(lat,6);

    Serial.print("Longitude : ");
    Serial.println(lon,6);

    Serial.print("Temperature : ");
    Serial.println(temp);

    Serial.print("Pressure : ");
    Serial.println(pressure);

    Serial.print("PM2.5 : ");
    Serial.println(pm25);

    Serial.print("CO : ");
    Serial.println(co);

    Serial.print("NH3 : ");
    Serial.println(nh3);

    Serial.print("NO2 : ");
    Serial.println(no2);

    sendDataToFirebase(lat,
                       lon,
                       co,
                       nh3,
                       no2,
                       pm25,
                       temp,
                       pressure);

    Serial.println("=======================================");
  }

}
