#include "MessageHandler.h"

MessageHandler::MessageHandler(String delimiter, String pinCode) {
  this->delimiter = delimiter;
  this->pinCode = pinCode;
}

void MessageHandler::onWrite(BLECharacteristic *characteristic) {
  String value = characteristic->getValue().c_str();

  int idx = value.indexOf(this->delimiter);
  if (idx == -1) {
    Serial.printf("Invalid value: %s\n", value);
  } else {
    String pinCode = value.substring(0, idx);
    String data = value.substring(idx + 1, value.length());

    if (this->pinCode.equals(pinCode)) {
      Serial.printf("Received data: %s\n", data);
    } else {
      Serial.printf("Invalid pin code: %s\n", pinCode);
    }
  }
}
