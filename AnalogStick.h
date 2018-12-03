#ifndef AnalogStick_h
#define AnalogStick_h
#include <Arduino.h>

class AnalogStick
{
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