#include <Utils.h>
#include <BLEDevice.h>
#include <MessageHandler.h>

TileWriter *createTileWriter() {
    std::vector<int> i2cAddresses = {0x3E, 0x71, 0x3F};

    std::vector<byte> patternTilePins = {0, 1, 4, 5, 8, 9, 2, 3, 6, 7, 10, 11};
    std::vector<byte> counterTilePins = {12, 13, 14};

    auto writer = new TileWriter();
    for (size_t i = 0; i < i2cAddresses.size(); i++) {
        auto address = i2cAddresses[i];
        auto io = new SX1509();

        if (io->begin(address)) {
            writer->addPatternTiles(io, patternTilePins);
            writer->addCounterTiles(io, counterTilePins);
        } else {
            Serial.printf(
                "SX with address %d at position %d is malfunctioning\n",
                address,
                i
            );

            return nullptr;
        }
    }
    return writer;
}

BLEService *createBLEService() {
    BLEDevice::init(getServiceName());
    return BLEDevice::createServer()->createService(getServiceUUID());
}

void setupWriteCharacteristic(BLEService *service, TileWriter *writer) {
    auto writes = service->createCharacteristic(
        getWriteCharacteristicUUID(),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    writes->setCallbacks(new MessageHandler(writer));
    writes->setValue(getServiceResponse());
}

void startAdvertisingBLE() {
    auto advertising = BLEDevice::getAdvertising();

    advertising->addServiceUUID(getServiceUUID());
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);
    advertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();
}
