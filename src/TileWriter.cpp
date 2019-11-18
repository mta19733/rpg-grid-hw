#include "TileWriter.h"
#include "Constants.h"

void TileWriter::reloadCurrentTiles(const std::vector<byte> &ids) {
    this->currentTiles.clear();

    for (auto id : ids) {
        if (0 > id || this->patternTiles.size() <= id) {
            Serial.printf("Invalid tile id: %d\n", id);
            continue;
        }

        this->currentTiles.push_back(
            this->patternTiles[id]
        );
    }

    state = State::PENDING;
}

void TileWriter::addCounterTiles(SX1509 *io, const std::vector<byte> &pins) {
    for (auto pin : pins) {
        this->counterTiles.push_back({io, pin});
        io->pinMode(pin, ANALOG_OUTPUT);
    }
}

void TileWriter::addTiles(SX1509 *io, const std::vector<byte> &pins) {
    for (auto pin : pins) {
        this->patternTiles.push_back({io, pin});
        io->pinMode(pin, ANALOG_OUTPUT);
    }
}

void TileWriter::update() {
    if (State::IDLE != state && this->transitionEndMillis < millis()) {
        nextState();
    }

    switch (state) {
        case State::PENDING:
            break;

        case State::WHITEOUT:
            write(this->patternTiles, getAnalogLowPower());
            write(this->counterTiles, getAnalogHighPower());
            break;

        case State::ENABLE:
            write(this->currentTiles, getAnalogHighPower());
            write(this->counterTiles, getAnalogLowPower());
            break;

        case State::IDLE:
            for (auto tile : patternTiles) {
                tile.io->pinMode(tile.pin, INPUT);
            }

            for (auto tile : counterTiles) {
                tile.io->pinMode(tile.pin, INPUT);
            }
            break;
    }
}

int TileWriter::size() {
    return this->patternTiles.size();
}

void TileWriter::nextState() {
    this->transitionEndMillis = millis() + getTransitionDurationMillis();
    this->state = static_cast<State>(
        (static_cast<int>(state) + 1) % (static_cast<int>(State::IDLE) + 1)
    );

    Serial.println(
        getDescription(this->state).c_str()
    );
}

std::string TileWriter::getDescription(TileWriter::State state) {
    switch (state) {
        case State::PENDING:
            return "Waiting for next state";
        case State::WHITEOUT:
            return "Cleaning all tiles";
        case State::ENABLE:
            return "Enabling current tiles";
        case State::IDLE:
            return "Keeping current tiles lit";
        default:
            return "Unknown";
    }
}

void TileWriter::pulsate(const std::vector<Tile> &tiles, int power) {
    if (this->pulsateEndMillis < millis()) {
        this->pulsateEndMillis = millis() + getPulsateDurationMillis();
    } else {
        for (auto tile : tiles) {
            tile.io->analogWrite(tile.pin, power);
        }
    }
}

void TileWriter::write(const std::vector<Tile> &tiles, int power) {
    for (auto tile : tiles) {
        tile.io->pinMode(tile.pin, ANALOG_OUTPUT);
        tile.io->analogWrite(tile.pin, power);
    }
}
