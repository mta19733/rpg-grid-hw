#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <TileWriter.h>
#include <BLEDevice.h>

class MessageHandler : public BLECharacteristicCallbacks {

private:
    TileWriter *tileWriter;

    /**
     * Currently parsed tile ids.
     */
    std::vector<byte> ids;

public:
    explicit MessageHandler(TileWriter *writer);

private:
    void onWrite(BLECharacteristic *characteristic) override;
};

#endif
