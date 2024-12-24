# BLE HID Mouse Using ESP32 and MPU-6050 



## Introduction 

In this project, a BLE (Bluetooth Low Energy) HID mouse is implemented using an ESP32 microcontroller and an MPU-6050 accelerometer and gyroscope sensor. This project combines embedded systems, BLE communication, and motion sensing to create a wireless mouse that operates by detecting hand movements. It was designed as part of the Cyber-Physical Systems course. 

### Objectives 

Implement BLE functionality on ESP32 to simulate a wireless mouse. 
Utilize MPU-6050 for motion detection and translate movements into mouse actions. 
Test and validate the system’s performance on a computer. 
## Materials and Components 

ESP32 microcontroller 
MPU-6050 accelerometer and gyroscope sensor 
Breadboard and jumper wires 
Computer with BLE support 
Arduino IDE 
## System Design 

The system comprises two main components: the ESP32, which handles BLE communication and mouse emulation, and the MPU-6050, which provides motion data. The MPU-6050 communicates with the ESP32 via I2C protocol. Hand movements detected by the sensor are processed and sent to the computer as mouse movements through the BLE HID protocol. 

### Hardware Setup 

Connections: 
Connect the MPU-6050 to the ESP32 as follows: 
VCC (MPU-6050) → 3.3V (ESP32) 
GND (MPU-6050) → GND (ESP32) 
SCL (MPU-6050) → GPIO 22 (ESP32) 
SDA (MPU-6050) → GPIO 21 (ESP32) 
Use a breadboard and jumper wires to establish connections. 
Power Supply: 
Ensure the ESP32 is powered through a USB connection to the computer. 
3.2 Software Implementation 
 https://github.com/GokceSoylu/CyberPhysicsalSystem/tree/main/cps_f1 

## Results and Observations 

The BLE mouse successfully connects to the computer via Bluetooth. 
Hand movements detected by the MPU-6050 are accurately translated into cursor movements on the screen. 
Sensitivity and thresholds were adjusted to balance responsiveness and stability. 
## Challenges and Solutions 

Challenge: Noise in accelerometer readings caused erratic cursor movements. 
Solution: Applied thresholds to filter out minor, unintentional movements. 
Challenge: Initial BLE connection delays. 
Solution: Debugged BLE initialization sequence and ensured proper pairing. 
## Conclusion 

The project demonstrates a practical implementation of a BLE HID mouse using ESP32 and MPU-6050. It highlights the integration of hardware components and BLE technology to create a functional cyber-physical system. The system’s performance is satisfactory for basic use, with room for future enhancements such as additional gesture controls or improved motion filtering. 

## References 

ESP32 Documentation 
MPU-6050 Datasheet 
Arduino IDE Resources 
 

 