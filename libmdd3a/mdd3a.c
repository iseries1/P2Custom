/**
 * @brief MDD3A motor driver
 * @author Michael Burmeister
 * @date February 22, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "propeller.h"
#include "smartpins.h"
#include "mdd3a.h"

int _M1A, _M1B, _M2A, _M2B;


void mdd3a_Init(int m1a, int m1b, int m2a, int m2b)
{
    int f;

    f = 500 | 500 << 16;

    _M1A = m1a;
    _M1B = m1b;
    _M2A = m2a;
    _M2B = m2b;

    _pinstart(_M1A, P_OE | P_PWM_TRIANGLE, f, 0);
    _pinstart(_M1B, P_OE | P_PWM_TRIANGLE, f, 0);
    _pinstart(_M2A, P_OE | P_PWM_TRIANGLE, f, 0);
    _pinstart(_M2B, P_OE | P_PWM_TRIANGLE, f, 0);

}

void mdd3a_SetPWM(int pwm1, int pwm2)
{
    int set1, set2;

    if (pwm1 < 1000)
        pwm1 = 1000;
    if (pwm1 > 2000)
        pwm1 = 2000;
    if (pwm2 < 1000)
        pwm2 = 1000;
    if (pwm2 > 2000)
        pwm2 = 2000;
    
    set1 = pwm1 - 1500;
    set2 = pwm2 - 1500;

    if (abs(set1) < 5)
        set1 = 0;
    if (abs(set2) < 5)
        set2 = 0;

    if (set1 < 0)
    {
        _wypin(_M1A, 0);
        _wypin(_M1B, -set1);
    }
    else
    {
        _wypin(_M1B, 0);
        _wypin(_M1A, set1);
    }

    if (set2 < 0)
    {
        _wypin(_M2A, 0);
        _wypin(_M2B, -set2);
    }
    else
    {
        _wypin(_M2B, 0);
        _wypin(_M2A, set2);
    }

}

void mdd3a_Stop(void)
{
    _pinf(_M1A);
    _pinf(_M1B);
    _pinf(_M2A);
    _pinf(_M2B);
}
