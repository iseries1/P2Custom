/**
 * @brief TFmini LiDAR Driver
 * @author Michael Burmeister
 * @date May 7, 2020
 * @version 1.0
 * 
*/
#include <propeller.h>
#include "tfmini.h"

#define TRX 37
#define TTX 36

int i;
int d, s, t;


int main()
{
  printf("Starting\n");

  i = tfmini_open(TRX, TTX);

  tfmini_setUnits(2);
   
  while(1)
  {
    d = tfmini_distance();
    s = tfmini_strength();
    t = tfmini_temperature();
    printf("Distance: %d, Strength: %d, Temp: %d\n", d, s, t);
    _waitms(1000);    
  }  
}
