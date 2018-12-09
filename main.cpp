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
#include "sinWave.h"
#include "Map.h"
#include "Coordinates.h"
#include "Button.h"


#include "MemoryFree.h" // https://playground.arduino.cc/Code/AvailableMemory
#include "Apples.h"

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")
const int WIDTH = tft.width();	// should be 240
const int HEIGHT = tft.height(); // should be 320

struct dataBus
{	/* Data inside here is saved after each game/life */
	uint32_t highScore[10];  // The top 10 scores that has been reached
	uint64_t check;  // A check to ensure that the proper vairables has been read
}topScores;

void drawFrame(uint16_t color)
{
	tft.drawRect(0,0,WIDTH,HEIGHT, color);
	tft.drawRect(1,1,WIDTH-2,HEIGHT-2, color);
	tft.drawRect(2,2,WIDTH-4,HEIGHT-4, color);
	tft.drawRect(0,HEIGHT-(Y_BOUND+1)*6,WIDTH,(Y_BOUND+1)*6, color);
	tft.drawRect(1,HEIGHT-(Y_BOUND+1)*6+1,WIDTH-2,(Y_BOUND+1)*6-2, color);
	tft.drawRect(2,HEIGHT-(Y_BOUND+1)*6+2,WIDTH-4,(Y_BOUND+1)*6-4, color);
}

void flashDeath()
{
	/* Animation for flashing the screen red on death */
	drawFrame(ILI9341_RED);
	delay(100);
	drawFrame(ILI9341_WHITE);
	delay(25);
	drawFrame(ILI9341_RED);
	delay(100);
	drawFrame(ILI9341_WHITE);
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

#define integrityCheck 0x1a2b3c4d5e6f789f  // The chosen variable that gets check every time the score is read from the Arduino

void setup()
{
	Serial.begin(9600);
  	tft.begin();			// initialize LCD
  	
	tft.fillScreen(ILI9341_BLACK);
	drawFrame(ILI9341_WHITE);
	
	eeprom_read_block((void*)&topScores, (void*)0, sizeof(topScores));  // Reads in the topscores from the Arduino
	if (topScores.check != integrityCheck)  // If the integrity check fails sets highscores to predetermined numbers
	{	

		topScores.highScore[0] = 500000;
		topScores.highScore[1] =  80000;
		topScores.highScore[2] =  75000;
		topScores.highScore[3] =  70000;
		topScores.highScore[4] =  60000;
		topScores.highScore[5] =  50000;
		topScores.highScore[6] =   4000;
		topScores.highScore[7] =   3000;
		topScores.highScore[8] =   2000;
		topScores.highScore[9] =   1000;
		topScores.check = integrityCheck;
		eeprom_update_block((const void*)&topScores, (void*)0, sizeof(topScores));  // Writes these predetermined numbers to the Arduino to replace misssing highscores
	}
	displayScore(0,ILI9341_WHITE);
	displayHighscore(ILI9341_WHITE);
}

uint32_t score = 0;

void runGame()
{
	Map snakeMap;
	Snake snek = Snake(X_BOUND>>1,Y_BOUND>>1, 3);
	Coordinates cords;
	Coordinates endCord;
	Map appleMap;  // Creates the map to keep track of the apples
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


	uint8_t index = 123;
	tft.setCursor(60, 34);
	tft.setTextSize(4);
	tft.setTextColor(ILI9341_WHITE);
	tft.println("Snake");

	
	for (int i = 0; i < 10; i++)
	{
		if (topScores.highScore[i] <= score)
		{
			if (i == 0)
			{
				displayHighscore(ILI9341_BLACK);
			}
			for (int j = 9; j > i; j-- )
			{
				topScores.highScore[j] = topScores.highScore[j-1];
			}
			topScores.highScore[i] = score;
			displayHighscore(ILI9341_WHITE);
			index = i;
			break;
		}
	}
	eeprom_update_block((const void*)&topScores, (void*)0, sizeof(topScores));
	
	
	cycle=100;
	for (int i = 0; i < 10; i++)
	{
		argb.r = sinWave[(cycle)%360];
		argb.g = sinWave[(cycle+120)%360];
		argb.b =  sinWave[(cycle+240)%360];

		tft.setCursor(64, 73 + 20*i);
		tft.setTextSize(2);
		tft.setTextColor( tft.color565(argb.r, argb.g, argb.b));
		if (i == index)
		{
			tft.setTextColor(ILI9341_WHITE);
		}
		printPadded(topScores.highScore[i], 9);
		cycle+=18;
		cycle%=360;
	}
	

	Button button = Button(A2);

	bool waitingForContinue = true;

	//tft.setCursor(64, 80 + 20*index);

	while(waitingForContinue)
	{
		delay(5);
		button.updateState();
		argb.r = sinWave[(cycle)%360];
		argb.g = sinWave[(cycle+120)%360];
		argb.b =  sinWave[(cycle+240)%360];
		uint16_t fade = argb.r;
		if (index <= 10)
		{
			
			tft.setCursor(64, 73 + 20*index);
			tft.setTextSize(2);
			tft.setTextColor(tft.color565(argb.r, argb.g, argb.b));
			printPadded(score, 9);
		}

		tft.setCursor(23, 280);
		tft.setTextColor(tft.color565(fade, fade, fade));
		tft.setTextSize(2);
		tft.println("<click to start>");
		cycle+=5;
		cycle%=360;
		if (button.isTriggered())
		{
			waitingForContinue = false;
		}
	}

	tft.setCursor(23, 280);
	tft.setTextColor(ILI9341_BLACK);
	tft.setTextSize(2);
	tft.println("<click to start>");

	tft.setCursor(60, 34);
	tft.setTextSize(4);
	tft.setTextColor(ILI9341_BLACK);
	tft.println("Snake");


	for (int i = 0; i < 10; i++)
	{
		tft.setCursor(64,73 + 20*i);
		tft.setTextSize(2);
		tft.setTextColor(ILI9341_BLACK);
		printPadded(topScores.highScore[i], 9);
	}
	

	randomSeed(analogRead(A14));  // Reads noise from an analog pin to change so that any random function will be different each time
	for (uint8_t i = 0; i < APPLE_COUNT; i++)  // Creates the number of apples wanted based upon game_config.h
	{


		Apple &apl = bunch[i];
		// Set each apple to random coordinate within the bounds of the screen
		apl.cord.x = random(0, X_BOUND);
		apl.cord.y = random(0, Y_BOUND);
		// Gives each apple a unique value to randomize color and point value
		apl.phaseShift = random(0, 360);
		// Checks to make sure that apples are not on the snake itself or another apple
		while (snakeMap.isMarked(apl.cord) || appleMap.isMarked(apl.cord))
		{
			apl.cord.x = random(0, X_BOUND);
			apl.cord.y = random(0, Y_BOUND);
		}
		// Creates a new point on the map for apples
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


			if (appleMap.isMarked(cords)) // Checks to see if the snake is currently on an apple
			{
				displayScore(score, ILI9341_BLACK);
				snek.grow(3);
				appleMap.removeMark(cords);  // The position of the apple that the snake is on is removed

				// Runs through each apple in order to replace the one that the snake is on
				for (uint8_t i=0; i < APPLE_COUNT; i++)
				{
					Apple &apl = bunch[i];
					// Tests to see if the current apple is the one the snake is on
					if (apl.cord.x == cords.x && apl.cord.y == cords.y)
					{
						// Replaces the apples coordinates until it's not either the snake or another apple
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
						appleMap.addMark(apl.cord);  // Adds the noew position of the apple
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
	delay(500);
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


