#ifndef Controller_h
#define Controller_h
#include <Arduino.h>

class Controller
{
    private:
        uint8_t  pinX;
        uint8_t  pinY;
        uint8_t  pinB;
        uint8_t  lastMove = 3;
        uint16_t middleX;
        uint16_t middleY;
        long deadZone = pow(128, 2);
    public:
        Controller(uint8_t pinX, uint8_t pinY, uint8_t pinB);
        uint8_t getDirection();
};

#endif