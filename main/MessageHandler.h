#include <BLEDevice.h>

class MessageHandler: public BLECharacteristicCallbacks {

  public:
    MessageHandler(
      int maxTileIds, 
      std::string dataDelimiter, 
      std::string pinDelimiter,
      std::string pin
    );

  private:
    int maxTileIds;
  
    std::string dataDelimiter;
    std::string pinDelimiter;
    std::string pin;
  
    std::vector<int> tileIds;

    /**
     * Handle BLE writes.
     */
    void onWrite(BLECharacteristic *characteristic);

    /**
     * Check if given pin is valid.
     */
    bool isPinValid(std::string pin);

    /**
     * Parse tile ids from given value.
     */
    void parseTileIds(std::string value);

    /**
     * Print current tile id set.
     */
    void printTileIds();
};
