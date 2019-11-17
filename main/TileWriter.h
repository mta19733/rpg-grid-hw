#ifndef TILE_WRITER_H
#define TILE_WRITER_H

#include <SparkFunSX1509.h>

// Writes signals to IO devices.
class TileWriter {

  public:
    TileWriter(
      unsigned long transitionDurationMillis,
      int highPower,
      int lowPower
    );

    // Add a new screen to the writer with given IO pins.
    void addScreen(SX1509& io, byte counterPin, std::vector<byte> pins);

    // Set new tile ids which are to be written during each update.
    void setIds(std::vector<byte> ids);

    // Execute one update tick.
    void update();

    // Get the size of total number of tiles.
    int size();

  private:
    struct Tile {

      // Which SX is this tile connected to.
      SX1509& io;

      // Pin which this tile is using.
      const byte pin;
    };

    // Duration of each transition.
    const unsigned long transitionDurationMillis;

    // When does the current transition end.
    unsigned long transitionEndMillis = 0;

    // Analog power which is used when enabling tiles.
    const int highPower;

    // Analog power which is used when disabling tiles.
    const int lowPower;

    // All connected tiles.
    std::vector<Tile> tiles;

    // All counterbalances of connected tiles.
    std::vector<Tile> counterTiles;

    // Tiles which are currently being displayed.
    std::vector<Tile> currentTiles;
};

#endif
