#include <SparkFunSX1509.h>
#include <MessageHandler.h>
#include <BLEDevice.h>
#include <BLEServer.h>

TileWriter *tileWriter = nullptr;

/**
 * @return prepared tile writer or <code>nullptr</code> on failure.
 */
TileWriter *createTileWriter() {
    auto io = new SX1509();

    if (io->begin(0x3E)) {
        auto writer = new TileWriter();

        writer->addCounterTiles(io, {4});
        writer->addPatternTiles(io, {0, 1, 2, 3});

        return writer;
    }
    return nullptr;
}

/**
 * @return prepared BLE service.
 */
BLEService *createBLEService() {
    BLEDevice::init(getServiceName());
    return BLEDevice::createServer()->createService(getServiceUUID());
}

/**
 * Listen for incoming messages on given BLE service.
 */
void setupWriteCharacteristic(BLEService *service) {
    auto writes = service->createCharacteristic(
        getWriteCharacteristicUUID(),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    writes->setCallbacks(new MessageHandler(tileWriter));
    writes->setValue(getServiceResponse());
}

/**
 * Advertise BLE.
 */
void startAdvertising() {
    auto advertising = BLEDevice::getAdvertising();

    advertising->addServiceUUID(getServiceUUID());
    advertising->setScanResponse(true);
    advertising->setMinPreferred(0x06);
    advertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();
}

void __unused setup() {
    Serial.begin(115200);

    Serial.println("Setting up Tile IO");
    tileWriter = createTileWriter();

    if (tileWriter == nullptr) {
        Serial.println("Could not setup Tile IO");
        return;
    }

    Serial.println("Creating BLE service");
    auto service = createBLEService();

    Serial.println("Setting up characteristic for writes");
    setupWriteCharacteristic(service);

    Serial.println("Starting BLE service");
    service->start();

    Serial.println("Starting advertising");
    startAdvertising();

    Serial.println("Ready");
}

void __unused loop() {
    tileWriter->update();
}
