/**
 * @brief Control Stepper motors
 * @author Michael Burmeister
 * @date November 29, 2020
 * @version 1.0
 * 
*/

#include <stdlib.h>
#include <propeller.h>
#include "step.h"

void doSteps(void *);



int volatile Stepper[5];
int volatile Function[5];
int volatile Busy;
int volatile Total = 0;
int Enable, Direction, Step;
int stack[5][60];

int Step_Start(int enable, int direction, int step)
{
  Enable = enable;
  Direction = direction;
  Step = step;
  _cogstart(doSteps, NULL, stack[Total], 60);
  _waitms(500);
  return Total++;
}

void Step_Step(int motor, int steps)
{
  if (motor < 5)
    Stepper[motor] = steps;
}

void Step_Wait(void)
{
  usleep(100);
  while (Busy)
    usleep(100);
}

void Step_Disable(int motor)
{
  Function[motor] = 1;
}

void Step_Enable(int motor)
{
  Function[motor] = 3;
}

int Step_Number(int motor)
{
  return Stepper[motor];
}

int Step_Clear(int motor)
{
  Function[motor] = 2;
}

void doSteps(void *par)
{
  int enable;
  int direction;
  int step;
  int current;
  int driver;
  int i, s, c, t;
  int rampup, rampdown;
  int ramp;
  int min;

  enable = Enable;
  direction = Direction;
  step = Step;
  ramp = 1024;
  min = 256;
  driver = Total;
  _pinl(enable);
  _pinl(step);
  _pinl(direction);
  current = 0;
  Stepper[driver] = 0;
  Function[driver] = 0;

  while (1)
  {
    if (Function[driver] > 0)
    {
      if (Function[driver] == 1) // disable
      {
        _pinh(enable);
      }

      if (Function[driver] == 2) // zero
      {
        current = 0;
        Stepper[driver] = 0;
      }

      if (Function[driver] == 3) // enable
      {
        _pinl(enable);
      }
      Function[driver] = 0;
    }
    
    i = Stepper[driver];
    if (current != i)
    {
      s = ramp + min;
      Busy |= (1 << driver);
      if (current > i)
      {
        _pinh(direction);
        c = -1;
      }
      else
      {
        _pinl(direction);
        c = 1;
      }
      t = abs(current - i) - (ramp * 2);
      if (t < 0)
      {
        rampup = ramp + (t / 2);
        rampdown = rampup;
        if (t & 1)
          rampup++;
      }
      else
      {
        rampup = ramp;
        rampdown = rampup;
      }
      for (i=0;i<rampup;i++)
      {
        _pinh(step);
        usleep(s);
        _pinl(step);
        s--;
        current += c;
      }
      for (i=0;i<t;i++)
      {
        _pinh(step);
        usleep(s);
        _pinl(step);
        current += c;
      }
      for (i=0;i<rampdown;i++)
      {
        _pinh(step);
        usleep(s);
        _pinl(step);
        s++;
        current += c;
      }
      Busy &= ~(1 << driver);
    }
    usleep(25);      
  }
}
