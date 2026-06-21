#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ----- LoRa Configuration -----
#define LORA_SS      5    // Chip select pin
#define LORA_RST     14   // Reset pin
#define LORA_DIO0    26   // DIO0 pin
#define LORA_FREQUENCY 433E6  // 433 MHz

// ----- Wi-Fi Configuration -----
const char* ssid = "your-SSID";         // Replace with your WiFi network name
const char* password = "your-PASSWORD"; // Replace with your WiFi password

// ----- Firebase Configuration -----
// For REST API access, use your Firebase Realtime Database URL in REST format:
const char* firebaseHost = "team-9-801be-default-rtdb.firebaseio.com";

// ----- Function to Send Data to Firebase -----
void sendDataToFirebase(String dataMessage) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Construct the URL: data will be sent to the "/data" node
    String url = String("https://") + firebaseHost + "/data.json";
    
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Create a JSON payload (you can modify this format as needed)
    String jsonPayload = "{\"data\":\"" + dataMessage + "\"}";
    Serial.print("Sending payload: ");
    Serial.println(jsonPayload);

    // Send an HTTP PUT request to update the data at the "/data" node
    int httpResponseCode = http.PUT(jsonPayload);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error sending data, code: ");
      Serial.println(httpResponseCode);
    }
    http.end();  // Free resources
  } else {
    Serial.println("WiFi not connected");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LoRa Receiver with Firebase");

  // ----- Connect to Wi-Fi -----
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());

  // ----- Initialize LoRa -----
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("LoRa init failed. Check wiring.");
    while (true);
  }
  Serial.println("LoRa Initialized");
}

void loop() {
  // Check if a LoRa packet is received
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.print("Received LoRa packet: ");
    Serial.println(incoming);

    // Send the received message to Firebase
    sendDataToFirebase(incoming);
    
    // Delay to avoid flooding Firebase with too many requests
    delay(5000);
  }
}
