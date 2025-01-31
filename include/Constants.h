#ifndef RPG_GRID_HW_CONSTANTS_H
#define RPG_GRID_HW_CONSTANTS_H

/**
 * @return BLE response text.
 */
std::string getServiceResponse();

/**
 * @return BLE service name.
 */
std::string getServiceName();

/**
 * @return BLE service UUID.
 */
std::string getServiceUUID();

/**
 * @return BLE service write characteristic UUID (incoming messages).
 */
std::string getWriteCharacteristicUUID();

/**
 * @return delimiter for ids in BLE payloads, e.g. <code>pin:1,2,3</code>.
 */
char getDataDelimiter();

/**
 * @return delimiter for pin in BLE payloads, e.g. <code>pin:1,2,3</code>.
 */
char getDataPinDelimiter();

/**
 * @return pin value.
 */
std::string getDataPin();

/**
 * @return duration in millis for each tile state transition.
 */
unsigned long getTransitionDurationMillis();

/**
 * @return duration in millis for each tile pulse.
 */
unsigned long getPulsateDurationMillis();

/**
 * @return pin mode to be used for output.
 */
int getOutputPinMode();

/**
 * @return pin mode to be used for input.
 */
int getInputPinMode();

/**
 * @return power used when whitening out the tiles.
 */
int getWhiteoutHighPower();

/**
 * @return power used when pulsing enabled tiles.
 */
int getHighPulsePower();

/**
 * @return power used when enabling tiles.
 */
int getHighPower();

/**
 * @return power used when disabling tiles.
 */
int getLowPower();

#endif
