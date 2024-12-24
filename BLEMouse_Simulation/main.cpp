#include <iostream>
#include <thread>
#include <chrono>

// Sahte BLEMouse sınıfı
class BLEMouse
{
public:
    void begin()
    {
        std::cout << "Sahte BLEMouse başlatıldı.\n";
    }

    bool isConnected()
    {
        return false; // Simülasyon için her zaman bağlantısız.
    }

    void move(int x, int y)
    {
        std::cout << "Fare hareketi: X=" << x << ", Y=" << y << std::endl;
    }
};

BLEMouse bleMouse;

void setup()
{
    std::cout << "Simülasyon: Setup başlatılıyor...\n";
    bleMouse.begin();
}

void loop()
{
    if (bleMouse.isConnected())
    {
        std::cout << "Simülasyon: BLE bağlı, fare hareket ediyor...\n";
        bleMouse.move(10, 10);
    }
    else
    {
        std::cout << "Simülasyon: BLE bağlantısı bekleniyor...\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
