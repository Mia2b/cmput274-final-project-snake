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
        Snake(uint8_t x, uint8_t y, uint16_t w, uint16_t h);
        void update();
        coordinates getCords();
        coordinates getEnd();
        bool isInHistory(uint16_t x, uint16_t y);
    private:
        coordinates cords;
        void move(uint8_t direction);
        Controller controller = Controller(A1,A0,13);
        uint64_t history0;
        uint64_t history1;
        uint16_t length;
    
};
#endif


