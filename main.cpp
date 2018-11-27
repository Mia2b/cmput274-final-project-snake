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
	//int rgb[3] = {255,0,0};
  	init();
  	setup();
	//uint16_t cords = ((x)<<8)+();
	Snake snek = Snake(3,5, WIDTH, HEIGHT);
	int s = 8;
	int c = 0;
	//for (int i = 0; i < WIDTH/4; i++)
	//{
	//	tft.fillRect(cords.x*s+5*s, cords.y*s, s, s, tft.color565(255-sqrt(cords.y*s*0.8f*cords.x*s*1.0666f),cords.y*s*0.8f,cords.x*s*1.0666f));
	//}
	//tft.fillRect(cords.x*s+5*s, cords.y*s, s, s, tft.color565(255-sqrt(cords.y*s*0.8f*cords.x*s*1.0666f),cords.y*s*0.8f,cords.x*s*1.0666f));
  makeCoordinates(WIDTH, HEIGHT, snek);
  Apple apple = getApple();
  tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(224, 0, 0));
  	while(true)
  	{
		snek.update();
		Snake::coordinates cords = snek.getCords();
		Snake::coordinates endCord = snek.getEnd();
		tft.fillRect(cords.x*s, cords.y*s, s, s, tft.color565(255-sqrt(cords.y*s*0.8f*cords.x*s*1.0666f),cords.y*s*0.8f,cords.x*s*1.0666f));
		//tft.fillRect(cords.x*s, cords.y*s, s, s, tft.color565(sinWave[c%360],sinWave[(c+120)%360],sinWave[(c+240)%360]));
		tft.fillRect(endCord.x*s, endCord.y*s, s, s, ILI9341_BLACK);
		c++;
		c %= 360;
		tft.fillRect(endCord.x*s, endCord.y*s, s, s, ILI9341_BLACK);
		if (appleCheck(WIDTH, HEIGHT, snek)) {
		Apple apple = getApple();
		
		// FIXME snek.Increase();
		}
		tft.fillCircle(apple.aX, apple.aY, s/2, tft.color565(sinWave[c%360],sinWave[(c+120)%360],sinWave[(c+240)%360]));
			delay(150);
		}
	return 0;
}


