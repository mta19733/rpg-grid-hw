#include "TileWriter.h"

TileWriter::TileWriter(
  unsigned long transitionDurationMillis,
  int highPower,
  int lowPower
) : transitionDurationMillis(transitionDurationMillis),
  highPower(highPower),
  lowPower(lowPower) { }

void TileWriter::addScreen(SX1509& io, byte counterPin, std::vector<byte> pins) {
  this->counterTiles.push_back({io, counterPin});
  io.pinMode(counterPin, ANALOG_OUTPUT);

  for (auto pin : pins) {
    this->tiles.push_back({io, pin});
    io.pinMode(pin, ANALOG_OUTPUT);
  }
}

void TileWriter::setIds(std::vector<byte> ids) {
  this->trasitionEndMillis = millis() + this->transitionDurationMillis;
  this->currentTiles.clear();

  for (auto id : ids) {
    if (0 > id || this->tiles.size() <= id) {
      Serial.printf("Invalid tile id: %d\n", id);
      continue;
    }

    this->currentTiles.push_back(
      this->tiles[id]
    );
  }
}

void TileWriter::update() {
  if (transitionEndMillis < millis()) {
    Serial.println("Transition ended");
    // TODO implement transition handling.
  }

  for (tile : this->currentTiles) {
    tile.io.analogWrite(tile.pin, this->highPower);
  }

  for (tile : this->counterTiles) {
    tile.io.analogWrite(tile.pin, this->lowPower);
  }
}

int TileWriter::size() {
  return this->tiles.size();
}
