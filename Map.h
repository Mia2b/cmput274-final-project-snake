#ifndef Map_h
#define Map_h
#include <Arduino.h>
#include "game_config.h"

class Map
{
    public:
        Map();
        void addMark(uint8_t x, uint8_t y);
        void removeMark(uint8_t x, uint8_t y);
        bool isMarked(uint8_t x, uint8_t y);
        bool isOutOfBounds(uint8_t x, uint8_t y);
    private:
        uint64_t grid[X_BOUND];
        uint64_t mask;
};

#endif