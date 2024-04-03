/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include <time.h>
#include "ina260.h"

#define CLK 36
#define DTA 37

char Modes[][20] = {"Power Down", "Current Trigger", "Voltage Trigger", "Trigger Both", "Power Down",
                   "Continues Current", "Continues Voltage", "Continues Both"};

int i, j;
int c, v;
int mv;
time_t t, p;
struct tm *x;

int main()
{
  printf("Starting\n");
  
  i = INA260_open(CLK, DTA);

  if (i == 0x5449)
    printf("INA260 Found\n");
  else
    printf("Not Found\n");
  
  i = INA260_getMode();

  printf("Mode: %s\n", Modes[i]);

  i = INA260_getVoltage();
  
  printf("Volts in Hundredths: %d\n", i);
  
  i = INA260_getCurrent();
  
  printf("Current: %d ma\n", i);
  
  i = INA260_getPower();
  
  printf("Power: %d mw\n", i);
  
  INA260_setMode(7);
  
  mv = 8200;
  p = 0;
  j = 0;
  while(1)
  {
    _waitms(1000);
    t = time(&t);
    c = INA260_getCurrent();
    v = INA260_getVoltage();
    printf("%d -> %dmv %dma\n",j++, v, c);
    if (v < mv)
    {
      t = time(&t);
      x = localtime(&t);
      printf("Time(%d): %s\n", t - p, asctime(x));
      mv = v - 100;
    }
  }  
}
