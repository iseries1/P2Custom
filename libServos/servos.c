/**
 * @brief Servo library driver
 * @author Michael Burmeister
 * @date January 8, 2021
 * @version 1.0
 * 
*/

#include <propeller.h>
#include <smartpins.h>
#include "servos.h"

int _SHigh = 2400;
int _SLow = 544;

void Servo_Enable(int pin, int position, int refresh)
{
    int freq = _clkfreq / 1000000;
    freq |= refresh << 16;
    
    _pinstart(pin, P_OE | P_PWM_SAWTOOTH, freq, position);
}

void Servo_Set(int pin, int position)
{
    if (position > _SHigh)
        return;

    if (position < _SLow)
        return;

    _wypin(pin, position);
}

void Servo_SetHighLow(int high, int low)
{
    _SHigh = high;
    _SLow = low;
}

void Servo_SetAngle(int pin, int angle)
{
    int a = (_SHigh - _SLow) * 10 / 180;

    a = a * angle / 10 + _SLow;
    Servo_Set(pin, a);
}
