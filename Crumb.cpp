/////////////////////////////////////////////////////////////////////////////
// Name: Mia2b, HalloweenRalph                                             //
// ID: 0000000, 0000001                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Crumb.h"

Crumb::Crumb()
{
    /* Initialize a crumb object*/
    length = 8; 
    lengthChanged = true;
}

void Crumb::setLength(uint16_t len)
{
    /* Set the length of the stored crumb
       This does not decrease the memory used just the amount 
       bit operation needed to store and acces data*/
    length = len;
    lengthChanged = true;
}

void Crumb::insert(uint8_t direction)
{
    /* Will insert to the start of the crump list what the move was, shifting
       all previos moves to the next index. */
    if (lengthChanged)
    {
        /* If the length has changed we will need to adjust to make sure
           all the moves that we are interested in are stored */
        storageSize = (length>>5) + 1;
        lengthChanged = false;
    }
    
    uint8_t hold = direction;
    for (uint16_t i = 0 ; i < storageSize ; i++)
    {
        /* Shift each move over 2 bit (each move is 2 bits wide) then add
           the new move to the front of the list */
        uint8_t store = hold;
        hold = ((moves[i]>>62)&3); // Moves the overflow to the next array index
        moves[i] <<= 2;
        moves[i] += store;
    }
}

uint8_t Crumb::getMove(uint16_t index)
{
    /* Will get the move at index */
    uint16_t subArray = index>>5;
    return uint8_t((moves[subArray]>>((index%32)<<1))&3);
}