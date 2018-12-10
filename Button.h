/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef Button_H
#define Button_H


/* This button class is a copy of the button class Amir Hansen (me) made for 
the couting lights assignment */
/*A class for handling button inputs*/

class Button
{
 private:
  int pin;
  int currentState;
  int lastState;
 public:
  /*Initializing the button object*/
  Button(int setPin);

  /*Return if the button has been pressed down*/
  bool isTriggered();

  /*Read the current state of the button*/
  void updateState();
};

#endif
