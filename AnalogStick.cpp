/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include "AnalogStick.h"

const uint8_t UP = 0;
const uint8_t RIGHT = 1;
const uint8_t LEFT = 2;
const uint8_t DOWN = 3;
//uint8_t = lastMoves;

AnalogStick::AnalogStick(uint8_t pinX, uint8_t pinY)
{
    /*Pin x and y must be analog for the joystick*/
    this->pinX = pinX;
    this->pinY = pinY;
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    middleX = analogRead(pinX);  // The x position of the analog stick at rest
    middleY = analogRead(pinY);  // The y position of the analog stick at rest
}

uint8_t AnalogStick::getDirection()
{

    int x = analogRead(pinX) - middleX;  // Centers the x coordinate based upon its position at rest
    int y = analogRead(pinY) - middleY;  // Centers the y coordinate based upon its position at rest
    long mag = (pow(x, 2) + pow(y, 2));  // Creates the magnitude of the joysticks current position
    float angle;
    // Creates the angle of the current postion, ranges from -180 to 180 degrees
    angle = atan2(-y,x)*(180.0/PI);

    // If the joystick is not outside of the given deadzone then no new direction is given
    if ( mag < deadZone)
    {
        return lastMove;
    }
    // Ensures that the snake will not flip 180 degrees
    // Checks to make sure that joystick is currently in the correcto quadrant
    // Up is in between 45 degrees and 135 degrees.  Right is in between -45 degrees and 45 degrees. Down is in between -135 degrees and -45 degrees.  While Left has to be less than or equal to -135 degrees or greater than or equal to 135 degrees.
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

