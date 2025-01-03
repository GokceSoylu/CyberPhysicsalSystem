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
### Software Implementation 
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
 

 







----------
# SAKLAMA
#include <Arduino.h>
#include <Wire.h>
#include <BLEMouse.h>

// BLE fare tanımı
BleMouse bleMouse;

// MPU-6050 I2C adresi
const int MPU_ADDR = 0x68;

// MPU-6050 veri depolama
int16_t accelX, accelY, accelZ;

// Hareket eşikleri
const int sensitivity = 500;      // Duyarlılık
const int movementThreshold = 50; // Fare hareket eşiği

void setup()
{
  Serial.begin(115200);
  Serial.println("MPU-6050 ve BLE Mouse başlatılıyor...");

  // BLE fareyi başlat
  bleMouse.begin();

  // MPU-6050 başlatma
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Güç yönetimi kaydını seç
  Wire.write(0x00); // Cihazı uyandır
  Wire.endTransmission();

  // MPU-6050'nin çalışıp çalışmadığını test edin
  Wire.beginTransmission(MPU_ADDR);
  if (Wire.endTransmission() != 0)
  {
    Serial.println("MPU-6050 algılanamadı!");
    while (1)
      ; // Sonsuza kadar bekle
  }
  else
  {
    Serial.println("MPU-6050 başarıyla başlatıldı!");
  }
}

void loop()
{
  if (bleMouse.isConnected())
  {
    // MPU-6050'den veri oku
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // Veri başlangıç adresi
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6, true); // Yalnızca ivmeölçer verileri alınacak

    accelX = Wire.read() << 8 | Wire.read();
    accelY = Wire.read() << 8 | Wire.read();
    accelZ = Wire.read() << 8 | Wire.read();

    // Seri Monitör'e sensör verilerini yazdır
    Serial.print("AccelX: ");
    Serial.print(accelX);
    Serial.print(", AccelY: ");
    Serial.print(accelY);
    Serial.print(", AccelZ: ");
    Serial.println(accelZ);

    // Hareket hesaplama
    int moveX = map(accelX, -sensitivity, sensitivity, -10, 10);
    int moveY = map(accelY, -sensitivity, sensitivity, -10, 10);

    // Hareket eşiğini kontrol et
    if (abs(moveX) > movementThreshold || abs(moveY) > movementThreshold)
    {
      bleMouse.move(moveX, -moveY); // Fareyi hareket ettir
      Serial.print("Hareket: X=");
      Serial.print(moveX);
      Serial.print(", Y=");
      Serial.println(moveY);
    }
  }
  else
  {
    Serial.println("BLE bağlantısı bekleniyor...");
    delay(1000);
  }
}
