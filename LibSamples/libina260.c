/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/
#include "ina260.h"
#include "simpletools.h"

#define CLK 0
#define DTA 1

int i;

int main()
{
  i = INA260_open(CLK, DTA);

  printi("MFG: %x\n", i);
  
  i = INA260_getVoltage();
  
  printi("Volts: %d\n", i);
  
  i = INA260_getCurrent();
  
  printi("Current: %d\n", i);
  
  i = INA260_getPower();
  
  printi("Power: %d\n", i);
  
  INA260_setConfig(INA260_BOTH_CONTINUOUS, INA260_1100, INA260_1100, INA260_AVG1024, 0);
  
  i = INA260_getConfig();
  
  printi("Config: %x\n", i);
  
  while(1)
  {
    pause(1000);
    i = INA260_getCurrent();
    printi("Current: %d  ", i);
    i = INA260_getVoltage();
    printi("Voltage: %d\n", i);
  }  
}
