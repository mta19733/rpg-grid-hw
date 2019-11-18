#ifndef TILE_WRITER_H
#define TILE_WRITER_H

#include <SparkFunSX1509.h>

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
         * Enable current tiles.
         */
        ENABLE,

        /**
         * Do nothing.
         */
        IDLE
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
    State state = State::IDLE;

    /**
     * When current transition should end.
     */
    unsigned long transitionEndMillis = 0;

    /**
     * When pulsing should end.
     */
    unsigned long pulsateEndMillis = 0;

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
    void addTiles(SX1509 *io, const std::vector<byte> &pins);

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
     * Pulsate currently enabled tiles.
     */
    void pulsate(const std::vector<Tile> &tiles, int power);

    /**
     * @return returns a friendly description of given state.
     */
    static std::string getDescription(State state);

    /**
     * Write given tiles.
     */
    static void write(const std::vector<Tile> &tiles, int power);
};

#endif
