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
#include "Snake.h"

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")

void setup()
{
	Serial.begin(9600);

  	tft.begin();			// initialize LCD
  	tft.fillScreen(ILI9341_BLACK);
}

void loop(void)
{
	//snek.update();
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
	//uint16_t cords = ((x)<<8)+();
	Snake snek = Snake(3,5);
  	while(true)
  	{
		snek.update();
		Snake::coordinates cords = snek.getCords();
		tft.fillRect(cords.x*8, cords.y*8, 8, 8, tft.color565(random(255),random(255),random(255)));
		delay(60);
  	}
	return 0;
}


