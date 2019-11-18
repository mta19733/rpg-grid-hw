#ifndef TILE_WRITER_H
#define TILE_WRITER_H

#include <SparkFunSX1509.h>
#include <Constants.h>

class TileWriter {

private:
    enum class State {

        /**
         * Ready to switch to another state. Intermediate state.
         */
        PENDING,

        /**
         * Clean all the tiles.
         */
        WHITEOUT,

        /**
         * Enable current pattern tiles.
         */
        PATTERN,

        /**
         * Pulse currently enabled tiles.
         */
        PULSE
    };

    struct Tile {

        /**
         * IO to which the tiles pin is connected to.
         */
        SX1509 *io;

        /**
         * Tiles pin.
         */
        const byte pin;
    };

    /**
     * All available pattern tiles.
     */
    std::vector<Tile> patternTiles;

    /**
     * Currently lit pattern tiles.
     */
    std::vector<Tile> currentTiles;

    /**
     * All available counterbalance "tiles".
     */
    std::vector<Tile> counterTiles;

    /**
     * Current state of the entire gird.
     */
    State state = State::PULSE;

    /**
     * When current transition should end.
     */
    unsigned long transitionEndMillis = 0;

    /**
     * When pulsing should end.
     */
    unsigned long pulsateEndMillis = 0;

    /**
     * Should the grid pulsate.
     */
    bool pulsate = false;

public:

    /**
     * Reload the write to use new tile ids.
     */
    void reloadCurrentTiles(const std::vector<byte> &ids);

    /**
     * Add a set of counterbalance tiles.
     */
    void addCounterTiles(SX1509 *io, const std::vector<byte> &pins);

    /**
     * Add a set of regular tiles.
     */
    void addPatternTiles(SX1509 *io, const std::vector<byte> &pins);

    /**
     * Execute one update tick.
     */
    void update();

    /**
     * @return number of total tiles.
     */
    int size();

private:

    /**
     * Switch the writer to next state.
     */
    void nextState();

    /**
     * @return returns a friendly description of given state.
     */
    static std::string getDescription(State state);

    /**
     * Set pin mode of given tiles.
     */
    static void setPinMode(const std::vector<Tile> &tiles, int mode);

    /**
     * Send power to given tiles.
     */
    static void writeTiles(const std::vector<Tile> &tiles, int power);
};

#endif
