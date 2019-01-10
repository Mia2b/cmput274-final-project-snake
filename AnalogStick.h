/////////////////////////////////////////////////////////////////////////////
// Name: Mia2b, HalloweenRalph                                             //
// ID: 0000000, 0000001                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef AnalogStick_h
#define AnalogStick_h
#include <Arduino.h>

class AnalogStick
{
    /* The Analog Stick take the input angle and magnitude and converts it
       to a snake direction. */
    private:
        uint8_t  pinX;
        uint8_t  pinY;
        uint8_t  lastMove = 3;
        uint16_t middleX;
        uint16_t middleY;
        long deadZone = pow(64, 2);
    public:
        AnalogStick(uint8_t pinX, uint8_t pinY);
        uint8_t getDirection();
};

#endif