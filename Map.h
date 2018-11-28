#ifndef Map_h
#define Map_h
#include <Arduino.h>
#include "game_config.h"
#include "Coordinates.h"

class Map
{
    public:
        Map();
        void addMark(Coordinates cord);
        void removeMark(Coordinates cord);
        bool isMarked(Coordinates cord);
        bool isOutOfBounds(Coordinates cord);
    private:
        uint64_t grid[X_BOUND];
        uint64_t mask;
};

#endif