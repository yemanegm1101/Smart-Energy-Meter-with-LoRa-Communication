# Smart Energy Meter With LoRa Communication
A complete smart energy metering system with wireless LoRa communication, built with Arduino Nano and simulated in Proteus.
![Image](https://github.com/user-attachments/assets/fe11b4bc-48e2-4441-9ed7-6c122f241089)
![Image](https://github.com/user-attachments/assets/1204392b-1575-412e-b2bb-04f52af7a580)


## Project Overview

This project implements a smart energy meter that measures voltage, current, power, and energy consumption, then transmits the data wirelessly using LoRa technology. The system consists of two main components:

1. **Sender Unit**: Measures electrical parameters using voltage and current sensors, displays readings on an LCD, and transmits data via LoRa.
2. **Receiver Unit**: Receives data from the sender unit and displays it on a serial monitor.

## Features

- **Real-time Monitoring**: Measures voltage, current, power, and energy consumption
- **Wireless Communication**: Uses LoRa (RFM95W) for long-range, low-power data transmission
- **Visual Feedback**: LCD display on sender unit and LED indicators for transmission status
- **Energy Calculation**: Calculates and displays energy consumption in watt-hours
- **Complete Simulation**: Fully simulated in Proteus for testing before hardware implementation

## Hardware Requirements

### Sender Unit
- Arduino Nano
- 20x4 I2C LCD Display
- RFM95W LoRa Module (868MHz)
- Voltage Sensor (Voltage divider circuit)
- Current Sensor (ACS712)
- 2x LEDs (Red and Green) with resistors
- Power supply components
- Connecting wires

### Receiver Unit
- Arduino Nano
- RFM95W LoRa Module (868MHz)
- 2x LEDs (Red and Green) with resistors
- Connecting wires

## Pin Connections

### Sender Unit
- **Voltage Sensor**: Connected to A0
- **Current Sensor**: Connected to A1
- **LCD Display**: I2C connection to A4 (SDA) and A5 (SCL)
- **LoRa Module**:
  - NSS: 10
  - RESET: 9
  - DIO0: 2
  - MOSI: 11
  - MISO: 12
  - SCK: 13
- **LEDs**:
  - Red LED: Pin 5
  - Green LED: Pin 6

### Receiver Unit
- **LoRa Module**:
  - NSS: 10
  - RESET: 9
  - DIO2: 2
  - MOSI: 11
  - MISO: 12
  - SCK: 13
- **LEDs**:
  - Red LED: Pin 5
  - Green LED: Pin 6

## Software Requirements

- Arduino IDE
- Libraries:
  - SPI
  - LoRa
  - Wire
  - LiquidCrystal_I2C
  - EmonLib
- Proteus Design Suite (for simulation)

## Simulation Setup

1. Open the Proteus project files:
   - `Smart_Meter_Arduino_Nano_Send.pdsprj` for the sender unit
   - `Smart_Meter_Arduino_Nano_Receive.pdsprj` for the receiver unit

2. Compile the Arduino sketches and generate HEX files:
   - `Smart_Energy_Meter_Arduino_nano_lora_sender.ino` for the sender unit
   - `Smart_Energy_Meter_Arduino_nano_lora_Receive.ino` for the receiver unit

3. Load the HEX files into the respective Arduino Nano components in Proteus

4. Run the simulation to observe the system in action

## How It Works

### Sender Unit
1. Reads voltage from the voltage sensor on pin A0
2. Reads current from the current sensor on pin A1
3. Calculates power (P = V × I) and energy consumption
4. Displays all measurements on the LCD
5. Transmits data via LoRa every 2 seconds
6. Indicates transmission with LED indicators

### Receiver Unit
1. Continuously listens for incoming LoRa packets
2. Parses received data to extract voltage, current, power, and energy values
3. Displays received values on the serial monitor
4. Indicates reception with LED indicators

## Calibration

The system includes calibration constants that may need adjustment based on your specific sensors:

- Voltage sensor: Calibration value of 187.0 (may need adjustment)
- Current sensor: Sensitivity of 185 mV/A for a 5A module (adjust based on your sensor)
- Offset voltage: 2542 mV (adjust based on your sensor's zero-current output)

## Files Included

- `Smart_Energy_Meter_Arduino_nano_lora_sender.ino`: Arduino code for the sender unit
- `Smart_Energy_Meter_Arduino_nano_lora_Receive.ino`: Arduino code for the receiver unit
- `Smart_Meter_Arduino_Nano_Send.pdsprj`: Proteus simulation file for the sender unit
- `Smart_Meter_Arduino_Nano_Receive.pdsprj`: Proteus simulation file for the receiver unit
- `Send_lora_RFM95W_868S2.jpg`: Image of the sender circuit
- `Receive_lora_RFM95W_868S2.jpg`: Image of the receiver circuit

# Note on LoRa Simulation
The LoRa module (RFM95) is not natively supported in Proteus for accurate wireless simulation. However, in this project, the LoRa module is implemented as a conceptual design. The Proteus schematic reflects the intended wiring and interfacing strategy, but actual LoRa communication testing must be done on real hardware.

## Troubleshooting
If LoRa.begin() fails, verify:
- Correct frequency band matches your RFM95 module
- CS, RST, DIO0 pins match LoRa.setPins() settings
- 3.3 V regulator can supply ≥120 mA peak

## Future Improvements
- Add data logging capability to store measurements
- Implement a web interface for remote monitoring
- Add more sensors for comprehensive power quality analysis
- Develop a mobile app for real-time monitoring
- Implement bidirectional communication for remote control

## Credits
Developed as part of an educational project on IoT and energy monitoring systems.

###  LoRa Module License
This project uses the RFM95 LoRa module symbols & footprint models provided by SnapMagic https://www.snapeda.com/about/import/#Proteus Search, Inc. By using these models in your PCB or schematic, you agree to the SnapMagic Search terms.

#### Design License
You and your sub-licensees are hereby licensed to design, manufacture, use and distribute circuit board designs and circuit boards formed by combining Models provided by SnapMagic Search with other circuit elements of your choosing. You may convey such combinations under licensing terms of your choice.
Individual Models remain the intellectual property of SnapMagic Search, Inc. You shall not:
   ##### 1. Sell, assign, lease, lend, rent, issue, sublicense, or otherwise distribute the Models; or
   ###### 2. Remove, alter, or conceal any copyright, trademark, or proprietary rights notices contained in the Models. 
   Once integrated into your PCB design, Models may be modified to suit your project requirements.
   ##### Limitation of Liability 
   In no event will SnapMagic Search or its affiliates be liable for any indirect, special, incidental, punitive, or consequential damages arising out of or in connection with this Agreement.
   
###### Refer to the original license text provided by SnapMagic Search for full details.

# Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
