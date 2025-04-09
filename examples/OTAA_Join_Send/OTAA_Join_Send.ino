#include <RA08Lora.h>

RA08Lora lora(10, 11); // RX = D10, TX = D11

void onIncomingMessage(String hexData) {
  Serial.print("Gelen veri (hex): ");
  Serial.println(hexData);
  
  // Eğer metin olarak görmek istersen:
  String decoded = "";
  for (int i = 0; i < hexData.length(); i += 2) {
    String byteStr = hexData.substring(i, i + 2);
    char c = strtol(byteStr.c_str(), NULL, 16);
    decoded += c;
  }

  Serial.print("Decoded: ");
  Serial.println(decoded);
}

void setup() {
  Serial.begin(9600);
  lora.begin();

  lora.setOTAA("B8F1E8CC369143AE", "025F71E3AF5551E3", "75BC9647D07797BFFB2745DF750D4D00");
  lora.join();

  while (!lora.isJoined()) {
    Serial.println("Ağa katılım bekleniyor...");
    delay(3000);
  }

  Serial.println("LoRaWAN ağına katıldı!");

  lora.enableClassC();
  lora.onMessage(onIncomingMessage);
}

void loop() {
  lora.listen(); // sürekli veri kontrolü
}
