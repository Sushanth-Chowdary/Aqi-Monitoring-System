# Air-Quality-Monitoring-System

## Project Overview
The Air-Quality-Monitoring-System is an advanced IoT-based solution designed to track and analyze air quality metrics in real time. Utilizing a dual ESP32 setup (Transmitter and Receiver) communicating over a 433 MHz LoRa network, this system accurately measures the concentration of harmful gases, particulate matter, and environmental factors, alongside precise GPS geolocation. The aggregated data is seamlessly synchronized with Firebase Realtime Database for real-time visualization and alerting via a companion Flutter mobile application.
<img width="4000" height="3000" alt="Sender" src="https://github.com/user-attachments/assets/d2bec1b0-6fbe-4907-9f8d-3ea817135730" />
<img width="4000" height="3000" alt="Reciver" src="https://github.com/user-attachments/assets/191706b1-a780-48b7-b32e-08a7cbcd7fa3" />

## Core Features
* **Real-Time Air Quality Tracking:** Continuous monitoring of CO, NH3, NO2, and PM2.5 levels.
* **Environmental Sensing:** Accurate temperature and barometric pressure readings.
* **GPS Geolocation:** Live spatial mapping of the sensor node.
* **Long-Range Communication:** LoRa transceiver integration for robust data transmission over long distances without reliance on Wi-Fi at the edge.
* **Cloud Integration:** Firebase Realtime Database backend for persistent storage and real-time syncing.
* **Mobile Application:** Dedicated Flutter application for live monitoring, alerts, and historical data visualization.

## Directory Tree
```text
Air-Quality-Monitoring-System/
├── README.md
├── PIN_CONNECTIONS.md
├── SYSTEM_ARCHITECTURE.md
├── FIREBASE_STRUCTURE.md
├── INSTALLATION.md
└── TROUBLESHOOTING_AND_FUTURE_SCOPE.md
```

## Bill of Materials (BOM)

| Component | Description | Quantity |
| :--- | :--- | :--- |
| **ESP32** | Microcontroller with built-in Wi-Fi & Bluetooth | 2 |
| **MICS-6814** | Multi-gas sensor (CO, NH3, NO2) | 1 |
| **GP2Y1010AU0F** | Optical dust/particulate matter (PM2.5) sensor | 1 |
| **BMP280** | Temperature and barometric pressure sensor | 1 |
| **NEO-6M** | GPS module for geolocation tracking | 1 |
| **SX1278 RA-02** | LoRa Transceiver Module (433 MHz) | 2 |

## Sensor Specifications

| Sensor | Parameter Measured | Typical Range | Unit |
| :--- | :--- | :--- | :--- |
| **MICS-6814** | Carbon Monoxide (CO) | 1 – 1000 | ppm |
| **MICS-6814** | Ammonia (NH3) | 1 – 500 | ppm |
| **MICS-6814** | Nitrogen Dioxide (NO2) | 0.05 – 10 | ppm |
| **GP2Y1010AU0F**| Particulate Matter (PM2.5)| 0 – 500 | µg/m³ |
| **BMP280** | Temperature | -40 to +85 | °C |
| **BMP280** | Barometric Pressure | 300 to 1100 | hPa |
| **NEO-6M** | Location | Global | Lat/Lon |

## Software Workflow & Flutter Application
### High-Level Workflow
1. **Data Acquisition:** The Transmitter ESP32 collects raw analog and digital signals from the connected sensors and GPS module.
2. **Data Transmission:** The readings are formatted into a structured payload and transmitted over LoRa (433 MHz) to the Receiver node.
3. **Cloud Synchronization:** The Receiver ESP32 parses the incoming LoRa payload and uploads the structured data directly to Firebase Realtime Database over a local Wi-Fi connection.
4. **Client Visualization:** The Flutter application listens to Firebase streams and updates the UI in real time.

### Mobile Application (Flutter)
> **Note:** The source code for the companion Flutter application is maintained in a separate repository to modularize the codebase and manage size effectively.

**Key App Features:**
* **Real-Time Monitoring:** Live dashboard displaying current AQI metrics and environmental conditions.
* **Live GPS Tracking:** Map integration pinpointing the exact location of the sensor node.
* **Firebase Integration:** Seamless real-time data synchronization.
* **AQI Visualization:** Color-coded indicators representing overall air quality safety levels.
* **Historical Graphs:** Interactive charts for analyzing trends over time.
* **Alerts:** Push notifications and visual warnings when hazardous gas or PM2.5 thresholds are breached.
