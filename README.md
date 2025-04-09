# RA08Lora Arduino Library

Bu kütüphane, AI-Thinker RA-08H LoRaWAN modülünü **Arduino Pro Mini** veya diğer Arduino uyumlu kartlarla kullanmak için geliştirilmiştir. Modül, Semtech SX1276 yongasını temel alır ve AT komutları üzerinden kontrol edilir.

## ✨ Özellikler

- LoRaWAN Class C desteği
- OTAA (Over-the-Air Activation) ile ağa katılım
- Sürekli RX penceresi ile mesaj dinleme (dinleme modu)
- Gelen mesajların seri port üzerinden alınması
- Geliştirilebilir AT komut kontrolü

## 🔌 Donanım Bağlantısı (Arduino Pro Mini)

| RA-08H Pin | Arduino Pro Mini Pin | Açıklama      |
|-----------:|---------------------:|---------------|
| VCC        | VCC (3.3V)           | Güç           |
| GND        | GND                  | Toprak        |
| TXD        | D8 (SoftwareSerial)  | Modül → Arduino |
| RXD        | D9 (SoftwareSerial)  | Arduino → Modül |
| RST        | D7                   | Reset pini *(opsiyonel)*

> **Not:** RA-08H modülü yalnızca 3.3V ile çalışır. 5V doğrudan bağlanmamalıdır.

## 🧪 Örnek Kullanım

```cpp
#include <RA08Lora.h>

RA08Lora lora(D8, D9); // TX, RX

void setup() {
  Serial.begin(9600);
  lora.begin();

  // OTAA ile ağa bağlan
  lora.joinOTAA("DevEUI", "AppEUI", "AppKey");

  // Sürekli RX modunu başlat
  lora.enableRXMode();
}

void loop() {
  String msg = lora.receive();
  if (msg.length() > 0) {
    Serial.println("Gelen Mesaj: " + msg);
  }
}

📦 Kurulum
  1. Arduino Library Manager üzerinden (yakında)
  2. Alternatif olarak:
      Bu depoyu zip olarak indir.

Arduino IDE > Sketch > Include Library > Add .ZIP Library üzerinden ekle.
