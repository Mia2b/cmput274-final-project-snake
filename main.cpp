/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Actor.h"
using namespace game;
int main()
{
  init();
  Serial.begin(9600);
  game::Actor obj;
  while(true)
  {
    obj.update();
  }
	return 0;
}
