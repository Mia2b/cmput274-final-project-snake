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

PDQ_ILI9341 tft;			// PDQ: create LCD object (using pins in "PDQ_ILI9341_config.h")

void setup()
{
Serial.begin(9600);

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
        //tft.drawRect(lastX,lastY,16,16,ILI9341_BLACK);
        tft.drawRect(x,y,16,16,tft.color565(x*1.0666f,y*0.8f,j));
        tft.drawRect(x+4,y+4,8,8,tft.color565(x*1.0666f,y*0.8f,j));
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
        //tft.drawRect(lastX,lastY,16,16,ILI9341_BLACK);
        tft.drawRect(x,y,16,16,tft.color565(x*1.0666f,y*0.8f,j));
        tft.drawRect(x+4,y+4,8,8,tft.color565(x*1.0666f,y*0.8f,j));
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
  while(true)
  {
    loop();
    delay();
  }
	return 0;
}
