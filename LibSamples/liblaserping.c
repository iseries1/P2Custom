/**
 * @brief Laser Ping Driver to determine distance
 * @author Michael Burmeister
 * @date March 30, 2019
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "laserping.h"


#define LASER 36
#define PING 0

int i;

int main()
{

  laserping_start('X', LASER);
  
  while(1)
  {
    i = laserping_distance();
    printf("Distance: %d\n", i);
    _waitms(500);
  }  
}
