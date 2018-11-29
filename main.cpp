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
#include "game_config.h" 
#include "Snake.h"
#include "Controller.h"
#include "sinWave.h"
#include "Map.h"
#include "Coordinates.h"
#include "MemoryFree.h" // https://playground.arduino.cc/Code/AvailableMemory

//#include "apples.h"

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
	Map map;
	Snake snek = Snake(X_BOUND>>1,Y_BOUND>>1,3);
	int s = 6;
	int c = 0;
	
	/*
  	makeCoordinates(WIDTH, HEIGHT, snek);
  	Apple apple = getApple();
  	tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(224, 0, 0));
*/
	tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_WHITE);
	tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_WHITE);
	tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_WHITE);

	tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_WHITE);
	tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_WHITE);
	tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_WHITE);

	
	//tft.fillRect(0,0)
	/*
	for (int i = 0 ; i < Y_BOUND; i++ )
	{
		tft.fillRect(3, i*s+23, s, s, tft.color565(255,255*(i&1),255));
	}
	*/
	Coordinates cords;
	Coordinates endCord;
  	while(snek.lives())
  	{
		  tft.fillRect(25*s+3, 25*s+23, s, s, ILI9341_WHITE);
		snek.update();
		cords = snek.getCords();
		endCord = snek.getEnd();
		if (map.isOutOfBounds(cords) || map.isMarked(cords))
		{
			tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_RED);
		tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_RED);
		tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_RED);

		tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_RED);
		tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_RED);
		tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_RED);

		delay(100);

		tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_WHITE);
		tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_WHITE);
		tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_WHITE);

		tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_WHITE);
		tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_WHITE);
		tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_WHITE);
		delay(25);
			tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_RED);
		tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_RED);
		tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_RED);

		tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_RED);
		tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_RED);
		tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_RED);

		delay(100);

		tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_WHITE);
		tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_WHITE);
		tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_WHITE);

		tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_WHITE);
		tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_WHITE);
		tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_WHITE);
		delay(25);
			snek.kill();
			delay(500);
			tft.fillRect(endCord.x*s+3, endCord.y*s+23, s, s, ILI9341_BLACK);
			while (snek.getLength() > 1)
			{
				snek.shrink(1);
				endCord = snek.getEnd();
				tft.fillRect(endCord.x*s+3, endCord.y*s+23, s, s, ILI9341_BLACK);
				int timeDelay = abs(100-(snek.getLength()<<1));
				if (timeDelay>5)
				{
					delay(timeDelay);
				}	
				else
				{
					delay(3);
				}
						
			}
		}
		else
		{
			if (cords.x == 25 && cords.y == 25)
			{
				snek.grow(2);
			}
			map.addMark(cords);
			map.removeMark(endCord);
			tft.fillRect(cords.x*s+3, cords.y*s+23, s, s, tft.color565(255-sqrt((cords.y%Y_BOUND)*s*0.8f*(cords.x%X_BOUND)*s*1.0666f),(cords.y%Y_BOUND)*s*0.8f,(cords.x%X_BOUND)*s*1.0666f));
			tft.fillRect(endCord.x*s+3, endCord.y*s+23, s, s, ILI9341_BLACK);
		}
		
		/*
		Serial.print("freeMemory()=");
    	Serial.println(freeMemory());
		*/
		
		c++;
		c %= 360;



		/*
		if (appleCheck(WIDTH, HEIGHT, snek)) {
		Apple apple = getApple();
		
		// FIXME snek.Increase();
		}
		tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(sinWave[c%360],sinWave[(c+120)%360],sinWave[(c+240)%360]));
			
		}
		*/
		int timeDelay = abs(100-(snek.getLength()>>2));
		if (timeDelay>25)
		{
			delay(timeDelay);
		}	
		else
		{
			delay(25);
		}
	}
	return 0;
}


