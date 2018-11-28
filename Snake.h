#ifndef snake_h
#define snake_h

#include "Controller.h"
#include <Arduino.h>
#include "Crumb.h"
#include "Coordinates.h"


class Snake
{
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
        Controller controller = Controller(A1,A0,13);
        Crumb moveHistory;
        uint16_t length;
        bool isAlive;
};
#endif


