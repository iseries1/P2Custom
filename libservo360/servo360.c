/**
 * @brief Driver for Servo 360
 * @author Michael Burmeister
 * @date Feburary 20, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <math.h>
#include <propeller.h>
#include "servo360.h"
#include "smartpins.h"

void DoServos(void *);


volatile struct S360 {
    int16_t Servo;
    int16_t Feedback;
    int16_t Angle;
    int16_t PrevAngle;
    int16_t TargetAngle;
    int16_t TargetTurns;
    int16_t Turns;
    int16_t TargetError;
    int16_t PWM;
} Servo360[9];

int Stack[100];


int Servo360_Start(int servo, int feedback)
{
    for (int i=0;i<9;i++)
        Servo360[i].Servo = -256;

    _cogstart(DoServos, NULL, Stack, 100);
    return Servo360_Add(servo, feedback);
}

void DoServos(void *par)
{
    while (1)
    {
        for (int i=0;i<9;i++)
        {
            if (Servo360[i].Servo >= 0)
            {
                UpdateAngle(i);
                if (Servo360[i].PWM != 0)
                    UpdatePosition(i);
                _wypin(Servo360[i].Servo, Servo360[i].PWM);
            }
        }
        DoChange();
        _waitus(100);
    }
}

void DoChange()
{
    uint32_t freq;

    for (int i=0;i<9;i++)
    {
        // add servo 
        if ((Servo360[i].Servo != -256) && (Servo360[i].Servo < -64))
        {
            Servo360[i].Servo = Servo360[i].Servo + 255;
            freq = (_clkfreq / 1000000) | (20000 << 16);
            _pinstart(Servo360[i].Servo, P_OE | P_PWM_SAWTOOTH, freq, Servo360[i].PWM);
        }

        // delete servo
        if (Servo360[i].Feedback < -64)
        {
            _wypin(Servo360[i].Servo, 0);
            _dirl(Servo360[i].Servo);
            Servo360[i].Servo = -256;
        }
    }
}

void UpdatePosition(int servo)
{
    int d, t;
    int a;

    d = Servo360[servo].TargetAngle + Servo360[servo].TargetTurns * 360;
    t = Servo360[servo].Angle + Servo360[servo].Turns * 360;

    d = d - t;

    if (abs(d) < 2)
    {
        Servo360[servo].PWM = 1500;
        return;
    }

    if (d > 210)
        d = 210;
    if (d < -210)
        d = -210;

    if ((d > -40) && (d < 40))
    {
        if (d < 0)
            d = -40;
        else
            d = 40;
    }

    Servo360[servo].PWM = 1500 - d;
}

void UpdateAngle(int servo)
{
    int i;
    uint32_t p;

    i = Servo360[servo].Feedback;

    __asm volatile {
    loop1   testp   i wc
    if_c    jmp     #loop1
    loop2   testp   i wc
    if_nc   jmp     #loop2
            getct   p
    loop3   testp   i wc
    if_c    jmp     #loop3
    }

    p = _cnt() - p;
    p = p / (_clkfreq/1000000) - 34;
    p = 360 * p / 1000;

    if (p > 360)
        p = 360;
    if (p < 0)
        p = 0;

    Servo360[servo].Angle = p;

    if (Servo360[servo].PrevAngle < 0)
    {
        Servo360[servo].PrevAngle = p;
        Servo360[servo].TargetAngle = p;
    }

    if ((p < 5) && (Servo360[servo].PrevAngle > 355))
    {
        Servo360[servo].Turns++;
    }

    if ((p > 355) && (Servo360[servo].PrevAngle < 5))
    {
        Servo360[servo].Turns--;
    }

    Servo360[servo].PrevAngle = p;
}

int Servo360_Add(int servo, int feedback)
{
    for (int i=0;i<9;i++)
    {
        if (Servo360[i].Servo == -256)
        {
            Servo360[i].PrevAngle = -1;
            Servo360[i].Turns = 0;
            Servo360[i].PWM = 0;
            Servo360[i].Feedback = feedback;
            Servo360[i].Servo = servo - 255;
            return i;
        }
    }
    return -1;
}

void Servo360_Remove(int servo)
{
    Servo360[servo].Feedback = Servo360[servo].Feedback - 255;
    return;
}

int Servo360_Angle(int servo)
{
    return Servo360[servo].Angle;
}

void Servo360_SetAngle(int servo, int angle)
{
    int t;
    int i;

    t = angle / 360;
    i = angle % 360;
    Servo360[servo].TargetTurns = t;
    Servo360[servo].TargetAngle = i;
}

int Servo360_GetTurns(int servo)
{
    return Servo360[servo].Turns;
}

void Servo360_ZeroTurns(int servo)
{
    Servo360[servo].Turns = 0;
    Servo360[servo].TargetTurns = 0;
}

void Servo360_SetPWM(int servo, int pwm)
{
    Servo360[servo].PWM = pwm;
}

int Servo360_Status(int servo)
{
    if (Servo360[servo].PWM != 1500)
        return Servo360[servo].PWM;
    
    return 0;
}

void Servo360_Enable(int servo, int enable)
{
    if (!enable)
        Servo360[servo].PWM = 0;
    else
    {
        Servo360[servo].PWM = 1500;
        Servo360[servo].TargetAngle = Servo360[servo].Angle;
        Servo360[servo].TargetTurns = Servo360[servo].Turns;
    }
}
