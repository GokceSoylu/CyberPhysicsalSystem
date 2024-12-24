#include <Arduino.h>
#include <BLEMouse.h>

// BLE fare tanımı
BleMouse bleMouse;

// Zamanlayıcı için değişkenler
unsigned long lastActionTime = 0;
const unsigned long actionInterval = 500; // Hareketler arası bekleme süresi (ms)

void drawS();
void drawO();
void drawY();
void drawL();
void drawU();

void setup()
{
  // Seri iletişim başlatma
  Serial.begin(115200);
  Serial.println("BLE Mouse başlatılıyor...");

  // BLE fareyi başlat
  bleMouse.begin();
  bleMouse.setBatteryLevel(100); // Pil seviyesi: %100
}

void loop()
{
  if (bleMouse.isConnected())
  {
    Serial.println("BLE bağlı, fare hareketi yapılıyor...");

    // "SOYLU" yazısını çiz
    drawS();
    delay(actionInterval);
    drawO();
    delay(actionInterval);
    drawY();
    delay(actionInterval);
    drawL();
    delay(actionInterval);
    drawU();

    // Çizim tamamlandıktan sonra bekle
    while (true)
    {
      Serial.println("Çizim tamamlandı, tekrar başlatmak için resetleyin.");
      delay(5000);
    }
  }
  else
  {
    Serial.println("BLE bağlantısı bekleniyor...");
    delay(1000);
  }
}

void drawS()
{
  Serial.println("S harfi çiziliyor...");
  bleMouse.press(MOUSE_LEFT);
  bleMouse.move(10, 0); // Sağ
  delay(100);
  bleMouse.move(0, 10); // Aşağı
  delay(100);
  bleMouse.move(-10, 0); // Sol
  delay(100);
  bleMouse.move(0, 10); // Aşağı
  delay(100);
  bleMouse.move(10, 0); // Sağ
  bleMouse.release(MOUSE_LEFT);
}

void drawO()
{
  Serial.println("O harfi çiziliyor...");
  bleMouse.press(MOUSE_LEFT);
  bleMouse.move(10, 0); // Sağ
  delay(100);
  bleMouse.move(0, 20); // Aşağı
  delay(100);
  bleMouse.move(-10, 0); // Sol
  delay(100);
  bleMouse.move(0, -20); // Yukarı
  bleMouse.release(MOUSE_LEFT);
}

void drawY()
{
  Serial.println("Y harfi çiziliyor...");
  bleMouse.press(MOUSE_LEFT);
  bleMouse.move(5, 10); // Sağ çapraz aşağı
  delay(100);
  bleMouse.move(5, -10); // Sağ çapraz yukarı
  delay(100);
  bleMouse.move(0, 10); // Dikey aşağı
  bleMouse.release(MOUSE_LEFT);
}

void drawL()
{
  Serial.println("L harfi çiziliyor...");
  bleMouse.press(MOUSE_LEFT);
  bleMouse.move(0, 20); // Dikey aşağı
  delay(100);
  bleMouse.move(10, 0); // Sağ
  bleMouse.release(MOUSE_LEFT);
}

void drawU()
{
  Serial.println("U harfi çiziliyor...");
  bleMouse.press(MOUSE_LEFT);
  bleMouse.move(0, 20); // Dikey aşağı
  delay(100);
  bleMouse.move(10, 0); // Sağ
  delay(100);
  bleMouse.move(0, -20); // Yukarı
  bleMouse.release(MOUSE_LEFT);
}
