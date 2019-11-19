#include <SparkFunSX1509.h>
#include <Constants.h>
#include <Arduino.h>

std::string getServiceResponse() {
    return "RPG Grid v1 test response";
}

std::string getServiceName() {
    return "RPG Grid v1";
}

std::string getServiceUUID() {
    return "d2007d50-6730-41c0-a871-06695ae08a55";
}

std::string getWriteCharacteristicUUID() {
    return "2be82d7d-6dd9-40ee-8ee9-af581af0fc92";
}

char getDataDelimiter() {
    return ',';
}

char getDataPinDelimiter() {
    return ':';
}

std::string getDataPin() {
    return "6969";
}

unsigned long getTransitionDurationMillis() {
    return 5000;
}

unsigned long getPulsateDurationMillis() {
    return 1000;
}

int getOutputPinMode() {
    return ANALOG_OUTPUT;
}

int getInputPinMode() {
    return INPUT;
}

int getHighPulsePower() {
    return getHighPower() / 2;
}

int getHighPower() {
    return 150;
}

int getLowPower() {
    return 0;
}
