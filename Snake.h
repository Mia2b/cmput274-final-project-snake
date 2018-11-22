#ifndef snake_h
#define snake_h
#include <Arduino.h>

class Snake
{
    private:
        uint16_t newPos;
        void move();
        void drawBody();
        
    public:
        Snake(uint16_t pos);
        void update();
};
#endif


