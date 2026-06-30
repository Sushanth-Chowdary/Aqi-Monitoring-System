#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <LoRa.h>

// WiFi credentials
const char* ssid = "IITT";
const char* password = "user@123";

// Firebase Realtime Database URL
const String firebase_url = "https://ecology-55107-default-rtdb.asia-southeast1.firebasedatabase.app/";

// LoRa pins
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendDataToFirebase(float latitude, float longitude, float co, float nh3, float no2, float pm25, float temp, float pressure) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = firebase_url + "/.json";

    DynamicJsonDocument jsonDoc(1024);
    JsonObject root = jsonDoc.to<JsonObject>();

    // CO
    JsonObject coData = root.createNestedObject("CO");
    JsonObject coLocation = coData.createNestedObject("Location");
    coLocation["lat"] = String(latitude, 6) + " N";
    coLocation["long"] = String(longitude, 6) + " E";
    coData["value"] = round(co);

    // NH3
    JsonObject nh3Data = root.createNestedObject("NH3");
    JsonObject nh3Location = nh3Data.createNestedObject("Location");
    nh3Location["lat"] = String(latitude, 6) + " N";
    nh3Location["long"] = String(longitude, 6) + " E";
    nh3Data["value"] = round(nh3);

    // NO2 → NO
    JsonObject no2Data = root.createNestedObject("NO");
    JsonObject no2Location = no2Data.createNestedObject("Location");
    no2Location["lat"] = String(latitude, 6) + " N";
    no2Location["long"] = String(longitude, 6) + " E";
    no2Data["value"] = round(no2);

    // PM2 (dust)
    JsonObject pm25Data = root.createNestedObject("PM2");
    JsonObject pm25Location = pm25Data.createNestedObject("Location");
    pm25Location["lat"] = String(latitude, 6) + " N";
    pm25Location["long"] = String(longitude, 6) + " E";
    pm25Data["value"] = round(pm25);

    // Temperature
    JsonObject tempData = root.createNestedObject("Temperature");
    JsonObject tempLocation = tempData.createNestedObject("Location");
    tempLocation["lat"] = String(latitude, 6) + " N";
    tempLocation["long"] = String(longitude, 6) + " E";
    tempData["value"] = round(temp);

    // Pressure
    JsonObject pressureData = root.createNestedObject("Pressure");
    JsonObject pressureLocation = pressureData.createNestedObject("Location");
    pressureLocation["lat"] = String(latitude, 6) + " N";
    pressureLocation["long"] = String(longitude, 6) + " E";
    pressureData["value"] = round(pressure);

    // Common Location
    JsonObject commonLocation = root.createNestedObject("Location");
    commonLocation["lat"] = String(latitude, 6) + " N";
    commonLocation["long"] = String(longitude, 6) + " E";

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.PUT(jsonData);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error on sending PUT: ");
      Serial.println(http.errorToString(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void setup() {
  Serial.begin(9600);
  connectWiFi();

  // LoRa setup
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }

    Serial.println("Received: " + received);

    // Example: CO:12.32,NH3:5.11,NO2:6.78,Dust:35.60,Temp:27.12,Pres:1008.55,Lat:12.971599,Lon:77.594566
    float co = 0, nh3 = 0, no2 = 0, pm25 = 0, temp = 0, pressure = 0, lat = 0, lon = 0;
    sscanf(received.c_str(), "CO:%f,NH3:%f,NO2:%f,Dust:%f,Temp:%f,Pres:%f,Lat:%f,Lon:%f", 
           &co, &nh3, &no2, &pm25, &temp, &pressure, &lat, &lon);

    // Send to Firebase
    sendDataToFirebase(lat, lon, co, nh3, no2, pm25, temp, pressure);
  }
}
