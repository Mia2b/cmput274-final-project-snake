/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <SPI.h>	
#include <avr/eeprom.h>
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
#include "Apples.h"

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")
const int WIDTH = tft.width();	// should be 240
const int HEIGHT = tft.height(); // should be 320

struct dataBus
{
	uint32_t highScore[5];
}topScores;

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

void printPadded(uint32_t v, uint16_t width)
{
	// Based on Adafruit ILI9341 graphics test example
	char str[32] = { 0 };
	sprintf(str, "%lu", v);
	while (strlen(str) < width)
	{
		memmove(str+1, str, strlen(str)+1);
		*str = '0';
	}
	tft.print(str);
}


void displayScore(uint32_t score ,uint16_t color)
{
	tft.setCursor(5, 5);
	tft.setTextSize(2);
	tft.setTextColor(color);
	printPadded(score,9);
}
void displayHighscore(uint16_t color)
{
	tft.setCursor(128, 5);
	tft.setTextSize(2);
	tft.setTextColor(color);
	printPadded(topScores.highScore[0],9);
}

void setup()
{
	Serial.begin(9600);
  	tft.begin();			// initialize LCD
  	drawBoard();
	uint64_t check;
	eeprom_read_block((void*)&check, (void*)0, 64);
	if (check == 0x1a2b3c4d5e6f7890)
	{
		eeprom_read_block((void*)&topScores, (void*)0, sizeof(topScores));
	}
	else
	{
		topScores.highScore[0] = 0;
		topScores.highScore[1] = 0;
		topScores.highScore[2] = 0;
		topScores.highScore[3] = 0;
		topScores.highScore[4] = 0;
	}
}

uint32_t score = 0;

