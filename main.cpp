/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <SPI.h>	
#include <SD.h>
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

void flashDeath()
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
}

void drawBoard()
{
	tft.fillScreen(ILI9341_BLACK);
	tft.drawRect(0,0,WIDTH,HEIGHT, ILI9341_WHITE);
	tft.drawRect(1,1,WIDTH-2,HEIGHT-2, ILI9341_WHITE);
	tft.drawRect(2,2,WIDTH-4,HEIGHT-4, ILI9341_WHITE);
	tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, ILI9341_WHITE);
	tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, ILI9341_WHITE);
	tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, ILI9341_WHITE);
}

void displayScore()
{
	tft.setCursor(5, 5);
	tft.setTextSize(2);
	tft.setTextColor(ILI9341_WHITE);
	tft.print("%f",11101);
}
void displayHighscore()
{
	tft.setCursor(128, 5);
	tft.setTextSize(2);
	tft.setTextColor(ILI9341_WHITE);
	tft.println(F("999999999"));
}

void setup()
{
	Serial.begin(9600);
	if (!SD.begin(SD_CS))
	{
		tft.fillScreen(ILI9341_RED);
		delay(2500);
 	}
  	tft.begin();			// initialize LCD
  	drawBoard();
}

void runGame()
{
	Map snakeMap;
	Snake snek = Snake(X_BOUND>>1,Y_BOUND>>1,3);
	Coordinates cords;
	Coordinates endCord;
	displayScore();
	displayHighscore();
  	while(snek.lives())
  	{
		Serial.print("freeMemory()=");
    	Serial.println(freeMemory());
		tft.fillRect(25*SCALE+3, 25*SCALE+23, SCALE, SCALE, ILI9341_WHITE);
		snek.update();
		cords = snek.getCords();
		endCord = snek.getEnd();
		if (snakeMap.isOutOfBounds(cords) || snakeMap.isMarked(cords))
		{
			flashDeath();
			snek.kill();
			delay(500);
			tft.fillRect(endCord.x*SCALE+3, endCord.y*SCALE+23, SCALE, SCALE, ILI9341_BLACK);
			while (snek.getLength() > 1)
			{
				snek.shrink(1);
				endCord = snek.getEnd();
				tft.fillRect(endCord.x*SCALE+3, endCord.y*SCALE+23, SCALE, SCALE, ILI9341_BLACK);
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
			snakeMap.addMark(cords);
			snakeMap.removeMark(endCord);

			tft.fillRect(cords.x*SCALE+3, cords.y*SCALE+23, SCALE, SCALE,\
			tft.color565(255-sqrt((cords.y%Y_BOUND)*SCALE*0.8f*(cords.x%X_BOUND)*SCALE*1.0666f), (cords.y%Y_BOUND)*SCALE*0.8f, (cords.x%X_BOUND)*SCALE*1.0666f));
			
			tft.fillRect(endCord.x*SCALE+3, endCord.y*SCALE+23, SCALE, SCALE, ILI9341_BLACK);
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
	}
	//respawnScreen();
	
	delay(2500);
	

}

int main()
{
  	init();
  	setup();
	while (true)
	{
		runGame();
	}
	return 0;
}


