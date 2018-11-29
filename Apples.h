#ifndef apples_h
#define apples_h
#include <Arduino.h>
#include "Coordinates.h"
#include "game_config.h"

struct Apple
{
    Coordinates cord;
    uint16_t phaseShift;
};
uint8_t apples = 0;
Apple bunch[APPLE_COUNT];

#endif
