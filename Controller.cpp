#include "Controller.h"

const uint8_t UP = 0;
const uint8_t RIGHT = 1;
const uint8_t LEFT = 2;
const uint8_t DOWN = 3;

//uint8_t = lastMoves;


Controller::Controller(uint8_t pinX, uint8_t pinY, uint8_t pinB)
{
    /*Pin x and y must be analog for the joystick*/
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinB = pinB;
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinB, INPUT_PULLUP);
    middleX = analogRead(pinX);
    middleY = analogRead(pinY);
}

uint8_t Controller::getDirection()
{
    int x = analogRead(pinX) - middleX;
    int y = analogRead(pinY) - middleY;
    uint16_t mag = sqrt(x*x + y*y);
    double angle = atan(abs(x)/abs(y));
    double ideal = PI/4.0;
    Serial.println(x);
    Serial.println(y);
    Serial.println(angle);

    if ( mag < deadZone)
    {
        return lastMove;
    }
    else if ((x <= 0) && (lastMove != DOWN) && (angle > PI/ideal))
    {   // UP
        lastMove = UP;
        return UP;
    }
    else if ((y >= 0) && (lastMove != LEFT) && (angle < PI/ideal))
    {   // RIGHT
        lastMove = RIGHT;
        return RIGHT;
    }
    else if ((y <= 0) && (lastMove != RIGHT) && (angle < PI/ideal))
    {   // LEFT
        lastMove = LEFT;
        return LEFT;
    }
    else if ((x >= 0) && (lastMove != UP) && (angle > PI/ideal))
    {   // DOWN
        lastMove = DOWN;
        return DOWN;
    }
    else
    {   // NO INPUT
        return lastMove;
    }

    //The following is temp for testing
        char myChar = Serial.read();
        if ((myChar == 'w') && (lastMove != DOWN))
        {   // UP
            lastMove = UP;
            return UP;
        }
        else if ((myChar == 'd') && (lastMove != LEFT))
        {   // RIGHT
            lastMove = RIGHT;
            return RIGHT;
        }
        else if ((myChar == 'a') && (lastMove != RIGHT))
        {   // LEFT
            lastMove = LEFT;
            return LEFT;
        }
        else if ((myChar == 's') && (lastMove != UP))
        {   // DOWN
            lastMove = DOWN;
            return DOWN;
        }
        else
        {   // NO INPUT
            return lastMove;
        }
}
