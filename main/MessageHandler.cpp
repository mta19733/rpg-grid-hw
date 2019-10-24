#include <Arduino.h>

#include "MessageHandler.h"

MessageHandler::MessageHandler(
  int maxTileIds,
  std::string dataDelimiter,
  std::string pinDelimiter,
  std::string pin
) : maxTileIds(maxTileIds),
  dataDelimiter(dataDelimiter),
  pinDelimiter(pinDelimiter),
  pin(pin),
  tileIds(maxTileIds) { };

void MessageHandler::onWrite(BLECharacteristic *characteristic) {
  std::string value = characteristic->getValue();

  if (!this->isPinValid(value)) {
    Serial.printf("Invalid pin for: %s\n", value.c_str());
    return;
  }

  parseTileIds(value);
  printTileIds();

  // TODO, send signals to Serial ports by using tileIds.
}

bool MessageHandler::isPinValid(std::string pin) {
  std::size_t idx = pin.find(this->pinDelimiter);
  if (idx == std::string::npos) {
    return false;
  }
  return this->pin == pin.substr(0, idx);
}

void MessageHandler::parseTileIds(std::string value) {
  this->tileIds.clear();

  std::size_t idx = value.find(this->pinDelimiter);
  if (idx == std::string::npos) {
    return;
  }

  // strtok doesn't accept strings, so &x[0] is used to convert it to char*.
  char* data = &value.substr(idx + 1, value.length())[0];
  char* tok = strtok(data, this->dataDelimiter.c_str());

  // Size restriction is added in-case of malformed message - it might 
  // crash due to OOM.
  while (tok != NULL && this->tileIds.size() < this->maxTileIds) {
    this->tileIds.push_back(atoi(tok));

    tok = strtok(NULL, this->dataDelimiter.c_str());
  }
}

void MessageHandler::printTileIds() {
  Serial.print("Ids:");
  for (int i = 0; i < this->tileIds.size(); i++) {
    Serial.printf(" %d", this->tileIds[i]);
  }
  Serial.println();
}