void runGame()
{
	Map snakeMap;
	Snake snek = Snake(X_BOUND>>1,Y_BOUND>>1,3);
	Coordinates cords;
	Coordinates endCord;
	Map appleMap;
	randomSeed(analogRead(A14));
	for (uint8_t i = 0; i < APPLE_COUNT; i++)
	{


		Apple &apl = bunch[i];
		apl.cord.x = random(0, X_BOUND);
		apl.cord.y = random(0, Y_BOUND);
		apl.phaseShift = random(0, 360);
		while (snakeMap.isMarked(apl.cord) || appleMap.isMarked(apl.cord))
		{
			apl.cord.x = random(0, X_BOUND);
			apl.cord.y = random(0, Y_BOUND);
		}
		appleMap.addMark(apl.cord);
	}
	for (uint8_t i = 0; i < APPLE_COUNT; i++)
	{
		Apple apl = bunch[i];
		Serial.println(apl.cord.x);
	} 
	displayScore(score,ILI9341_BLACK);
	score = 0;
	displayScore(score,ILI9341_WHITE);
	displayHighscore(ILI9341_WHITE);
	int cycle = 0;


	struct rgb
	{
		int16_t r;
		int16_t g;
		int16_t b;
	};
	rgb srgb;	// Snake rgb values 
	rgb argb;	// Apple rgb values
	rgb drgb;	// Delta rgb values
  	while(snek.lives())
  	{
		/*
		Serial.print("freeMemory()=");
    	Serial.println(freeMemory());
		*/
		snek.update();
		cords = snek.getCords();
		endCord = snek.getEnd();
		srgb.g = (cords.y%Y_BOUND)*SCALE*0.8f;
		srgb.b = (cords.x%X_BOUND)*SCALE*1.0666f;
		srgb.r = 255-sqrt(srgb.g*srgb.b);
		
		if (snakeMap.isOutOfBounds(cords) || snakeMap.isMarked(cords))
		{
			snek.kill();
			
			for (uint8_t i = 0; i < APPLE_COUNT; i++)
			{
				Apple apl = bunch[i];
				tft.fillRect((apl.cord.x)*SCALE+3, (apl.cord.y)*SCALE+23, SCALE, SCALE , ILI9341_BLACK);
			}
			flashDeath();
			
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
					delay(5);
				}
						
			}
		}
		else
		{
			snakeMap.addMark(cords);
			snakeMap.removeMark(endCord);


			if (appleMap.isMarked(cords))
			{
				displayScore(score, ILI9341_BLACK);
				snek.grow(3);
				appleMap.removeMark(cords);

				for (uint8_t i=0; i < APPLE_COUNT; i++)
				{
					Apple &apl = bunch[i];
					if (apl.cord.x == cords.x && apl.cord.y == cords.y)
					{
						while(snakeMap.isMarked(apl.cord) || appleMap.isMarked(apl.cord))
						{
							apl.cord.x = random(0, X_BOUND);
							apl.cord.y = random(0, Y_BOUND);
						}
						argb.r = sinWave[(apl.phaseShift+cycle)%360];
						argb.g = sinWave[(apl.phaseShift+cycle+120)%360];
						argb.b =  sinWave[(apl.phaseShift+cycle+240)%360];

						drgb.r = 256-abs(argb.r - srgb.r);
						drgb.g = 256-abs(argb.g - srgb.g);
						drgb.b = 256-abs(argb.b - srgb.b);

						score += pow(((snek.getLength())*drgb.r*drgb.g*drgb.b),1);
						apl.phaseShift = random(0, 360);
						appleMap.addMark(apl.cord);
					}
				}
				displayScore(score, ILI9341_WHITE);
			}

			for (uint8_t i = 0; i < APPLE_COUNT; i++)
			{
				Apple apl = bunch[i];
				argb.r = sinWave[(apl.phaseShift+cycle)%360];
				argb.g = sinWave[(apl.phaseShift+cycle+120)%360];
				argb.b =  sinWave[(apl.phaseShift+cycle+240)%360];
				tft.fillRect((apl.cord.x)*SCALE+3, (apl.cord.y)*SCALE+23, SCALE, SCALE , tft.color565(argb.r, argb.g, argb.b));
			}

			tft.fillRect(cords.x*SCALE+3, cords.y*SCALE+23, SCALE, SCALE,\
			tft.color565(srgb.r, srgb.g, srgb.b));
			
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
			cycle+=2;
			cycle%=360;
		}
	}
	uint8_t index = 5;
	tft.setCursor(100, 20);
	tft.setTextSize(2);
	tft.setTextColor(ILI9341_WHITE);
	tft.print("Press the Joystick to Continue");
	for (int i = 0; i < 5; i++)
	{
		if (topScores.highScore[i] <= score)
		{
			topScores.highScore[i] = score;
			index = i;
		}
		tft.setCursor(100, 40 + 20*i);
		tft.setTextSize(2);
		tft.setTextColor(ILI9341_WHITE);
		printPadded(topScores.highScore[i], 0);
	}
	int joystickCur = controller.getButton();
	int joystickOld = joystickCur;
	bool waitingForContinue = true;
	while(waitingForContinue)
	{
		joystickCur = controller.getButton();

		if (index != 5)
		{
			tft.setCursor(100, 40 + 20*index);
			tft.setTextSize(2);
			tft.setTextColor(ILI9341_BLACK);
			printPadded(score, 9);
			delay(500);
			tft.setTextColor(ILI9341_WHITE);
			printPadded(score, 9);
			delay(500);
		}

		if (joystickCur == HIGH && joystickOld == LOW)
		{
			waitingForContinue = false;
		}
		joystickOld = joystickCur;
	}
	uint64_t check = 0x1a2b3c4d5e6f7890;
	eeprom_write_block((const void*)&check, (void*)0, 64);
	eeprom_update_block((const void*)&topScores, (void*)0, sizeof(topScores));
	/*
	if (score > topScores.highScore[0])
	{
		
		displayHighscore(ILI9341_BLACK);
		topScores.highScore[0] = score;
		eeprom_write_block((const void*)&topScores, (void*)0, sizeof(topScores));
		displayHighscore(ILI9341_WHITE);
	}
	*/


	delay(2500);
	//while()
	///{
		
	//}
	//respawnScreen();
	
	
	

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


