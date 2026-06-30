# ESP32 Air Quality Monitoring System

## Documentation

This repository contains the firmware and documentation for a real-time
air quality monitoring system using ESP32, LoRa, GPS, BMP280,
GP2Y1010AU0F and MICS-6814.

## Hardware

See the dedicated hardware wiring guide:

**➡️ [PIN_CONNECTIONS.md](PIN_CONNECTIONS.md)**

This document contains all transmitter and receiver wiring tables.

## Communication

Transmitter → SX1278 LoRa → Receiver → Wi-Fi → Firebase Realtime
Database → Flutter App

## LoRa Payload

``` text
LAT:17.385044,LON:78.486671,TEMP:29.54,PRESS:1008.63,PM25:15.62,CO:58.00,NH3:36.00,NO2:34.00
```

## Firebase Structure

Each sensor is stored with its own Location object and value:

-   CO
-   NH3
-   NO
-   PM2
-   Temperature
-   Pressure
-   Common Location

Refer to the project report for implementation details.

## Software

-   Arduino IDE
-   ESP32 Core
-   LoRa
-   TinyGPS++
-   Adafruit BMP280
-   ArduinoJson
-   WiFi
-   HTTPClient

## Setup

1.  Wire the hardware using **PIN_CONNECTIONS.md**.
2.  Upload the transmitter sketch.
3.  Upload the receiver sketch.
4.  Configure Wi-Fi and Firebase.
5.  Power both ESP32 boards.
6.  Verify LoRa communication.
7.  Check Firebase updates.
