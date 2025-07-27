# IoT-Based ECG, Heart Rate and Oxygen Monitoring System

## Overview

This project implements a comprehensive IoT-based health monitoring system that continuously tracks vital signs including ECG signals, heart rate, SpO2 (blood oxygen saturation), and body temperature. The system uses ESP8266 microcontroller to collect sensor data and transmit it to the cloud via MQTT protocol for real-time monitoring and analysis.

## Features

- **Real-time Vital Signs Monitoring:**
  - ECG signal acquisition and processing
  - Heart rate measurement (65-100 BPM normal range)
  - SpO2 (Blood Oxygen Saturation) monitoring (>95% normal)
  - Body temperature measurement (normal <99°F)

- **IoT Connectivity:**
  - WiFi connectivity for internet access
  - MQTT protocol for cloud data transmission
  - Integration with Ubidots IoT platform

- **Alert System:**
  - Visual LED indicators for health status
  - Automatic alerts for abnormal vital signs
  - Real-time health condition monitoring

- **Remote Monitoring:**
  - Cloud-based data storage and visualization
  - Remote access to patient health data
  - Continuous monitoring capabilities

## Hardware Components

- **ESP8266 WiFi Module** - Main microcontroller
- **MAX30100 Pulse Oximeter Sensor** - Heart rate and SpO2 measurement
- **DS18B20 Temperature Sensor** - Body temperature monitoring
- **ECG Sensor Module** - ECG signal acquisition
- **LED Indicators** - Status and alert notifications
- **Connecting wires and breadboard**

## Pin Configuration

```
ESP8266 Pin Configuration:
- A0: ECG sensor input
- D2: DS18B20 temperature sensor (ONE_WIRE_BUS)
- D6: Green LED (Normal status indicator)
- D7: WiFi status LED
- D8: Red LED (Alert indicator)
```

## Software Dependencies

### Arduino Libraries Required:
- `Wire.h` - I2C communication
- `MAX30100_PulseOximeter.h` - Pulse oximeter functionality
- `ESP8266WiFi.h` - WiFi connectivity
- `PubSubClient.h` - MQTT client
- `OneWire.h` - OneWire protocol for temperature sensor
- `DallasTemperature.h` - DS18B20 temperature sensor library

## Installation and Setup

### 1. Hardware Setup
1. Connect the sensors according to the pin configuration
2. Ensure proper power supply to all components
3. Verify all connections before powering on

### 2. Software Setup
1. Install Arduino IDE
2. Install ESP8266 board package
3. Install required libraries via Library Manager
4. Configure WiFi credentials and Ubidots token

### 3. Configuration
Update the following parameters in `iot_health_monitoring.ino`:

```cpp
#define WIFISSID "YOUR_WIFI_SSID"     // Your WiFi network name
#define PASSWORD "YOUR_WIFI_PASSWORD"  // Your WiFi password
#define TOKEN "YOUR_UBIDOTS_TOKEN"     // Your Ubidots device token
```

## Code Structure

### Main Functions:

- **`setup()`**: Initializes sensors, WiFi connection, and MQTT client
- **`loop()`**: Main execution loop that reads sensors and publishes data
- **`reconnect()`**: Handles MQTT reconnection
- **`callback()`**: Processes incoming MQTT messages
- **`onBeatDetected()`**: Callback for pulse detection events

### Data Flow:
1. Read ECG signal from analog pin A0
2. Collect SpO2 and heart rate data
3. Measure body temperature using DS18B20
4. Process and format data for MQTT transmission
5. Publish data to Ubidots cloud platform
6. Monitor health parameters and trigger alerts

## Health Monitoring Parameters

| Parameter | Normal Range | Alert Condition |
|-----------|--------------|-----------------|
| Heart Rate | 65-100 BPM | <65 or >100 BPM |
| SpO2 | >95% | <95% |
| Temperature | <99°F | >99°F |
| ECG | Continuous monitoring | Irregular patterns |

## Alert System

- **Green LED (D6)**: Normal health status
- **Red LED (D8)**: Alert condition triggered
- **WiFi LED (D7)**: Connection status indicator

Alert triggers when any of the following conditions are met:
- Temperature > 99°F
- SpO2 < 95%
- Heart rate < 65 BPM or > 100 BPM

## Cloud Integration

The system integrates with **Ubidots** IoT platform for:
- Real-time data visualization
- Historical data storage
- Remote monitoring dashboards
- Alert notifications
- Data analytics and trends

### MQTT Topics:
```
/v1.6/devices/remote-patient-health-monitoring
```

### Variables Published:
- `myecg` - ECG sensor readings
- `SPo2` - Blood oxygen saturation
- `heartrate` - Heart rate in BPM
- `temperature` - Body temperature in Fahrenheit

## Usage Instructions

1. **Power on the system** and wait for WiFi connection
2. **Monitor LED indicators** for system status
3. **Access Ubidots dashboard** for real-time data visualization
4. **Set up alerts** in Ubidots for abnormal readings
5. **Monitor patient health** remotely through the cloud interface

## Safety Considerations

⚠️ **Important Safety Notes:**
- This system is for educational and demonstration purposes
- Not intended for critical medical diagnosis
- Always consult healthcare professionals for medical decisions
- Ensure proper sensor placement for accurate readings
- Regular calibration of sensors is recommended

## Troubleshooting

### Common Issues:
1. **WiFi Connection Problems**: Check SSID and password
2. **Sensor Readings Irregular**: Verify sensor connections
3. **MQTT Connection Failed**: Verify Ubidots token and internet connection
4. **Temperature Sensor Not Working**: Check OneWire bus connection

## Future Enhancements

- Integration with additional sensors (blood pressure, glucose)
- Mobile application development
- Machine learning for pattern recognition
- Battery power optimization
- Wireless sensor nodes
- Advanced alert systems (SMS, email notifications)

## Contributing

Contributions to improve the system are welcome. Please follow these steps:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is open-source and available under the MIT License.

## Author

**nirmt-124398**

## Acknowledgments

- Ubidots IoT platform for cloud services
- Arduino community for libraries and support
- ESP8266 community for documentation and examples

---

*For questions, issues, or suggestions, please open an issue in the repository.*
