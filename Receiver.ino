// Receiver.ino
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <LoRa.h>

const char* ssid="IITT";
const char* password="user@123";
const String firebase_url="https://ecology-55107-default-rtdb.asia-southeast1.firebasedatabase.app/";

void connectWiFi(){
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED) delay(500);
}

void sendDataToFirebase(float latitude,float longitude,float co,float nh3,float no2,float pm25,float temp,float pressure){
  HTTPClient http;
  DynamicJsonDocument doc(1024);
  auto root=doc.to<JsonObject>();
  root["CO"]["value"]=round(co);
  root["NH3"]["value"]=round(nh3);
  root["NO"]["value"]=round(no2);
  root["PM2"]["value"]=round(pm25);
  root["Temperature"]["value"]=round(temp);
  root["Pressure"]["value"]=round(pressure);
  root["Location"]["lat"]=String(latitude,6)+" N";
  root["Location"]["long"]=String(longitude,6)+" E";
  String body;
  serializeJson(doc,body);
  http.begin(firebase_url+"/.json");
  http.addHeader("Content-Type","application/json");
  http.PUT(body);
  http.end();
}

void setup(){
 Serial.begin(9600);
 connectWiFi();
 LoRa.setPins(5,14,26);
 LoRa.begin(433E6);
}

void loop(){
 int p=LoRa.parsePacket();
 if(p){
   String s="";
   while(LoRa.available()) s+=(char)LoRa.read();
   Serial.println(s);
   float co,nh3,no2,dust,temp,pres,lat,lon;
   sscanf(s.c_str(),"CO:%f,NH3:%f,NO2:%f,Dust:%f,Temp:%f,Pres:%f,Lat:%f,Lon:%f",
          &co,&nh3,&no2,&dust,&temp,&pres,&lat,&lon);
   sendDataToFirebase(lat,lon,co,nh3,no2,dust,temp,pres);
 }
}
