/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <SPI.h>
#include "PDQ_GFX.h"				// PDQ: Core graphics library
#include "PDQ_ILI9341_config.h"			// PDQ: ILI9341 pins and other setup for this sketch
#include "PDQ_ILI9341.h"			// PDQ: Hardware-specific driver library  
#include "snake.h"                                     

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")

void setup()
{
	Serial.begin(9600);

  	tft.begin();			// initialize LCD
  	tft.fillScreen(ILI9341_BLACK);
}

void loop(void)
{
	/*
	TODO have the snake move on command
	TODO have the snake move in the input direction
	TODO keep track of the movement history of the snake
	TODO use the move history to keep track of the segments
	TODO for the length of the snake erase the segment a sertain amount back
	*/
}

int main()
{
  	init();
  	setup();
	
  	while(true)
  	{
		loop();
  	}
	return 0;
}


