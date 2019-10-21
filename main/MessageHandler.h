#include <BLEDevice.h>
#include <Arduino.h>

class MessageHandler: public BLECharacteristicCallbacks {

  public:
    MessageHandler(String delimiter, String pinCode);

  private:
    String delimiter;
    String pinCode;
  
  void onWrite(BLECharacteristic *characteristic);
};
