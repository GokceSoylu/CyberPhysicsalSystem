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
 

 



 #include <Arduino.h>
#include <Wire.h>
#include <BLEMouse.h>

// BLE fare tanımı
BleMouse bleMouse; // neneyi oluşturuyoruz

// MPU-6050 I2C adresi
const int MPU_ADDR = 0x68; // sensörü tanıyabilmek için adres atadım

// MPU-6050 veri depolama
int16_t accelX, accelY, accelZ; // acceleration - ivme
int16_t gyroX, gyroY, gyroZ;    // gyroscope - açısla hız

// Hareket eşikleri
const int sensitivity = 1000;      // MPU-6050 duyarlılık katsayısı - burada katsayı gerktii durumda daha da küçültülüp
                                   // hassaslaştırılabilir. map fonksiyonunda accellation dğişkenleri(accelx, accely) ile birlikte
                                   // kullanılacaktır.
const int movementThreshold = 200; // Fare hareketi için eşik - bu eşiği anlmasız hareketleri ignore etmemiz için

void setup()
{
  // Seri iletişim başlatma
  Serial.begin(115200); // Hızı, sistem ihtiyaçlarına göre 9600, 115200, hatta 256000 gibi farklı değerlerde seçebilirdik. Ancak
                        // hem kodda hem de seri monitörde aynı hızın kullanıldığımızdan emin olunmalıyız.
  Serial.println("MPU-6050 ve BLE Mouse başlatılıyor...");

  // BLE fareyi başlat
  bleMouse.begin(); // nesnemizi başlatıyoruz. bu şekilde esp32 yi nübir ble fare olarak görücek

  // MPU-6050 başlatma
  Wire.begin();                     // esp32 nin 12c protokolü ile haberşelmesini başlattık
  Wire.beginTransmission(MPU_ADDR); // zaten yukarıda değişkeni tanımlamıştık. bu sensörümüzmün adresi. esp32 den sensörümüze
                                    // veri göndermek için yazdk
  Wire.write(0x6B);                 // Güç yönetimi kaydını seç bit 6 uyku modu kontrolu. değer 1: uykuda, değer: 0 çalışıyor
  Wire.write(0x00);                 // Cihazı uyandır. 6.biti 0nyapıpı uyanık vaziyete getirdik
  Wire.endTransmission();           // haberleşmeyi sonladırıp veriyi sensöre gönderdik :))
}

void loop()
{
  if (bleMouse.isConnected()) // bağlantı olup olmadığını kontrol ediyoruz
  {
    // MPU-6050'den veri oku
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);                     // Veri başlangıç adresi - bu sensörümüzün MPU-6050'nin ivmeölçer X ekseni değerinin başlangıç adresidi
    Wire.endTransmission(false);          // burada yanlış anlama sadece veriyi esp 32 ye göndermeyi hazıladık letişimi kesmiyoruz.
    Wire.requestFrom(MPU_ADDR, 14, true); // 6 bayt ivmeölçer, 6 bayt jiroskop için( x-y-z (ikişer bayt)
                                          // kalan ikide sıcalıkda aslında burada kullanmıyıcaz
    // veri okuma işlemi. kaydırrıak okumasebebi her eksen için 2 bayt(16 bit) veri var ancak metodumuz ancak bit bayt
    // okuyabildiği için ilk baytı okuyup bir bayt(8 bit) kaydırıp devamını da tekrardan okuyup iik baytı birleştiriryoruz
    accelX = Wire.read() << 8 | Wire.read();
    accelY = Wire.read() << 8 | Wire.read();
    accelZ = Wire.read() << 8 | Wire.read();
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();

    // Hareket hesaplaması - biliyorsun bunu detayagirmiyorum. hassaslık değer küçükse hassaas vb
    int moveX = map(accelX, -sensitivity, sensitivity, -10, 10);
    int moveY = map(accelY, -sensitivity, sensitivity, -10, 10);

    // Hareket eşiklerini kontrol etme - abs burada mutlak değere alır. aşaıdaki kontrol anlamsız harekti göz ardı etmek için
    if (abs(moveX) > movementThreshold || abs(moveY) > movementThreshold)
    {
      bleMouse.move(moveX, -moveY); // BLE fareyi hareket ettir- aldığımız verilerle şimdi ekrandaki fareyi hrt ettirelim :))
      Serial.print("Hareket: X=");
      Serial.print(moveX);
      Serial.print(", Y=");
      Serial.println(moveY);
    }
  }
  else
  {
    Serial.println("BLE bağlantısı bekleniyor...");
    delay(1000); // bağlantı olmamaıs durumunda bir sn bekler ve tekrar bağlanmayı dener
  }
}
