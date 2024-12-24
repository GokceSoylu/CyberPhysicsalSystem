#include <Arduino.h>
#include <BLEMouse.h>

// BLE fare tanımı
BleMouse bleMouse;

void setup()
{
  // Seri iletişim başlatma
  Serial.begin(115200);
  Serial.println("BLE Mouse başlatılıyor...");

  // BLE fareyi başlat
  bleMouse.begin();
}

void loop()
{
  if (bleMouse.isConnected())
  {
    Serial.println("BLE bağlı, fare hareketi yapılıyor...");
    bleMouse.move(10, 0); // Farenin sağa hareketi
    delay(500);
  }
  else
  {
    Serial.println("BLE bağlantısı bekleniyor...");
    delay(1000);
  }
}
