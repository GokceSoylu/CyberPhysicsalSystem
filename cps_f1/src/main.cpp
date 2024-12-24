// #include <Arduino.h>

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEMouse.h>

// BLE Mouse nesnesini oluştur
BLEMouse bleMouse;

void setup()
{
  Serial.begin(115200);

  // BLE Mouse'u başlat
  if (!bleMouse.isConnected())
  {
    Serial.println("BLE Mouse başlatılıyor...");
    bleMouse.begin();
  }
}

void loop()
{
  // BLE bağlıysa fare hareketi ve tıklama simüle edelim
  if (bleMouse.isConnected())
  {
    Serial.println("BLE bağlı, fare hareketi yapılıyor...");

    // Fareyi sağa doğru hareket ettir
    bleMouse.move(10, 0);
    delay(500);

    // Sol fare tıklaması
    bleMouse.click(MOUSE_LEFT);
    delay(500);
  }
  else
  {
    Serial.println("BLE bağlantısı bekleniyor...");
  }

  delay(1000);
}
