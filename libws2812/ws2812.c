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
    short H, L;

    H = _clkfreq/1111111; // 90nsec (1250000 80ns)
    L = _clkfreq/2857143; // 35nsec (2500000 40ns)

    _pinl(pin);
    
    for (int i=0;i<num;i++)
    {
    	color = leds[i];
    	bits = 24;
    
    __asm const{
        ws2812	shl color, #8
        loop	rcl color, #1 wc
        		drvh pin
         if_c	waitx  H
         if_nc  waitx  L
         		drvl pin
         if_c   waitx  L
         if_nc  waitx  H
         		djnz bits, #loop
      }
    }
}
