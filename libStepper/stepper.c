/**
 * @brief Drive Stepper Motors 
 * @author Michael Burmeister
 * @date March 11, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "stepper.h"
#include "smartpins.h"

void DoStepper(void *);


int Enable;
int Direction;
int Step;
int volatile Total = 0;
int Motors[5];

int Stepper_Start(int enable, int direction, int step)
{
    int i;

    Motors[Total] = (enable << 16) | (direction << 8) | step;
    _dirh(enable);
    _dirh(direction);
    _dirh(step);

    _pinh(enable);
    _pinh(direction);
    _pinl(step);

    _pinstart(step, P_OE | P_NCO_FREQ, 2, 0);

    return Total++;
}

void Stepper_Enable(int motor, int enable)
{
    int m;

    m = Motors[motor] >> 16;
    if (enable == 0)
        _pinh(m);
    else
        _pinl(m);
}

void Stepper_Direction(int motor, int direction)
{
    int m;

    m = ((Motors[motor] >> 8) & 0xff);
    if (direction == 0)
        _pinh(m);
    else
        _pinl(m);
}

void Stepper_Speed(int motor, int speed)
{
    int m;

    m = (Motors[motor] & 0xff);
    _wypin(m, speed * 4295);
}
