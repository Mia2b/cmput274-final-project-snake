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
        coordinates getEnd();
    private:
        coordinates cords;
        void move(uint8_t direction);
        void drawBody();
        Controller controller = Controller(A1,A0,13);
        uint64_t history0;
        uint64_t history1;
        uint16_t length = 60;
    
};
#endif


