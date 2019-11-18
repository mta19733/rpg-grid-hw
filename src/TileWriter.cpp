#include <TileWriter.h>
#include <sstream>

/**
 * @return returns a friendly description of given pin mode.
 */
std::string getPinModeDescription(int mode) {
    if (getOutputPinMode() == mode) {
        return "output";
    } else if (getInputPinMode() == mode) {
        return "input";
    } else {
        std::ostringstream stream;
        stream << mode;
        return stream.str();
    }
}

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
    }
}

void TileWriter::addPatternTiles(SX1509 *io, const std::vector<byte> &pins) {
    for (auto pin : pins) {
        this->patternTiles.push_back({io, pin});
    }
}

void TileWriter::update() {
    auto now = millis();
    if (State::PULSE != state && this->transitionEndMillis < now) {
        nextState();
    }

    switch (state) {
        case State::PENDING:
            break;

        case State::WHITEOUT:
            writeTiles(this->patternTiles, getLowPower());
            writeTiles(this->counterTiles, getHighPower());
            break;

        case State::PATTERN:
            writeTiles(this->currentTiles, getHighPower());
            writeTiles(this->counterTiles, getLowPower());
            break;

        case State::PULSE:
            if (this->pulsateEndMillis < now) {
                this->pulsateEndMillis = now + getPulsateDurationMillis();
                this->pulsate = !this->pulsate;

                setPinMode(
                    this->currentTiles,
                    this->pulsate ? getOutputPinMode() : getInputPinMode()
                );

                setPinMode(
                    this->counterTiles,
                    this->pulsate ? getOutputPinMode() : getInputPinMode()
                );
            }

            if (this->pulsate) {
                writeTiles(this->currentTiles, getHighPulsePower());
                writeTiles(this->counterTiles, getLowPower());
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
        (static_cast<int>(state) + 1) % (static_cast<int>(State::PULSE) + 1)
    );

    switch (this->state) {
        case State::PENDING:
            break;

        case State::WHITEOUT:
            setPinMode(this->patternTiles, getOutputPinMode());
            setPinMode(this->counterTiles, getOutputPinMode());
            break;

        case State::PATTERN:
            setPinMode(this->currentTiles, getOutputPinMode());
            setPinMode(this->counterTiles, getOutputPinMode());
            break;

        case State::PULSE:
            setPinMode(this->patternTiles, getInputPinMode());
            setPinMode(this->counterTiles, getInputPinMode());
            break;
    }

    Serial.println(
        getDescription(this->state).c_str()
    );
}

std::string TileWriter::getDescription(TileWriter::State state) {
    switch (state) {
        case State::PENDING:
            return "Waiting for next state";
        case State::WHITEOUT:
            return "Cleaning up all tiles";
        case State::PATTERN:
            return "Enabling current tiles";
        case State::PULSE:
            return "Keeping current tiles lit by pulsing";
        default:
            return "Unknown";
    }
}

void TileWriter::setPinMode(const std::vector<Tile> &tiles, int mode) {
    Serial.print("Setting pin mode of:");
    for (auto tile : tiles) {
        tile.io->pinMode(tile.pin, mode);
        Serial.printf(" %d", tile.pin);
    }

    Serial.printf(
        " to %s\n",
        getPinModeDescription(mode).c_str()
    );
}

void TileWriter::writeTiles(const std::vector<Tile> &tiles, int power) {
    for (auto tile : tiles) {
        tile.io->analogWrite(tile.pin, power);
    }
}
