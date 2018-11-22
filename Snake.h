#ifndef snake_h
#define snake_h

#include "Controller.h"
#include <Arduino.h>

class Snake
{
    public:
        struct coordinates
        {
            uint8_t x;
            uint8_t y;
        };
        Snake(uint8_t x, uint8_t y);
        void update();
        coordinates getCords();
    private:
        coordinates cords;
        void move(uint8_t direction);
        void drawBody();
        Controller controller = Controller(A1,A0,13);
    
};
#endif


