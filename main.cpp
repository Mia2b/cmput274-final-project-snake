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
#include "sinWave.h"
#include "apples.h"

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
	Snake snek = Snake(8,8, WIDTH, HEIGHT);
	int s = 6;
	int c = 0;
	
  	makeCoordinates(WIDTH, HEIGHT, snek);
  	Apple apple = getApple();
  	tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(224, 0, 0));

	struct xy
	{
		int x;
		int y;
	} b;
	b.x = 39;
	b.y = 49;

	tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_WHITE);
	tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_WHITE);
	tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_WHITE);

	tft.drawRect(0,HEIGHT-(b.y+1)*6,WIDTH,(b.y+1)*6, ILI9341_WHITE);
	tft.drawRect(1,HEIGHT-(b.y+1)*6+1,WIDTH-2,(b.y+1)*6-2, ILI9341_WHITE);
	tft.drawRect(2,HEIGHT-(b.y+1)*6+2,WIDTH-4,(b.y+1)*6-4, ILI9341_WHITE);

	
	//tft.fillRect(0,0)
	/*
	for (int i = 0 ; i < b.y; i++ )
	{
		tft.fillRect(3, i*s+23, s, s, tft.color565(255,255*(i&1),255));
	}
	*/
  	while(true)
  	{
		snek.update();
		Snake::coordinates cords = snek.getCords();
		Snake::coordinates endCord = snek.getEnd();
		tft.fillRect((cords.x%b.x)*s+3, (cords.y%b.y)*s+23, s, s, tft.color565(255-sqrt((cords.y%b.y)*s*0.8f*(cords.x%b.x)*s*1.0666f),(cords.y%b.y)*s*0.8f,(cords.x%b.x)*s*1.0666f));
		tft.fillRect((endCord.x%b.x)*s+3, (endCord.y%b.y)*s+23, s, s, ILI9341_BLACK);



		c++;
		c %= 360;




		if (appleCheck(WIDTH, HEIGHT, snek)) {
		Apple apple = getApple();
		
		// FIXME snek.Increase();
		}
		tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(sinWave[c%360],sinWave[(c+120)%360],sinWave[(c+240)%360]));
			delay(25);
		}
	return 0;
}


