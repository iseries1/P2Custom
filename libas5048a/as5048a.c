/**
 * @brief AS5048 Position Sensor
 * @author Michael Burmeister
 * @date January 19, 2016
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "as5048a.h"

int as5048aSR(int);

int aCS;
int aSCK;
int aMOSI;
int aMISO;
int aOffset;


// Open Connection to as5048a sensor
int as5048a_open(int acs, int asck, int amosi, int amiso)
{
  int i;
  
  aCS = acs;
  aSCK = asck;
  aMOSI = amosi;
  aMISO = amiso;
  
  aOffset = 0;
  high(aMOSI);
  high(aCS);
  i = as5048aSR(0x0000); // Nop
  as5048aSR(0xffff); // Set Register for angle
  
  return i;
}

// Get current sensor angle
int as5048a_readAngle(void)
{
  int i;
  
  low(aCS);
  i = shift_in(aMISO, aSCK, MSBPOST, 16);
  high(aCS);
  if ((i & 0x4000) != 0)  // If error flag is set try reseting it
  {
    i = as5048aSR(0x4001); // clear errors
    i = as5048aSR(0xffff); // reset
    low(aCS);
    i = shift_in(aMISO, aSCK, MSBPOST, 16);
    high(aCS);
  }
 
  i = i & 0x3FFF;
  i = i * 10 / 456;
  
  if (i >= 0)
  {
    i = i - aOffset;
    if (i < 0)
      i = i + 360;
  }

  return i;
}

// Set angle offset
void as5048a_setOffset(int offset)
{
  if (offset > 359)
    return;
  if (offset < 0)
    return;
  aOffset = offset;
}

// Send Receive data
int as5048aSR(int i)
{
  low(aCS);
  shift_out(aMOSI, aSCK, MSBFIRST, 16, i);
  high(aCS);
  pause(10);
  low(aCS);
  i = shift_in(aMISO, aSCK, MSBPOST, 16);
  high(aCS);
  return i;
}
