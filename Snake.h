/////////////////////////////////////////////////////////////////////////////
// Name: Mia2b, HalloweenRalph                                             //
// ID: 0000000, 0000001                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef snake_h
#define snake_h

#include "AnalogStick.h"
#include <Arduino.h>
#include "Crumb.h"
#include "Coordinates.h"

class Snake
{
    /* A snake object can change length and is controlled by the player */
  public:
    Snake(uint8_t x, uint8_t y, uint16_t startLen);
    void update();
    Coordinates getCords();
    Coordinates getEnd();
    bool lives();
    void kill();
    void grow(uint16_t growLength);
    void shrink(uint16_t shrinkLength);
    uint16_t getLength();

  private:
    Coordinates cords;
    Coordinates lastEnd;
    bool hasGrown;
    void move(uint8_t direction);
    AnalogStick controller = AnalogStick(A1, A0);
    Crumb moveHistory;
    uint16_t length;
    bool isAlive;
};
#endif
