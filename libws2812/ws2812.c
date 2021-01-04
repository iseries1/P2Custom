/**
 * @brief Driver for ws2812 leds
 * @author Michael Burmeister
 * @date November 10, 2020
 * @version 1.0
 * 
*/

#include "ws2812.h"

void ws2812_set(int pin, unsigned long *leds, int num)
{
    unsigned long color;
    unsigned int w;
    int bits;
    
    _pinl(pin);
    
    for (int i=0;i<num;i++)
    {
    	color = leds[i];
    	bits = 24;
    
    __asm const{
        ws2812	shl color, #8
        loop	rcl color, #1 wc
        		drvh pin
         if_c	waitx  #155
         if_nc  waitx  #65
         		drvl pin
         if_c   waitx  #65
         if_nc  waitx  #155
         		djnz bits, #loop
      }
    }
}
