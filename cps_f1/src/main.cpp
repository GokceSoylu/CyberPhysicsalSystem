#include <Arduino.h>
#include <Wire.h>
#include <BLEMouse.h>

// BLE fare tanımı
BleMouse bleMouse;

// MPU-6050 I2C adresi
const int MPU_ADDR = 0x68;

// MPU-6050 veri depolama
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

// Hareket eşikleri
const int sensitivity = 1000;      // MPU-6050 duyarlılık katsayısı
const int movementThreshold = 200; // Fare hareketi için eşik

void setup()
{
  // Seri iletişim başlatma
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
}

void loop()
{
  if (bleMouse.isConnected())
  {
    // MPU-6050'den veri oku
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // Veri başlangıç adresi
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 14, true);

    accelX = Wire.read() << 8 | Wire.read();
    accelY = Wire.read() << 8 | Wire.read();
    accelZ = Wire.read() << 8 | Wire.read();
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();

    // Hareket hesaplaması
    int moveX = map(accelX, -sensitivity, sensitivity, -10, 10);
    int moveY = map(accelY, -sensitivity, sensitivity, -10, 10);

    // Hareket eşiklerini kontrol et
    if (abs(moveX) > movementThreshold || abs(moveY) > movementThreshold)
    {
      bleMouse.move(moveX, -moveY); // BLE fareyi hareket ettir
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
