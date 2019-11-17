#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <BLEDevice.h>

#include "TileWriter.h"

class MessageHandler: public BLECharacteristicCallbacks {

  public:
    MessageHandler(
      std::string dataDelimiter,
      std::string pinDelimiter,
      std::string pin,
      TileWriter& writer
    );

  private:

    // Delimiter between ids.
    std::string dataDelimiter;

    // Delimiter between pin code and the message payload.
    std::string pinDelimiter;

    // Pin code.
    std::string pin;

    // IO handler.
    TileWriter& writer;

    // Currently parsed tile ids.
    std::vector<byte> tileIds;

    // Handle BLE writes.
    void onWrite(BLECharacteristic *characteristic);

    // Check if given pin code is valid.
    bool isPinValid(std::string pin);

    // Parse tile ids from raw string value.
    void parseTileIds(std::string value);

    // Print currently parsed ids.
    void printTileIds();
};

#endif
