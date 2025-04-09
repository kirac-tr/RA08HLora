#ifndef RA08Lora_h
#define RA08Lora_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class RA08Lora {
  public:
    RA08Lora(uint8_t rxPin, uint8_t txPin, uint32_t baud = 9600);
    void begin();
    void setOTAA(String devEUI, String appEUI, String appKey, String region = "EU868");
    void join();
    bool isJoined();
    void sendHex(String hexData);
    void enableClassC();
    void onMessage(void (*callback)(String msg));
    void listen(); // loop içinde çağırılır

  private:
    SoftwareSerial loraSerial;
    String _devEUI, _appEUI, _appKey, _region;
    void (*messageCallback)(String msg);
    void sendCommand(String cmd, uint16_t delayTime = 500);
    String readResponse();
};

#endif
