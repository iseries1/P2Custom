/**
 * @brief TFmini LiDAR Driver
 * @author Michael Burmeister
 * @date May 7, 2020
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "tfmini.h"
#include "serial.h"

void doTFmini(void *par);

FILE *_s;

static volatile int send;
static volatile int distance;
static volatile int strength;
static volatile int temperature;
static char Buffer[32];
static long Stack[40];

int tfmini_open(int Rx, int Tx)
{
  int c;
  
  send = 0;
  distance = -1;
  strength = -1;
  Buffer[0] = Rx;
  Buffer[1] = Tx;
  
  c = _cogstart(doTFmini, 0, Stack, 40);
  
  return c;
}

int tfmini_distance()
{
  return distance;
}

int tfmini_strength()
{
  return strength;
}

int tfmini_temperature()
{
  return temperature;
}

void tfmini_setUnits(int units)
{
  Buffer[10] = 5;
  if (units == 1)
    Buffer[11] = 1;
  if (units == 2)
    Buffer[11] = 6;
  send = 5;
}

void tfmini_setRate(short rate)
{
  if (rate > 1000)
    rate = 1000;
  Buffer[10] = 3;
  Buffer[11] = rate & 0x0f;
  Buffer[12] = rate >> 8;
  send = 6;
}

void doTFmini(void *par)
{
  char data;
  int i;
  char s;
    
  _s = serial_open(Buffer[0], Buffer[1], 115200);
  i = 0;
  
  while (1)
  {
    Buffer[i++] = serial_rxChar(_s);
    _pinl(56);
    if (i == 2)
    {
      if ((Buffer[0] != 0x59) || (Buffer[1] != 0x59))
        i = 0;
    }
        
    if (i > 8)
    {
      distance = Buffer[2] | Buffer[3] << 8;
      strength = Buffer[4] | Buffer[5] << 8;
      temperature = Buffer[6] | Buffer[7] << 8;
      i = 0;
    }
    
    if (send > 0)
    {
      Buffer[8] = 0x5a;
      Buffer[9] = send;
      s = 0;
      for (int j=0;j<send;j++)
      {
        serial_txChar(_s, Buffer[j+8]);
        s += Buffer[j+8];
      }        
      serial_txChar(_s, s);
      send = 0;
      i = 0;
    }        
  }

}
