/**
 * @brief Control Stepper motors
 * @author Michael Burmeister
 * @date November 29, 2020
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "step.h"

#define ENABLEA 16
#define STEPA 17
#define DIRECTIONA 18
#define ENABLEB 19
#define STEPB 20
#define DIRECTIONB 21



int main()
{
    int m, n;
    
  m = Step_Start(ENABLEA, DIRECTIONA, STEPA);
  n = Step_Start(ENABLEB, DIRECTIONB, STEPB);
  
  printf("Starting %d \n", m);
  Step_Step(m, 2000);
  Step_Step(n, -5000);
  Step_Wait();
  printf("Step 1\n");
  _waitms(5000);
  Step_Step(m, -2000);
  Step_Step(n, 5000);
  Step_Wait();
  printf("Step 2\n");
  _waitms(5000);
  Step_Step(m, 0);
  Step_Step(n, 0);
  Step_Wait();
  
  printf("Done\n");
  
  while(1)
  {
    _waitms(1000);    
  }  
}
