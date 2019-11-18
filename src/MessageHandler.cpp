#include <Arduino.h>
#include <sstream>

#include "MessageHandler.h"
#include "Constants.h"

/**
 * @return returns <code>true</code> if given pin is valid or
 * <code>false</code> otherwise.
 */
bool isPinValid(const std::string &pin) {
    auto idx = pin.find(getDataPinDelimiter());
    if (idx == std::string::npos) {
        return false;
    }
    return getDataPin() == pin.substr(0, idx);
}

/**
 * Parse tile ids into result from raw string value.
 */
void parseTileIds(
    std::vector<byte> &result,
    const std::string &value,
    int limit
) {
    result.clear();

    auto idx = value.find(getDataPinDelimiter());
    if (idx == std::string::npos) {
        return;
    }

    std::stringstream stream(
        value.substr(idx + 1, value.length())
    );

    int id;
    while (stream >> id && result.size() < limit) {
        result.push_back(id);
        if (stream.peek() == getDataDelimiter()) {
            stream.ignore();
        }
    }
}

/**
 * Print given id vector.
 */
void printIds(const std::vector<byte> &ids) {
    if (ids.empty()) {
        Serial.println("Empty ids");
    } else {
        Serial.print("Ids:");
        for (auto id : ids) {
            Serial.printf(" %d", id);
        }
        Serial.println();
    }
}

MessageHandler::MessageHandler(TileWriter *writer) : tileWriter(writer) {}

void MessageHandler::onWrite(BLECharacteristic *characteristic) {
    auto value = characteristic->getValue();

    if (!isPinValid(value)) {
        Serial.printf("Invalid pin for: %s\n", value.c_str());
        return;
    }

    parseTileIds(this->ids, value, this->tileWriter->size());
    printIds(this->ids);

    this->tileWriter->reloadCurrentTiles(ids);
}
