/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Button.h"

/* This button class is a copy of the button class Amir Hansen (me) made for 
the couting lights assignment */
Button::Button(int setPin)
{
  /*Initialize the button pin, use the pin as input, and pull the pin to high*/
  pin = setPin;
  pinMode(pin, INPUT_PULLUP);
}

bool Button::isTriggered()
{
  /*Return true uppon the button being pressed down*/
  return (currentState == LOW && lastState == HIGH);
}

void Button::updateState()
{
  /*Save the the last read state of the button and read the current state*/
  lastState = currentState;
  currentState = digitalRead(pin);
}


