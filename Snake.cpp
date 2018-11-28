#include "Snake.h"
#include <Arduino.h>
#include "Controller.h"
#include "Crumb.h"

const uint8_t UP = 0;
const uint8_t RIGHT = 1;
const uint8_t LEFT = 2;
const uint8_t DOWN = 3;

Snake::Snake(uint8_t x, uint8_t y, uint16_t startLen)
{
    cords.x = x;
    cords.y = y;
    length = startLen;
    isAlive = true;
    hasGrown = true;
    moveHistory.setLength(length+1);
}

bool Snake::lives()
{
    return isAlive;
}

void Snake::kill()
{
    isAlive = false;
}

void Snake::update()
{
    move(controller.getDirection());
}

void Snake::grow(uint16_t growLength)
{
    length+= growLength;
    hasGrown = true;
    moveHistory.setLength(length+1);
}

void Snake::shrink(uint16_t shrinkLength)
{
    length-= shrinkLength;
    hasGrown = true;
    moveHistory.setLength(length+1);
}

uint16_t Snake::getLength()
{
    return length;
}

void Snake::move(uint8_t direction)
{
    if (direction == UP) cords.y--;
    else if (direction == RIGHT) cords.x++;
    else if (direction == LEFT) cords.x--;
    else if (direction == DOWN) cords.y++;
    //direction is two bits wide - 0,1,2,3 - store each bit in the history;
    moveHistory.insert(direction);
}

Coordinates Snake::getCords()
{
    return cords;
}

Coordinates Snake::getEnd()
{
    Coordinates endSeg;
    if (hasGrown)
    {
        endSeg = cords;
        for (uint16_t i = 0 ; i < length; i++)
        {
            //Serial.println(history0);
            uint8_t direction = moveHistory.getMove(i)^3;
            if (direction == UP) endSeg.y--;
            else if (direction == RIGHT) endSeg.x++;
            else if (direction == LEFT) endSeg.x--;
            else if (direction == DOWN) endSeg.y++;
        }
        hasGrown = false;
    }
    else
    {
        endSeg = lastEnd;
        uint8_t direction = moveHistory.getMove(length);
        if (direction == UP) endSeg.y--;
            else if (direction == RIGHT) endSeg.x++;
            else if (direction == LEFT) endSeg.x--;
            else if (direction == DOWN) endSeg.y++;
    }
    lastEnd = endSeg;
    return endSeg;
}