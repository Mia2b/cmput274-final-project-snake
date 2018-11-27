#include "Snake.h"
#include <Arduino.h>
#include "Controller.h"
#include "Crumb.h"

const uint8_t UP = 0;
const uint8_t RIGHT = 1;
const uint8_t LEFT = 2;
const uint8_t DOWN = 3;

Snake::Snake(uint8_t x, uint8_t y, uint16_t w, uint16_t h)
{
    cords.x = x;
    cords.y = y;
    length = 250;
    moveHistory.setLength(length+1);
}

void Snake::update()
{
    move(controller.getDirection());
}

void Snake::move(uint8_t direction)
{
    Serial.println(direction);
    if (direction == UP) cords.y--;
    else if (direction == RIGHT) cords.x++;
    else if (direction == LEFT) cords.x--;
    else if (direction == DOWN) cords.y++;
    //direction is two bits wide - 0,1,2,3 - store each bit in the history;
    moveHistory.insert(direction);
}

Snake::coordinates Snake::getCords()
{
    return cords;
}

Snake::coordinates Snake::getEnd()
{
    coordinates endSeg = cords;
    for (uint16_t i = 0 ; i < length; i++)
    {
        //Serial.println(history0);
        uint8_t direction = moveHistory.getMove(i)^3;
        if (direction == UP) endSeg.y--;
        else if (direction == RIGHT) endSeg.x++;
        else if (direction == LEFT) endSeg.x--;
        else if (direction == DOWN) endSeg.y++;
    }
    return endSeg;
}

bool Snake::isInHistory(uint16_t x, uint16_t y)
{
    coordinates seg = cords;
    for (uint16_t i = 0 ; i < length; i++)
    {
        uint8_t direction = moveHistory.getMove(i)^3;
        if (direction == UP) seg.y--;
        else if (direction == RIGHT) seg.x++;
        else if (direction == LEFT) seg.x--;
        else if (direction == DOWN) seg.y++;
        if(seg.x == x && seg.y == y)
        {
            return true;
        }
    }
    return false;
}