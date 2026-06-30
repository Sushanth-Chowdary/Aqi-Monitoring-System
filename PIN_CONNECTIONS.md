# ESP32 Air Quality Monitoring System - Pin Connections

## Transmitter ESP32

### MICS-6814

  Sensor Pin   ESP32 Pin
  ------------ -----------
  CO           GPIO34
  NH3          GPIO35
  NO2          GPIO32
  VCC          5V
  GND          GND

### GP2Y1010AU0F

  Sensor Pin    ESP32 Pin
  ------------- -----------
  Vo            GPIO36
  LED Control   GPIO2
  VCC           5V
  GND           GND

### BMP280

  Sensor Pin   ESP32 Pin
  ------------ -----------
  SDA          GPIO21
  SCL          GPIO22
  VIN          3.3V
  GND          GND

### NEO-6M GPS

  GPS Pin   ESP32 Pin
  --------- -----------
  TX        GPIO16
  RX        GPIO17
  VCC       3.3V/5V
  GND       GND

### SX1278 LoRa

  Module Pin   ESP32 Pin
  ------------ -----------
  NSS          GPIO5
  SCK          GPIO18
  MISO         GPIO19
  MOSI         GPIO23
  RESET        GPIO14
  DIO0         GPIO26
  VCC          3.3V
  GND          GND

## Receiver ESP32

### SX1278 LoRa

  Module Pin   ESP32 Pin
  ------------ -----------
  NSS          GPIO5
  SCK          GPIO18
  MISO         GPIO19
  MOSI         GPIO23
  RESET        GPIO14
  DIO0         GPIO26
  VCC          3.3V
  GND          GND

### Wi-Fi

Built into the ESP32. No external wiring required.

## Notes

-   Never power the SX1278 from 5V.
-   Use a common GND for all modules.
-   BMP280 uses the I²C bus (GPIO21/22).
-   GPS uses UART1 (GPIO16/17).
