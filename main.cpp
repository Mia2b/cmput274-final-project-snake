/////////////////////////////////////////////////////////////////////////////
// Name: Amir Hansen, Ralph Milford                                        //
// ID: 1523209, 1534131                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "Actor.h"
#include <SPI.h>
//using namespace game;

// This is part of the PDQ re-mixed version of Adafruit's GFX library
// and associated chipset drivers.
// Here is the libraries original copyright notice:

/***************************************************
  This is an example sketch for the Adafruit 2.2" SPI display.
  This library works with the Adafruit 2.2" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/1480
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
#include "PDQ_GFX.h"				// PDQ: Core graphics library
#include "PDQ_ILI9341_config.h"			// PDQ: ILI9341 pins and other setup for this sketch
#include "PDQ_ILI9341.h"			// PDQ: Hardware-specific driver library
                                           

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")
/*
#include <Fonts/FreeSerif12pt7b.h>	// include fancy serif font
#include <Fonts/FreeSans12pt7b.h>	// include fancy sans-serif font
*/
// NOTE: Changes to test with Adafruit libraries (comment out PDQ lines above and un-comment the AF: ones below)

// AF: #include <Adafruit_GFX.h>		// AF: Core graphics library
// AF: #include <Adafruit_ILI9341.h>		// AF: Hardware-specific library
// AF: Adafruit_ILI9341 tft(10,  9, 8); 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)

// These are used to get information about static SRAM and flash memory sizes
extern "C" char __data_start[];		// start of SRAM data
extern "C" char _end[];			// end of SRAM data (used to check amount of SRAM this program's variables use)
extern "C" char __data_load_end[];	// end of FLASH (used to check amount of Flash this program's code and data uses)

void setup()
{
	Serial.begin(115200);
	while (!Serial);
	
#if defined(_PDQ_ILI9341H_)
	Serial.println(F("PDQ ILI9341 2.2\" SPI TFT Test!     ")); 
#else
 	Serial.println(F("Adafruit ILI9341 2.2\" SPI TFT Test!")); 
#endif
 
#if defined(ILI9341_RST_PIN)	// reset like Adafruit does
	FastPin<ILI9341_RST_PIN>::setOutput();
	FastPin<ILI9341_RST_PIN>::hi();
	FastPin<ILI9341_RST_PIN>::lo();
	delay(1);
	FastPin<ILI9341_RST_PIN>::hi();
#endif

	tft.begin();			// initialize LCD
        tft.fillScreen(ILI9341_BLACK);
}

void loop(void)
{
  
  int lasti = 0;
  int h = tft.height();
  int w = tft.width();
  int m = h>>1;
  /*
  for(int i = 1; i< h; i++)
  {
    tft.drawLine(0,m,w,i,ILI9341_WHITE);
    tft.drawLine(0,m+1,w,i+1,ILI9341_BLACK);
    tft.drawLine(0,m-1,w,i-1,ILI9341_BLACK);
  }
  
  for(int y=0; y<h; y+=16)
  {
    tft.drawFastHLine(0, y, w, ILI9341_WHITE);
  }
  
  for(int x=0; x<w; x+=16) 
  {
    tft.drawFastVLine(x, 0, h, ILI9341_WHITE);
  }
  
  for(int i = h; i>0 ; i--)
  {
    //tft.drawLine(0,m,w,i,ILI9341_WHITE);
    
    tft.drawLine(0,m,w,i,ILI9341_WHITE);
    tft.drawLine(0,m+1,w,i+1,ILI9341_BLACK);
    tft.drawLine(0,m-1,w,i-1,ILI9341_BLACK);
  }
  
  for(int y=0; y<h; y+=16)
  {
    tft.drawFastHLine(0, y, w, ILI9341_WHITE);
  }
  
  for(int x=0; x<w; x+=16) 
  {
    tft.drawFastVLine(x, 0, h, ILI9341_WHITE);
  }
  */
  int lastX = 0;
  int lastY = 0;
  for(int j = 0; j<254; j+=8)
  {
    for(int x=0; x<w; x+=16) 
    {
      for(int y=0; y<h; y+=16)
      {
        tft.drawRect(lastX,lastY,16,16,ILI9341_BLACK);
        tft.fillRect(x,y,16,16,tft.color565(x*1.0666f,y*0.8f,j));
        lastX = x;
        lastY = y;
      }
    }
  }
  for(int j = 255; j>1; j-=8)
  {
    for(int x=0; x<w; x+=16) 
    {
      for(int y=0; y<h; y+=16)
      {
        tft.drawRect(lastX,lastY,16,16,ILI9341_BLACK);
        tft.fillRect(x,y,16,16,tft.color565(x*1.0666f,y*0.8f,j));
        lastX = x;
        lastY = y;
      }
    }
  }
  /*
  int x1,x2,lx1,lx2;
  int y1,y2,ly1,ly2;
  tft.drawLine(random(0,w),random(0,h),random(0,w),random(0,h),ILI9341_WHITE);
  */
}

int main()
{
  init();
  setup();
  Serial.begin(9600);
  game::Actor obj;
  while(true)
  {
    loop();
  }
	return 0;
}
