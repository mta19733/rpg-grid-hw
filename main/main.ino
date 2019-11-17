#include <SparkFunSX1509.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "TileWriter.h"
#include "MessageHandler.h"

const std::string UUID_SERVICE              = "d2007d50-6730-41c0-a871-06695ae08a55";
const std::string UUID_WRITE_CHARACTERISTIC = "2be82d7d-6dd9-40ee-8ee9-af581af0fc92";

const std::string SERVICE_NAME           = "RPG Grid";
const std::string SERVICE_RESPONSE_VALUE = "RPG Grid test response";

const std::string DATA_DELIMITER     = ",";
const std::string DATA_PIN_DELIMITER = ":";
const std::string DATA_PIN           = "6969";

const unsigned long TRANSITION_DURATION_MILLIS = 3000;

const int HIGH_ANALOG_POWER = 100;
const int LOW_ANALOG_POWER = 0;

TileWriter writer = TileWriter(
  TRANSITION_DURATION_MILLIS,
  HIGH_ANALOG_POWER,
  LOW_ANALOG_POWER
);

// Setup IO for all connected tiles.
void setupTileIo() {
  SX1509 io;

  if (io.begin(0x3E)) {
    writer.addScreen(io, 4, {0, 1, 2, 3}); 
  } else {
    Serial.println("Could not setup IO");
  }
}

// Setup BLE service
BLEService* createBluetoothService() {
  BLEDevice::init(SERVICE_NAME);
  BLEServer* server = BLEDevice::createServer();

  return server->createService(UUID_SERVICE);
}

// Setup listen for incoming BLE messages.
void setupWriteCharacteristic(BLEService* service) {
  BLECharacteristic* writes = service->createCharacteristic(
    UUID_WRITE_CHARACTERISTIC,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );

  writes->setCallbacks(
    new MessageHandler(
      DATA_DELIMITER,
      DATA_PIN_DELIMITER,
      DATA_PIN,
      writer
    )
  );

  writes->setValue(SERVICE_RESPONSE_VALUE);
}

// Setup BLE advertising so that other devices could pick it up.
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

  Serial.println("Setting up Tile IO");
  setupTileIo();

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
  writer.update();
}
