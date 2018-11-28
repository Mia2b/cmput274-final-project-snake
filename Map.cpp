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

void Map::addMark(Coordinates cord)
{
    grid[cord.x] |= mask<<cord.y;
}

void Map::removeMark(Coordinates cord)
{
    grid[cord.x] &= ~(mask<<cord.y);
}

bool Map::isMarked(Coordinates cord)
{
    return (((grid[cord.x]>>cord.y) & 1)?true:false);
}

bool Map::isOutOfBounds(Coordinates cord)
{
    return (cord.x >= X_BOUND || cord.y >= Y_BOUND);
}
