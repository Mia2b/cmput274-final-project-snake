/////////////////////////////////////////////////////////////////////////////
// Name: Mia2b, HalloweenRalph                                             //
// ID: 0000000, 0000001                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef apples_h
#define apples_h
#include <Arduino.h>
#include "Coordinates.h"
#include "game_config.h"

/* Apple data*/
struct Apple
{
    Coordinates cord;
    uint16_t phaseShift;
};
uint8_t apples = 0;
Apple bunch[APPLE_COUNT];

#endif
