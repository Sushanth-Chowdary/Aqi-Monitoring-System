// Sender.ino
// NOTE: Replace this placeholder with the latest sensor code you developed.
// This file is intended to contain:
// - MICS-6814 (CO/NH3/NO2)
// - GP2Y1010 Dust Sensor
// - BMP280
// - TinyGPS++
// - LoRa SX1278 transmission
//
// At the end of loop():
// String payload = "CO:" + String(co_ugm3,2) + ",NH3:" + String(nh3_ugm3,2) +
// ",NO2:" + String(no2_ugm3,2) + ",Dust:" + String(dustDensity,2) +
// ",Temp:" + String(temperature,2) + ",Pres:" + String(pressure,2) +
// ",Lat:" + String(latitude,6) + ",Lon:" + String(longitude,6);
//
// LoRa.beginPacket();
// LoRa.print(payload);
// LoRa.endPacket();
