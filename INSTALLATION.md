# Installation & Setup Guide

Follow this step-by-step pipeline to configure, flash, and deploy the firmware onto the Transmitter and Receiver ESP32 nodes.

## 1. Arduino IDE Setup
1. Download and install the latest [Arduino IDE](https://www.arduino.cc/en/software).
2. Go to **File -> Preferences**.
3. Add the following URL to the *Additional Boards Manager URLs* field:
   `https://dl.espressif.com/dl/package_esp32_index.json`
4. Go to **Tools -> Board -> Boards Manager**, search for `esp32`, and install the package by Espressif Systems.

## 2. Required Libraries
Install the following libraries via the **Library Manager** (Sketch -> Include Library -> Manage Libraries):
* `LoRa` by Sandeep Mistry
* `Adafruit BMP280 Library` by Adafruit
* `Adafruit Unified Sensor` by Adafruit
* `TinyGPSPlus` by Mikal Hart
* `Firebase ESP32 Client` by Mobizt

## 3. Configuration & Secrets Injection
Before flashing, you must update the firmware files with your local and cloud credentials.

### Receiver Node (Wi-Fi & Firebase)
Open the Receiver sketch and locate the configuration section. Update the following constants:

```cpp
// Wi-Fi Credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Firebase Configuration
#define FIREBASE_HOST "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret-or-auth-token"
```

## 4. Flashing Instructions

### Flashing the Transmitter
1. Connect the **Transmitter ESP32** to your computer via USB.
2. In Arduino IDE, select **Tools -> Board -> ESP32 Dev Module**.
3. Select the correct **COM Port**.
4. Open the Transmitter sketch.
5. Click **Upload**. (If it fails to connect, hold the `BOOT` button on the ESP32 when the console displays "Connecting...").

### Flashing the Receiver
1. Connect the **Receiver ESP32** to your computer.
2. Select the correct **COM Port**.
3. Open the Receiver sketch.
4. Click **Upload**.

## 5. System Verification
To ensure everything is working correctly:
1. Open the **Serial Monitor** (set baud rate to `115200`).
2. **On the Transmitter:** You should see successful sensor initialization messages followed by the payload string being transmitted (e.g., `Sending packet: LAT:17.38...`).
3. **On the Receiver:** You should see successful Wi-Fi connection, LoRa initialization, and incoming packet parsed logs, ending with `Data pushed to Firebase successfully`.
4. Log into your **Firebase Console** and verify that the data nodes are updating in real time.
