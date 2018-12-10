/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef Map_h
#define Map_h
#include <Arduino.h>
#include "game_config.h"
#include "Coordinates.h"

class Map
{
    /* A map object the allows for storing binary states of coordinates in a
    memory efficient way. */
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