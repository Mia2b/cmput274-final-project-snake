#include <Arduino.h>
#include "Crumb.h"

Crumb::Crumb()
{
  length = 8; 
  lengthChanged = true; 
}
void Crumb::setLength(uint16_t len)
{
    length = len;
    lengthChanged = true;
}
void Crumb::insert(uint8_t direction)
{
    if (lengthChanged)
    {
        storageSize = length>>5;
        lengthChanged = false;
    }
    //Serial.println(storageSize);
    uint8_t hold = direction;
    for (uint16_t i = 0 ; i <= storageSize ; i++)
    {
        uint8_t store = hold;
        hold = ((moves[i]>>62)&3);
        moves[i] <<= 2;
        moves[i] += store;
    }
}
uint8_t Crumb::getMove(uint16_t index)
{
    uint16_t subArray = index>>5;
    return uint8_t((moves[subArray]>>((index%32)<<1))&3);
}