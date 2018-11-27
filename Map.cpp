#include "Map.h"

/* 
Functions addMark and removeMark based on this:
https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
*/
Map::Map()
{
    for (int i = 0; i < X_BOUND; i++)
    {
        grid[i] = 0;
    }
    mask = 1;
}

void Map::addMark(uint8_t x, uint8_t y)
{
    grid[x] |= mask<<y;
}

void Map::removeMark(uint8_t x, uint8_t y)
{
    grid[x] &= ~(mask<<y);
}

bool Map::isMarked(uint8_t x, uint8_t y)
{
    return (((grid[x]>>y) & 1)?true:false);
}

bool Map::isOutOfBounds(uint8_t x, uint8_t y)
{
    return (x >= X_BOUND || y >= Y_BOUND);
}
