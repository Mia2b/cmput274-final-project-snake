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
    int x = analogRead(pinX);
    int y = analogRead(pinY);

    if ((y <= (MiddleY - deadZone)) && (lastMove != DOWN))
    {   // UP
        lastMove = UP;
        return UP;
    }
    else if ((x >= (MiddleX + deadZone)) && (lastMove != LEFT))
    {   // RIGHT
        lastMove = RIGHT;
        return RIGHT;
    }
    else if ((x <= (MiddleX - deadZone)) && (lastMove != RIGHT))
    {   // LEFT
        lastMove = LEFT;
        return LEFT;
    }
    else if ((y >= (MiddleY + deadZone)) && (lastMove != UP))
    {   // DOWN
        lastMove = DOWN;
        return DOWN;
    }
    else
    {   // NO INPUT
        return lastMove
    }

    //The following is temp for testing
    /*
    if ((Serial.read() == 'w') && (lastMove == LEFT || lastMove == RIGHT))
    {   // UP
        lastMove = UP;
        return UP;
    }
    else if ((Serial.read() == 'd') && (lastMove == UP || lastMove == DOWN))
    {   // RIGHT
        lastMove = RIGHT;
        return RIGHT;
    }
    else if ((Serial.read() == 'a') && (lastMove == UP || lastMove == DOWN))
    {   // LEFT
        lastMove = LEFT;
        return LEFT;
    }
    else if ((Serial.read() == 's') && (lastMove == LEFT || lastMove == RIGHT))
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
