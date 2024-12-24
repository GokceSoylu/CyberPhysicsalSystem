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
