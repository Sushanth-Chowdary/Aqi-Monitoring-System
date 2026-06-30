# Firebase Realtime Database Structure

The cloud backend is powered by Firebase Realtime Database. The schema is designed to be flat and efficient, enabling the ESP32 to push updates seamlessly and the Flutter app to maintain synchronized data streams without complex queries.

## JSON Schema

The database utilizes a hierarchical tree structure organized by functional categories: location, environmental conditions, and gas concentrations.

```json
{
  "aqi_monitor": {
    "current_readings": {
      "timestamp": 1698765432,
      
      "location": {
        "latitude": 17.385044,
        "longitude": 78.486671
      },
      
      "environment": {
        "temperature": 30.25,
        "pressure": 1009.45
      },
      
      "particulate_matter": {
        "pm25": 20.30
      },
      
      "gases": {
        "co": 45.00,
        "nh3": 20.00,
        "no2": 10.00
      }
    }
  }
}
```

## Database Tree Visualization

```text
aqi_monitor/
└── current_readings/
    ├── timestamp: 1698765432
    ├── location/
    │   ├── latitude: 17.385044
    │   └── longitude: 78.486671
    ├── environment/
    │   ├── temperature: 30.25
    │   └── pressure: 1009.45
    ├── particulate_matter/
    │   └── pm25: 20.30
    └── gases/
        ├── co: 45.00
        ├── nh3: 20.00
        └── no2: 10.00
```

### Notes for Application Integration
* **`timestamp`:** Represents the epoch time when the packet was received by the ESP32 Receiver node.
* **Listeners:** The Flutter app should establish real-time listeners on the `/aqi_monitor/current_readings` path to trigger state updates instantly upon any value change.
