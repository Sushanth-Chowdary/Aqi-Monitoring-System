# System Architecture

The Air-Quality-Monitoring-System features a robust end-to-end data pipeline, transitioning from edge sensing to cloud storage, and finally to a mobile interface.

## Architecture Flow

Below is the high-level physical pipeline depicting the flow of data across the system:

```text
[ Physical Environment ]
          |
          v
+-----------------------+
|   SENSORS & GPS       |
|  (MICS-6814, GP2Y,    |
|   BMP280, NEO-6M)     |
+-----------------------+
          | (Analog / I2C / UART)
          v
+-----------------------+
|  TRANSMITTER NODE     |
|      (ESP32)          |
+-----------------------+
          | 
          | (SPI)
          v
+-----------------------+
|  SX1278 LORA (Tx)     |
+-----------------------+
          |
          | ~ ~ ~ RF 433 MHz ~ ~ ~
          v
+-----------------------+
|  SX1278 LORA (Rx)     |
+-----------------------+
          |
          | (SPI)
          v
+-----------------------+
|    RECEIVER NODE      |
|      (ESP32)          |
+-----------------------+
          |
          | (Wi-Fi)
          v
+-----------------------+
|  FIREBASE REALTIME DB |
|       (Cloud)         |
+-----------------------+
          |
          | (Streams / Sockets)
          v
+-----------------------+
|  FLUTTER MOBILE APP   |
|   (Client UI/UX)      |
+-----------------------+
```

## LoRa Configuration Parameters

To ensure reliable, long-range communication between the Transmitter and Receiver nodes, the SX1278 RA-02 modules are configured with the following optimized parameters:

* **Frequency:** 433 MHz (ISM Band)
* **Bandwidth (BW):** 125 kHz (Balances range and data rate)
* **Coding Rate (CR):** 4/5 (Standard error correction overhead)
* **Spreading Factor (SF):** 7 (Provides good reliability with minimal airtime)
* **Sync Word:** `0x12` (Network identifier to isolate our system's packets)
* **CRC:** Enabled (Ensures packet payload integrity on the receiver side)

## Communication Protocol

Data is encapsulated into a lightweight, string-based packet format before being transmitted over the LoRa network. The Receiver parses this exact structure and maps it to Firebase fields.

### Packet Payload Structure
Key-value pairs separated by commas.

**Format:**
`LAT:<val>,LON:<val>,TEMP:<val>,PRESS:<val>,PM25:<val>,CO:<val>,NH3:<val>,NO2:<val>`

**Example Transmission Payload:**
```text
LAT:17.385044,LON:78.486671,TEMP:30.25,PRESS:1009.45,PM25:20.30,CO:45.00,NH3:20.00,NO2:10.00
```

### Parsing Logic
When the Receiver node detects a valid packet (CRC passed), it splits the string using the comma (`,`) delimiter, then further isolates the metric and the value using the colon (`:`). These parsed float/double values are then batched and pushed to the corresponding Firebase JSON nodes.
