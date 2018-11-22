#include "Controller.h"
#include <Arduino.h>

#define UP 0;
#define RIGHT 1;
#define LEFT 2;
#define DOWN 3;

//uint8_t = lastMoves;


Controller::Controller(uint8_t pinX, uint8_t pinY, uint8_t pinB)
{
    /*Pin x and y must be analog for the joystick*/
    this.pinX = pinX;
    this.pinY = pinY;
    this.pinB = pinB;
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinB, INPUT_PULLUP);
    middleX = analogRead(pinX);
    middleY = analogRead(pinY);
}

uint8_t Controller::getDirection()
{
    int x = analogRead(pinX);
    int y = analogRead(pinY);
    
}