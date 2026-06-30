# ESP32 Air Quality Monitoring System with LoRa

## Overview

This project uses two ESP32 boards.

-   **Transmitter ESP32**
    -   MICS-6814 Gas Sensor
    -   GP2Y1010AU0F PM2.5 Sensor
    -   BMP280 Temperature & Pressure Sensor
    -   NEO-6M GPS
    -   SX1278 (Ra-02) LoRa Module
-   **Receiver ESP32**
    -   SX1278 (Ra-02) LoRa Module
    -   Wi-Fi
    -   Firebase Realtime Database

The transmitter reads all sensors and sends one LoRa packet every 5
seconds.

Example payload:

``` text
LAT:17.385044,LON:78.486671,TEMP:29.54,PRESS:1008.63,PM25:15.62,CO:58.00,NH3:36.00,NO2:34.00
```

------------------------------------------------------------------------

# Transmitter Pin Connections

## MICS-6814

  Sensor Pin   ESP32
  ------------ --------
  CO           GPIO34
  NH3          GPIO35
  NO2          GPIO32
  VCC          5V
  GND          GND

## GP2Y1010AU0F

  Sensor Pin    ESP32
  ------------- --------
  Vo            GPIO36
  LED Control   GPIO2
  VCC           5V
  GND           GND

## BMP280

  Sensor Pin   ESP32
  ------------ --------
  SDA          GPIO21
  SCL          GPIO22
  VIN          3.3V
  GND          GND

## NEO-6M GPS

  GPS Pin   ESP32
  --------- -----------
  TX        GPIO16
  RX        GPIO17
  VCC       3.3V/5V\*
  GND       GND

(\*Depending on module.)

## LoRa SX1278 (Ra-02)

  LoRa Pin   ESP32
  ---------- -----------
  NSS        GPIO5
  SCK        GPIO18
  MISO       GPIO19
  MOSI       GPIO23
  RESET      GPIO14
  DIO0       GPIO26
  VCC        3.3V ONLY
  GND        GND

------------------------------------------------------------------------

# Receiver Pin Connections

## LoRa SX1278

Same connections as transmitter.

  LoRa Pin   ESP32
  ---------- -----------
  NSS        GPIO5
  SCK        GPIO18
  MISO       GPIO19
  MOSI       GPIO23
  RESET      GPIO14
  DIO0       GPIO26
  VCC        3.3V ONLY
  GND        GND

------------------------------------------------------------------------

# Required Arduino Libraries

-   LoRa (Sandeep Mistry)
-   TinyGPS++
-   Adafruit BMP280
-   Adafruit Unified Sensor
-   ArduinoJson
-   WiFi
-   HTTPClient

------------------------------------------------------------------------

# LoRa Packet Format

``` text
LAT:<latitude>,
LON:<longitude>,
TEMP:<temperature>,
PRESS:<pressure>,
PM25:<pm2.5>,
CO:<co>,
NH3:<nh3>,
NO2:<no2>
```

Example

``` text
LAT:17.385044,LON:78.486671,TEMP:29.54,PRESS:1008.63,PM25:15.62,CO:58.00,NH3:36.00,NO2:34.00
```

------------------------------------------------------------------------

# Firebase Structure

``` json
{
  "CO": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 58.0
  },
  "NH3": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 36.0
  },
  "NO": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 34.0
  },
  "PM2": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 15.62
  },
  "Temperature": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 29.54
  },
  "Pressure": {
    "Location": {
      "lat": 17.385044,
      "long": 78.486671
    },
    "value": 1008.63
  },
  "Location": {
    "lat": 17.385044,
    "long": 78.486671
  }
}
```

------------------------------------------------------------------------

# Sensor Outputs

  Sensor        Unit
  ------------- -----------------
  CO            µg/m³ (mapped)
  NH3           µg/m³ (mapped)
  NO2           µg/m³ (mapped)
  PM2.5         µg/m³
  Temperature   °C
  Pressure      hPa
  Latitude      Decimal Degrees
  Longitude     Decimal Degrees

------------------------------------------------------------------------

# Communication Flow

    MICS-6814
    GP2Y1010AU0F
    BMP280
    NEO-6M
          │
          ▼
    ESP32 Transmitter
          │
          ▼
    SX1278 LoRa
    ~~~~~~~~~~~~~~
    SX1278 LoRa
          │
          ▼
    ESP32 Receiver
          │
          ▼
    Wi-Fi
          │
          ▼
    Firebase Realtime Database
