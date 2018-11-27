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
    Serial.println("x");
    Serial.println(x);
    Serial.println("y");
    Serial.println(y);
    double mag = pow((pow(x, 2) + pow(y, 2)), 0.5);
    float angle;
    angle = atan2(-y,x)*(180.0/PI);

    char c;
    Serial.println("Mag");
    Serial.println(mag);

    if ( mag < int(deadZone))
    {
        Serial.println("Dead");
        return lastMove;
    }
    else if ((lastMove != DOWN) && (angle >= 45 && angle <= 135))
    {   // UP
        lastMove = UP;
        return UP;
    }
    else if ((lastMove != LEFT) && (angle <= 45 && angle >= -45))
    {   // RIGHT
        lastMove = RIGHT;
        return RIGHT;
    }
    else if ((lastMove != RIGHT) && (angle >= 135 || angle <= -135))
    {   // LEFT
        lastMove = LEFT;
        return LEFT;
    }
    else if ((lastMove != UP) && (angle >= -135 && angle <= -45))
    {   // DOWN
        lastMove = DOWN;
        return DOWN;
    }
    else
    {   // NO INPUT
        return lastMove;
    }

   /*
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
    */
}
