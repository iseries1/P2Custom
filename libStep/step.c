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
int volatile Busy;
int volatile Total = 0;
int Enable, Direction, Step;
int stack[5][60];

int Step_Start(int enable, int direction, int step)
{
  Enable = enable;
  Direction = direction;
  Step = step;
  Stepper[Total] = 0;
  _cogstart(doSteps, NULL, stack[Total], 60);
  _waitms(1000);
  return Total++;
}

void Step_Step(int motor, int steps)
{
  if (motor < 5)
    Stepper[motor] = steps;
}

void Step_Wait(void)
{
  while (Busy)
    usleep(100);
}

void Step_Disable(void)
{
  
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
  
  enable = Enable;
  direction = Direction;
  step = Step;
  driver = Total;
  _pinl(enable);
  _pinl(step);
  _pinl(direction);
  current = 0;
  Stepper[driver] = 0;
  
  while (1)
  {
    i = Stepper[driver];
    if (current != i)
    {
      s = 900;
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
      t = abs(current - i) - 1600;
      if (t < 0)
      {
        rampup = 800 + t/2;
        rampdown = rampup;
        if (t & 1)
          rampup++;
      }
      else
      {
        rampup = 800;
        rampdown = rampup;
      }
      for (i=0;i<rampup;i++)
      {
        _pinh(step);
        usleep(s--);
        _pinl(step);
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
        usleep(s++);
        _pinl(step);
        current += c;
      }
      Busy &= ~(1 << driver);
    }
    usleep(100);      
  }
}
