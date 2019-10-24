#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "MessageHandler.h"

#define UUID_SERVICE              "d2007d50-6730-41c0-a871-06695ae08a55"
#define UUID_WRITE_CHARACTERISTIC "2be82d7d-6dd9-40ee-8ee9-af581af0fc92"

#define SERVICE_NAME           "RPG Grid"
#define SERVICE_RESPONSE_VALUE "RPG Grid test response"

#define DATA_DELIMITER     ","
#define DATA_PIN_DELIMITER ":"
#define DATA_PIN           "6969"

#define MAX_TILES 8 * 8

/**
 * Setup BLE service.
 */
BLEService* createBluetoothService() {
  BLEDevice::init(SERVICE_NAME);
  BLEServer* server = BLEDevice::createServer();

  return server->createService(UUID_SERVICE);
}

/**
 * Listen for incoming write messages (id parsing).
 */
void setupWriteCharacteristic(BLEService* service) {
  BLECharacteristic* writes = service->createCharacteristic(
    UUID_WRITE_CHARACTERISTIC,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );

  writes->setCallbacks(
    new MessageHandler(
      MAX_TILES,
      DATA_DELIMITER,
      DATA_PIN_DELIMITER,
      DATA_PIN
    )
  );

  writes->setValue(SERVICE_RESPONSE_VALUE);
}

/**
 * Advertise BLE so that other devices could pick up ESP.
 */
void startAdvertising() {
  BLEAdvertising* advertising = BLEDevice::getAdvertising();

  advertising->addServiceUUID(UUID_SERVICE);

  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);
  advertising->setMinPreferred(0x12);

  BLEDevice::startAdvertising();
}

void setup() {
  Serial.begin(115200);

  Serial.println("Creating Bluetooth service");
  BLEService* service = createBluetoothService();

  Serial.println("Setting up characteristic for writes");
  setupWriteCharacteristic(service);

  Serial.println("Starting Bluetooth service");
  service->start();

  Serial.println("Starting advertising");
  startAdvertising();

  Serial.println("Ready");
}

void loop() {
  delay(2000);
}
