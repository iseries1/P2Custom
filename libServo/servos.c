/**
 * @brief Servo library driver
 * @author Michael Burmeister
 * @date January 8, 2021
 * @version 1.0
 * 
*/

#include <propeller.h>
#include "servos.h"


void Servo_Enable(int pin, int position, int refresh)
{
    int freq = _clkfreq / 1000000;
    freq |= 20000 << 16;
    
    _pinh(pin);
    _wrpin(pin, P_OE | P_PWM_SAWTOOTH);
    _wxpin(pin, freq);
    _dirh(pin);
    _wypin(pin, position);
}

void Servo_Set(int pin, int position)
{
    _wypin(pin, position);
}
