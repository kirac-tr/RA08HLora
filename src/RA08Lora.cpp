#include "RA08Lora.h"

RA08Lora::RA08Lora(uint8_t rxPin, uint8_t txPin, uint32_t baud) : loraSerial(rxPin, txPin) {
  loraSerial.begin(baud);
  messageCallback = nullptr;
}

void RA08Lora::begin() {
  delay(2000);
}

void RA08Lora::setOTAA(String devEUI, String appEUI, String appKey, String region) {
  _devEUI = devEUI;
  _appEUI = appEUI;
  _appKey = appKey;
  _region = region;

  sendCommand("AT+MODE=LWOTAA");
  sendCommand("AT+ID=DevEui,\"" + _devEUI + "\"");
  sendCommand("AT+ID=AppEui,\"" + _appEUI + "\"");
  sendCommand("AT+KEY=APPKEY,\"" + _appKey + "\"");
  sendCommand("AT+DR=" + _region);
}

void RA08Lora::join() {
  sendCommand("AT+JOIN", 3000);
}

bool RA08Lora::isJoined() {
  sendCommand("AT+JOINSTATUS");
  String res = readResponse();
  return res.indexOf("Joined") != -1;
}

void RA08Lora::sendHex(String hexData) {
  sendCommand("AT+MSGHEX=\"" + hexData + "\"", 2000);
}

void RA08Lora::enableClassC() {
  sendCommand("AT+CLASS=C");
}

void RA08Lora::onMessage(void (*callback)(String msg)) {
  messageCallback = callback;
}

void RA08Lora::listen() {
  if (loraSerial.available()) {
    String msg = loraSerial.readStringUntil('\n');
    msg.trim();
    if (msg.startsWith("RX")) {
      int idx = msg.indexOf("\"");
      int endIdx = msg.lastIndexOf("\"");
      if (idx != -1 && endIdx != -1 && endIdx > idx) {
        String hexData = msg.substring(idx + 1, endIdx);
        if (messageCallback != nullptr) {
          messageCallback(hexData);
        }
      }
    }
  }
}

String RA08Lora::readResponse() {
  String response = "";
  unsigned long timeout = millis() + 2000;
  while (millis() < timeout) {
    while (loraSerial.available()) {
      char c = loraSerial.read();
      response += c;
    }
  }
  return response;
}

void RA08Lora::sendCommand(String cmd, uint16_t delayTime) {
  loraSerial.println(cmd);
  delay(delayTime);
}
