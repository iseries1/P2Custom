/**
 * @brief AS5048 Position Sensor
 * @author Michael Burmeister
 * @date January 19, 2016
 * @version 1.0
 * @details Magnetic Rotary Encoder
 *  The AS5048 is an easy to use 360° angle position sensor with a 14-bit high resolution output
*/

#include <stdio.h>
#include <propeller.h>
#include "simpletools.h"
#include "as5048a.h"

#define CS 16
#define SCK 17
#define MOSI 18
#define MISO 19

int Angle;

int main()
{
  int i;
  
  i = as5048a_open(CS, SCK, MOSI, MISO);
  
  print("Status: %x\n", i);
  
  while(1)
  {
    pause(250);
    Angle = as5048a_readAngle();
    if (i != Angle)
      print("Angle: %d\n", Angle);
    i = Angle;
  }
  
}
