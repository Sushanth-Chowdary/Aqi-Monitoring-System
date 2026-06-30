# Pin Connections & Wiring Mapping

This document provides a comprehensive wiring guide for the Transmitter Node (ESP32). It outlines the pin assignments for all sensors and communication modules.

## Transmitter Node (ESP32) Wiring

### 1. Analog Sensors (MICS-6814 & GP2Y1010AU0F)
The multi-gas sensor and the dust sensor output analog voltages that require the ESP32's internal ADC.

| Sensor Pin | ESP32 GPIO | Description |
| :--- | :--- | :--- |
| **MICS-6814 CO** | GPIO34 | Carbon Monoxide analog output |
| **MICS-6814 NH3** | GPIO35 | Ammonia analog output |
| **MICS-6814 NO2** | GPIO32 | Nitrogen Dioxide analog output |
| **GP2Y A-OUT** | GPIO36 (VP)| PM2.5 analog voltage output |
| **GP2Y I-LED** | GPIO33 | LED trigger for dust sampling |
| **VCC / GND** | 3.3V / 5V / GND| Power supply as required per module |

### 2. I2C Bus (BMP280)
The BMP280 temperature and pressure sensor communicates via the standard I2C protocol.

| BMP280 Pin | ESP32 GPIO | Description |
| :--- | :--- | :--- |
| **SDA** | GPIO21 | I2C Serial Data |
| **SCL** | GPIO22 | I2C Serial Clock |
| **VCC** | 3.3V | Power Supply |
| **GND** | GND | Ground |

### 3. Hardware UART (NEO-6M GPS)
The NEO-6M GPS module streams NMEA sentences over a serial interface.

| NEO-6M Pin | ESP32 GPIO | Description |
| :--- | :--- | :--- |
| **TX** | GPIO16 (RX2) | Transmits NMEA data to ESP32 |
| **RX** | GPIO17 (TX2) | Receives commands (optional) |
| **VCC** | 3.3V / 5V | Power Supply |
| **GND** | GND | Ground |

### 4. SPI Bus (SX1278 RA-02 LoRa)
The LoRa transceiver requires a high-speed SPI bus along with dedicated control pins for synchronization.

| SX1278 Pin | ESP32 GPIO | Description |
| :--- | :--- | :--- |
| **SCK** | GPIO18 | SPI Clock |
| **MISO** | GPIO19 | SPI Master In Slave Out |
| **MOSI** | GPIO23 | SPI Master Out Slave In |
| **NSS / CS** | GPIO5 | SPI Chip Select (Active Low) |
| **RESET** | GPIO14 | Hardware Reset Pin |
| **DIO0** | GPIO26 | Interrupt pin (Tx/Rx Done) |
| **VCC** | 3.3V | Power Supply |
| **GND** | GND | Ground |

> **Warning:** Ensure that logic levels for the LoRa module and sensors match the 3.3V logic level of the ESP32. Applying 5V to ESP32 GPIO pins may damage the microcontroller.
