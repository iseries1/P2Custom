/**
 * @brief BME280 sensor library
 * @author Michael Burmeister
 * @date December 14, 2017
 * @version 1.2
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "simpletools.h"
#include "bme280.h"

void doReset(void);


#define BMESCL 16
#define BMESDA 17


int main()
{
  int i;
  int j;
  float f;
  
  i = BME280_open(BMESCL, BMESDA);
  
  print("should be hex (60):%x \n", i);
  
  doReset();
  
  i = BME280_getMode();
  print("Mode: %x \n", i);
  
  f = 0;
  
  while(1)
  {
    j = 0;
    while (i != 0)
    {
      j++;
      printf("%8.8x\n", i);
      pause(1000);
      i = BME280_getStatus();
      i = i & 0x09;
      if (j > 4)
      {
        doReset();
        print("Reset\n");
        j = 0;
      }        
    }
    
    if (j != 0)
    {
      j = 0;
      print("\n");
    }
          
    i = BME280_getTempF();
//    f = BME280_getTemperature();
//    printf("Temp: %d %2.2f ", i, f);
    print("Temp: %d ", i);
    
    i = BME280_getPressure();
//    f = BME280_getPressuref();
//    printf("Pressure: %d %2.2f ", i, f);
    print("Pressure: %d ", i);
    
    i = BME280_getHumidity();
//    f = BME280_getHumidityf();
//    printf("Humidity: %d %2.2f\n", i, f);
    print("Humidity: %d%% \n", i/100);
    
    i = BME280_getStatus();
    pause(1000);
  }  
}

void doReset()
{
  BME280_reset();
  
  BME280_setHumidity(oversample_1);
  BME280_setTemp(oversample_1);
  BME280_setPressure(oversample_1);
  BME280_setStandbyRate(standby625);
  BME280_setMode(BME280_normal);
  pause(250);
}
