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
     
}

Snake::coordinates Snake::getCords()
{
    return cords;
}

void Snake::drawBody()
{
    
}