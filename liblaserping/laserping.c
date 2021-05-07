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
#include "serial.h"


void laserping_run(void *par);
void laserping_runp(void *par);
void PulseOut(int, int);
int PulseIn(int, int);


char _Pin;
int _Average[16];
char _Buffer[25];
int _RS;
long Stack[51];
FILE *_s;

void laserping_start(char mode, char pin)
{
  _Pin = pin;

  if (mode == 'S')
    cogstart(laserping_run, 0, Stack, 50);
  else
    cogstart(laserping_runp, 0, Stack, 50);
}
  
void laserping_run(void *par)
{
  char c;
  int p;
  int i;
  int t;
  
  _dirh(_Pin);
  _pinl(_Pin);
  _waitms(250);

  _s = serial_open( -1, _Pin, 9600);
  
  serial_txChar(_s, 'I');
  serial_txChar(_s, 'I');

  serial_close(_s);
  _s = serial_open(_Pin, -1, 9600);

  p = 0;
  t = 0;
  _RS = 1;
  while (_RS)
  {
    c = serial_rxChar(_s);
    if (c == 13)
    {
      _Buffer[p] = 0;
      i = atoi(_Buffer);
      _Average[t++] = i;
      t = t & 0x0f;
      p = 0;
    }
    else
      _Buffer[p++] = c;

    if (p > 10)
      p = 0;
  }
  serial_close(_s);
  //cogstop(cogid());
}

void laserping_runp(void *par)
{
  int i;
  int t;
  
  _pinl(_Pin);
  
  t = 0;
  _RS = 1;
  while (_RS)
  {
    _waitms(70);
    _pinl(_Pin);
    PulseOut(_Pin, 5);
    i = PulseIn(_Pin, 1);
    _Average[t++] = i * 1715 / 10000;
    t = t & 0x0f;
  }
}
  
int laserping_distance(void)
{
  int d = 0;
  
  for (int i=0;i<16;i++)
    d = d + _Average[i];
  
  return d / 16;
}

void laserping_stop(void)
{
  _RS = 0;
}

// Pulse pin for x
void PulseOut(int p, int t)
{
    int i;
    
    i = _pinr(p);
    if (i == 0)
    	_pinh(p);
    else
    	_pinl(p);
    _waitus(t);
    if (i == 0)
    	_pinl(p);
    else
    	_pinh(p);
}

// Get Pulse Length in microseconds
int PulseIn(int p, int s)
{
    int i;
    
    _pinf(p);
    i = _getus();
    while ((_pinr(p) != s) && ((_getus() - i) < 1000));
    i = _getus();
    while ((_pinr(p) == s) && ((_getus() - i) < 100000));
    i = _getus() - i;
    return i;
}
