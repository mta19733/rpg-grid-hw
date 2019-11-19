#ifndef RPG_GRID_HW_UTILS_H
#define RPG_GRID_HW_UTILS_H

#include <TileWriter.h>
#include <BLEService.h>

/**
 * @return prepared tile writer or <code>nullptr</code> on failure.
 */
TileWriter *createTileWriter();

/**
 * @return prepared BLE service.
 */
BLEService *createBLEService();

/**
 * Listen for incoming messages on given BLE service.
 */
void setupWriteCharacteristic(BLEService *service, TileWriter *writer);

/**
 * Advertise BLE.
 */
void startAdvertisingBLE();

#endif
