#ifndef apples_h
#define apples_h

#include "Arduino.h"
#include "Snake.h"

struct Apple {
    uint16_t aX;
    uint16_t aY;
};

Apple appleCoordinates;

void makeCoordinates(uint16_t WIDTH, uint16_t HEIGHT, Snake snek) {

    randomSeed(analogRead(0));
    appleCoordinates.aX = random(0, WIDTH);
    appleCoordinates.aY = random(0, HEIGHT);

    if (snek.isInHistory(appleCoordinates.aX, appleCoordinates.aY)) {
        
        appleCoordinates.aX = random(0, WIDTH);
        appleCoordinates.aY = random(0, HEIGHT);

    }
}

bool appleCheck(uint16_t WIDTH, uint16_t HEIGHT, Snake snek) {

    if (snek.isInHistory(appleCoordinates.aX, appleCoordinates.aY)) {

        makeCoordinates(WIDTH, HEIGHT, snek);
        return true;

    } else {

        return false;

    }
}

Apple getApple() {

    return appleCoordinates;

}

#endif
