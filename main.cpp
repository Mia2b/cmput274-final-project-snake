/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <SPI.h>	
#include "PDQ_GFX.h"			// PDQ: Core graphics library
#include "PDQ_ILI9341_config.h"	// PDQ: ILI9341 pins and other setup for this sketch
#include "PDQ_ILI9341.h"		// PDQ: Hardware-specific driver library  
#include "Snake.h"
#include "Controller.h"

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")
const int WIDTH = tft.width();	// should be 240
const int HEIGHT = tft.height(); // should be 320
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
		Snake::coordinates endCord = snek.getEnd();
		tft.fillRect(cords.x*8, cords.y*8, 8, 8, tft.color565(255,255,255));
		tft.fillRect(endCord.x*8, endCord.y*8, 8, 8, tft.color565(0,0,0));
		delay(50);
	}
//	Snake snek = Snake(3);
 	/*
        Controller controls = Controller(A0, A1, 13);
  	while(true)
  	{
//		snek.update();
                Serial.println(controls.getDirection());
  	}
	  */
	return 0;
}


