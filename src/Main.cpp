#include <Utils.h>

TileWriter *writer = nullptr;

void __unused setup() {
    Serial.begin(115200);

    Serial.println("Creating up tile writer");
    writer = createTileWriter();

    if (writer == nullptr) {
        Serial.println("Could not create tile writer");
        return;
    }

    Serial.println("Creating BLE service");
    auto service = createBLEService();

    Serial.println("Setting up characteristic for writes");
    setupWriteCharacteristic(service, writer);

    Serial.println("Starting BLE service");
    service->start();

    Serial.println("Starting advertising");
    startAdvertisingBLE();

    Serial.println("Ready");
}

void __unused loop() {
    writer->update();
}
