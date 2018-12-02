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
        long deadZone = pow(64, 2);
        void Setup();
    public:
        Controller(uint8_t pinX, uint8_t pinY, uint8_t pinB);
        uint8_t getDirection();
        int getButton();
};

#endif