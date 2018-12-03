#include "Snake.h"
#include <Arduino.h>
#include "AnalogStick.h"
#include "Crumb.h"

/*  These directions are used becuse the XOR of them gives the optosite 
    direction. */
const uint8_t UP = 0;    // 00
const uint8_t RIGHT = 1; // 01
const uint8_t LEFT = 2;  // 10
const uint8_t DOWN = 3;  // 11

Snake::Snake(uint8_t x, uint8_t y, uint16_t startLen)
{
    /* Initialized the snake starting position... */
    cords.x = x;
    cords.y = y;
    /* ...Length...*/
    length = startLen;
    /* ... and some variables used for checks.*/
    isAlive = true;
    hasGrown = true;
    moveHistory.setLength(length + 1);
}

bool Snake::lives()
{
    /* Get if the snake is living */
    return isAlive;
}

void Snake::kill()
{
    /* Allows things to kill the snake */
    isAlive = false;
}

void Snake::update()
{
    /* Called every game cycle */
    move(controller.getDirection()); // The snake is always moving.
}

void Snake::grow(uint16_t growLength)
{
    /* Increase the length of the snake by a specified amount */
    length += growLength;
    hasGrown = true;
    moveHistory.setLength(length + 1);
}

void Snake::shrink(uint16_t shrinkLength)
{
    /* Basicaly the reverse of grow */
    length -= shrinkLength;
    hasGrown = true;
    moveHistory.setLength(length + 1);
}

uint16_t Snake::getLength()
{
    /* Get the snake length */
    return length;
}

void Snake::move(uint8_t direction)
{
    /* Get the direction to move from the Analog Stick*/
    if (direction == UP)
        cords.y--;
    else if (direction == RIGHT)
        cords.x++;
    else if (direction == LEFT)
        cords.x--;
    else if (direction == DOWN)
        cords.y++;
    /*  direction is two bits wide - 0,1,2,3, insert them into the history 
        so that we may retrace our steps to find the end of the snake */
    moveHistory.insert(direction);
}

Coordinates Snake::getCords()
{
    /* Returns the snake current possition */
    return cords;
}

Coordinates Snake::getEnd()
{
    Coordinates endSeg;
    if (hasGrown)
    { /* If the snake has grown, retrace the snakes crumb trail*/
        endSeg = cords;
        for (uint16_t i = 0; i < length; i++)
        {
            uint8_t direction = moveHistory.getMove(i) ^ 3;
            if (direction == UP)
                endSeg.y--;
            else if (direction == RIGHT)
                endSeg.x++;
            else if (direction == LEFT)
                endSeg.x--;
            else if (direction == DOWN)
                endSeg.y++;
        }
        hasGrown = false;
    }
    else
    {
        /*  If the snake hasnt grown we can just use the length index
            To find where the next end segment should be.   */
        endSeg = lastEnd;
        uint8_t direction = moveHistory.getMove(length);
        if (direction == UP)
            endSeg.y--;
        else if (direction == RIGHT)
            endSeg.x++;
        else if (direction == LEFT)
            endSeg.x--;
        else if (direction == DOWN)
            endSeg.y++;
    }
    lastEnd = endSeg;
    return endSeg;
}