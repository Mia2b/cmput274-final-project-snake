#ifndef snake_h
#define snake_h

#include "Controller.h"
#include <Arduino.h>
#include "Crumb.h"

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
        Controller controller = Controller(A0,A1,13);
        Crumb moveHistory;
        uint16_t length;
    
};
#endif


