/**
 * @brief Control ws2812b led's
 * @author Michael Burmeister
 * @date October 31, 2020
 * @version 1.0
 * 
*/
#include "ws2812.h"

#include "simpletools.h"

#define WSLED 32
#define LED_COUNT 50


unsigned long ledColors[LED_COUNT];
int i;
unsigned long c[3];

int main()
{
  int x;
  
  printi("Starting\n");
  
  c[0] = COLOR(32,0,0);
  c[1] = COLOR(0,32,0);
  c[2] = COLOR(0,0,32);
  
  x = 0;
  
  for (int i=0;i<12;i++)
  {
    for (int j=0;j<LED_COUNT;j++)
    {
      if (x > 2)
        x = x - 3;
      ledColors[j] = c[x++];
    }
    x++;
    ws2812_set(WSLED, ledColors, LED_COUNT);
    pause(1000);
  }
 
  for (int i=0;i<LED_COUNT;i++)
    ledColors[i] = 0;
  
  ws2812_set(WSLED, ledColors, LED_COUNT);
  
  printi("Done\n");
  
  while(1)
  {
    pause(1000);
  }  
}
