# Troubleshooting & Future Scope

## Troubleshooting Matrix

If you encounter issues during setup or operation, consult the table below for common symptoms and their resolutions.

| Issue / Symptom | Possible Cause | Solution / Fix |
| :--- | :--- | :--- |
| **LoRa Initialization Failed** | SPI wiring error or NSS/RST pin mismatch. | Double-check SCK, MISO, MOSI connections. Ensure `LoRa.setPins(ss, rst, dio0)` matches the physical wiring (GPIO5, 14, 26). |
| **Missing GPS Satellite Lock** | Indoor environment, bad antenna, or reversed TX/RX. | Move outdoors for a clear view of the sky. Ensure GPS TX goes to ESP32 RX, and GPS RX goes to ESP32 TX. |
| **Firebase Sync Errors** | Incorrect database URL, Auth secret, or Wi-Fi drop. | Verify `FIREBASE_HOST` (no `https://` or trailing slash) and `FIREBASE_AUTH`. Check if ESP32 is successfully connected to Wi-Fi. |
| **BMP280 I2C Address Not Found** | Incorrect I2C address or SDA/SCL lines swapped. | Run an I2C Scanner sketch. Common addresses are `0x76` or `0x77`. Update `bmp.begin(0x76)` in the code accordingly. |
| **NaN or 0.0 values from Sensors**| Analog pins disconnected or ADC not configured properly. | Check MICS-6814 and GP2Y wiring. Ensure pins 34, 35, 32, 36 are connected correctly. Verify 3.3V power to the analog modules. |
| **Receiver not receiving LoRa packets** | Frequency, Sync Word, or SF mismatch. | Ensure both Transmitter and Receiver use `433E6`, `setSyncWord(0x12)`, and the same Spreading Factor / Bandwidth. |

---

## Future Scope

The Air-Quality-Monitoring-System establishes a solid foundation for environmental telemetry. Future iterations can leverage several technical upgrade vectors:

### 1. Standardized AQI Calculation
* **CPCB / EPA Standards:** Implement onboard micro-algorithms to convert raw PPM and µg/m³ values into standard Air Quality Index (AQI) scores based on regional regulatory math (e.g., Central Pollution Control Board of India).

### 2. Mesh Networking Integration
* **Multi-Node Routing:** Upgrade the point-to-point LoRa architecture to a LoRa mesh network, allowing multiple Transmitter nodes to relay data across wider municipal or industrial areas to a centralized Receiver gateway.

### 3. Power Optimization
* **Deep-Sleep Implementations:** Integrate solar charging modules combined with ESP32 Deep-Sleep cycles (e.g., wake up every 5 minutes, read sensors, transmit, sleep) to make the Transmitter nodes completely autonomous and off-grid.

### 4. Over-The-Air (OTA) Firmware Delivery
* **Remote Updates:** Implement OTA programming capabilities so that calibration algorithms or new sensor configurations can be pushed to remote edge nodes securely over the air without physical retrieval.

### 5. Machine Learning & Predictive Analytics
* **Local Pollution Trends:** Export historical Firebase data to train Time-Series forecasting models (e.g., ARIMA, LSTM). Integrate the predictive model into the Flutter app to provide users with 24-hour localized pollution forecasts.
