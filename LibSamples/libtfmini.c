/**
 * @brief TFmini LiDAR Driver
 * @author Michael Burmeister
 * @date May 7, 2020
 * @version 1.0
 * 
*/
#include <propeller.h>
#include "simpletools.h"
#include "tfmini.h"

#define TRX 1
#define TTX 0

int i;
int d, s, t;


int main()
{
  i = tfmini_open(TRX, TTX);

  tfmini_setUnits(2);
   
  while(1)
  {
    d = tfmini_distance();
    s = tfmini_strength();
    t = tfmini_temperature();
    print("Distance: %d, Strength: %d, Temp: %d\n", d, s, t);
    pause(1000);    
  }  
}
