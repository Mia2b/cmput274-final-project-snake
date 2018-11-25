#ifndef apples_h
#define apples_h

#include "Arduino.h"
#include "Snake.h"

class apples {
    
    public:

        struct Coord {
            uint8_t aX;
            uint8_t aY;
        };

        void makeCoord(uint8_t screenWidth, uint8_t screenLength);
        Coord appleMake();
        bool appleCheck();

    private:

        Coord appleCurrent;

}

#endif
