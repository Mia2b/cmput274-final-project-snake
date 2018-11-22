#include "Snake.h"
#include <Arduino.h>
#include "Controller.h"

const uint8_t UP = 0;
const uint8_t RIGHT = 1;
const uint8_t LEFT = 2;
const uint8_t DOWN = 3;

Snake::Snake(uint8_t x, uint8_t y)
{
    cords.x = x;
    cords.y = y;
    history1 = 0;
    history0 = 0;
}

void Snake::update()
{
    move(controller.getDirection());
}

void Snake::move(uint8_t direction)
{
    //Serial.println(direction);
    if (direction == UP) cords.y--;
    else if (direction == RIGHT) cords.x++;
    else if (direction == LEFT) cords.x--;
    else if (direction == DOWN) cords.y++;
    //direction is two bits wide - 0,1,2,3 - store each bit in the history;
    history1 <<=1;
    history0 <<=1;
    history1 += (direction>>1)&1;
    history0 += direction&1;
}

Snake::coordinates Snake::getCords()
{
    return cords;
}

Snake::coordinates Snake::getEnd()
{
    coordinates endSeg = cords;
    for (int i = 0 ; i < length; i++)
    {
        //Serial.println(history0);
        uint8_t direction = (((history1>>(i))&1) << 1) + ((history0>>(i))&1);
        direction = (~direction)&3;
        if (direction == UP) endSeg.y--;
        else if (direction == RIGHT) endSeg.x++;
        else if (direction == LEFT) endSeg.x--;
        else if (direction == DOWN) endSeg.y++;

        if (endSeg.x == cords.x && endSeg.y == cords.y)
        {
            Serial.println("Ouch");
        }
    }
    return endSeg;
}
void Snake::drawBody()
{
    
}