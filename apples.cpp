#include "Arduino.h"
#include "Snake.h"
#include "apples.h"


void apples::makeCoord(screenWidth, screenLength) {

    appleCurrent.aX = random(0, screenWidth);
    appleCurrent.aY = random(0, screenLength);

    while (Snake.isInHistory(appleCurrent.aX, appleCurrent.aY) {

      appleCurrent.aX = random(0, screenWidth);
      appleCurrent.aY = random(0, screenLength);

    } 

}


bool apples::appleCheck(screenWidth, screenLength) {

    if (Snake.isInHistory(appleCurrent.aX, appleCurrent.aY)) {

        makeCoord(screenWidth, screenLength
        return true;

    } else {

        return false;

    }

}


apples::Coord apples::appleMake() {

    return appleCurrent;

}
