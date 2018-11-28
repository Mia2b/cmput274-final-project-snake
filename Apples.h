#ifndef apples_h
#define apples_h
#include <Arduino.h>
#include "Coordinates.h"

class Apples
{
    public:
        Apples();
        Coordinates location;
        uint8_t eatLocation(Coordinates cord);
    private:
};

#endif
