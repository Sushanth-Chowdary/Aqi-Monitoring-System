# ESP32-Based Real-Time Air Quality Monitoring System

## Table of Contents

1.  Project Overview
2.  Objectives
3.  System Architecture
4.  Hardware Components
5.  ESP32 Pin Connections
6.  Software Stack
7.  Data Flow
8.  LoRa Packet Format
9.  Firebase Database Structure
10. Sensor Outputs
11. Required Libraries
12. Setup
13. Future Improvements

# Project Overview

This project implements a low-cost, real-time air quality monitoring
system using two ESP32 boards connected through SX1278 (Ra-02) LoRa
modules.

The transmitter collects environmental data from multiple sensors,
attaches GPS coordinates, and transmits the measurements over LoRa. The
receiver uploads the decoded data to Firebase Realtime Database over
Wi-Fi, enabling live monitoring in a Flutter application.

# Objectives

-   Monitor CO, NH3, NO2 and PM2.5.
-   Measure temperature and atmospheric pressure.
-   Tag every reading with GPS coordinates.
-   Transmit measurements wirelessly using LoRa.
-   Store measurements in Firebase Realtime Database.
-   Support real-time visualization in a Flutter mobile application.

# System Architecture

``` text
MICS-6814
GP2Y1010AU0F
BMP280
NEO-6M GPS
      │
      ▼
ESP32 Transmitter
      │
 SX1278 LoRa (433 MHz)
~~~~~~~~ Wireless ~~~~~~~~
 SX1278 LoRa (433 MHz)
      │
ESP32 Receiver
      │
      ▼
Wi-Fi
      │
      ▼
Firebase Realtime Database
      │
      ▼
Flutter Mobile App
```

# Hardware Components

  Component      Purpose
  -------------- -----------------------------------
  ESP32 (2x)     Transmitter and receiver
  MICS-6814      CO, NH3 and NO2 sensing
  GP2Y1010AU0F   PM2.5 sensing
  BMP280         Temperature and pressure
  NEO-6M GPS     Latitude and longitude
  SX1278 Ra-02   Long-range wireless communication

# ESP32 Pin Connections

## Transmitter

### MICS-6814

  Signal   ESP32
  -------- --------
  CO       GPIO34
  NH3      GPIO35
  NO2      GPIO32
  VCC      5V
  GND      GND

### GP2Y1010AU0F

  Signal   ESP32
  -------- --------
  Vo       GPIO36
  LED      GPIO2
  VCC      5V
  GND      GND

### BMP280

  Signal   ESP32
  -------- --------
  SDA      GPIO21
  SCL      GPIO22
  VIN      3.3V
  GND      GND

### NEO-6M GPS

  Signal   ESP32
  -------- ---------
  TX       GPIO16
  RX       GPIO17
  VCC      3.3V/5V
  GND      GND

### SX1278 LoRa

  Signal   ESP32
  -------- --------
  NSS      GPIO5
  SCK      GPIO18
  MISO     GPIO19
  MOSI     GPIO23
  RESET    GPIO14
  DIO0     GPIO26
  VCC      3.3V
  GND      GND

## Receiver

Uses identical LoRa wiring plus Wi-Fi connectivity.

# Software Stack

-   Arduino IDE
-   ESP32 Core
-   LoRa Library
-   TinyGPS++
-   Adafruit BMP280
-   ArduinoJson
-   WiFi
-   HTTPClient
-   Firebase Realtime Database
-   Flutter

# Data Flow

1.  Read all sensors.
2.  Read GPS location.
3.  Read BMP280 temperature and pressure.
4.  Package values into a LoRa packet.
5.  Transmit via SX1278.
6.  Receiver decodes the packet.
7.  Receiver uploads JSON to Firebase.
8.  Flutter app displays live values.

# LoRa Packet Format

``` text
LAT:17.385044,LON:78.486671,TEMP:29.54,PRESS:1008.63,PM25:15.62,CO:58.00,NH3:36.00,NO2:34.00
```

# Firebase JSON Structure

``` json
{
  "CO":{"Location":{"lat":17.385044,"long":78.486671},"value":58.0},
  "NH3":{"Location":{"lat":17.385044,"long":78.486671},"value":36.0},
  "NO":{"Location":{"lat":17.385044,"long":78.486671},"value":34.0},
  "PM2":{"Location":{"lat":17.385044,"long":78.486671},"value":15.62},
  "Temperature":{"Location":{"lat":17.385044,"long":78.486671},"value":29.54},
  "Pressure":{"Location":{"lat":17.385044,"long":78.486671},"value":1008.63},
  "Location":{"lat":17.385044,"long":78.486671}
}
```

# Sensor Outputs

  Parameter     Unit
  ------------- -----------------
  CO            µg/m³
  NH3           µg/m³
  NO2           µg/m³
  PM2.5         µg/m³
  Temperature   °C
  Pressure      hPa
  Latitude      Decimal degrees
  Longitude     Decimal degrees

# Setup

1.  Upload transmitter firmware.
2.  Upload receiver firmware.
3.  Configure Wi-Fi credentials.
4.  Configure Firebase URL.
5.  Power both ESP32 boards.
6.  Verify LoRa packets.
7.  Observe live updates in Firebase and Flutter.

# Future Improvements

-   Timestamp every measurement.
-   Historical data visualization.
-   AQI computation using CPCB breakpoints.
-   Additional pollutants (PM10, SO2, O3).
-   Battery-powered remote nodes.
-   Multi-node LoRa network.
