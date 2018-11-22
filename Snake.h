#ifndef snake_h
#define snake_h

#include "Controller.h"
#include <Arduino.h>

class Snake
{
    private:
        uint16_t newPos;
        void move();
        void drawBody();
        Controller controller = Controller(A1,A0,13);
    public:
        Snake(uint16_t pos);
        void update();
};
#endif


