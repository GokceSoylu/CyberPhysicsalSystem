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

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("MPU-6050 testi başlatılıyor...");

//   // MPU-6050 başlatma
//   Wire.begin();
//   Wire.beginTransmission(MPU_ADDR);
//   Wire.write(0x6B); // Güç yönetimi kaydını seç
//   Wire.write(0x00); // Cihazı uyandır
//   Wire.endTransmission();

//   // MPU-6050'nin çalışıp çalışmadığını test edin
//   Wire.beginTransmission(MPU_ADDR);
//   if (Wire.endTransmission() != 0)
//   {
//     Serial.println("MPU-6050 algılanamadı!");
//     while (1)
//       ; // Sonsuza kadar bekle
//   }
//   else
//   {
//     Serial.println("MPU-6050 başarıyla başlatıldı!");
//   }
// }

// void loop()
// {
//   // Boş bırakılabilir
// }

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("BLE başlatılıyor...");

//   // BLE başlat
//   BLEDevice::init("ESP32_Test");
//   BLEServer *pServer = BLEDevice::createServer();

//   Serial.println("BLE başlatıldı ve yayında!");
// }

// void loop()
// {
//   delay(1000);
// }
