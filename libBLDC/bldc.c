/**
 * @brief BLDC Motor Driver
 * @author Michael Burmeister
 * @date October 30, 2023
 * @version 1.0
 * @brief pins: ul, uh, vl, vh, wl, wh, xl, xh, su, sv, sw, sx, sc, hu, hv, hw
*/

#include <stdlib.h>
#include <propeller.h>
#include "bldc.h"

void BLDC_Left(int *);
void BLDC_Right(int *);

#define MAX 50


int Stack[100];
int Stack2[100];

char High[] = {0, 'W', 'W', 'V', 'V', 'U', 'U'};
char Low[] = {0, 'V', 'U', 'U', 'W', 'W', 'V'};
char HS[] = {0, 4, 2, 3, 6, 5, 1, 0};
char SH[] = {0, 6, 2, 3, 1, 5, 4, 0};
volatile int RStep, LStep;
volatile int RHall, LHall;
volatile int _Left = 0;
volatile int _Right = 0;
volatile int LTotal, RTotal;
volatile int LDirection, RDirection;
volatile int RTicks, LTicks;
volatile int RIdle, LIdle;


int BLDC_Init(int left_pins, int right_pins)
{
    int i;

    RTicks = 0;
    LTicks = 0;
    LDirection = 0;
    RDirection = 0;
    RIdle = 25;
    LIdle = 25;

    cogstart(BLDC_Left, &left_pins, Stack, sizeof(Stack));
    cogstart(BLDC_Right, &right_pins, Stack2, sizeof(Stack2));
    _waitms(500);

    BLDC_Enable();

    while (RHall <= 0)
        _waitms(250);

    return 1;
}

void BLDC_Hall(int *left, int *right)
{
    *left = LHall;
    *right = RHall;
}

void BLDC_LStep(int forward)
{
    if (forward > 0)
        LStep++;
    else
        LStep--;
    
    if (LStep > 6)
        LStep = 1;
    if (LStep < 1)
        LStep = 6;
}

void BLDC_RStep(int forward)
{
    if (forward > 0)
        RStep--;
    else
        RStep++;
    
    if (RStep > 6)
        RStep = 1;
    if (RStep < 1)
        RStep = 6;
}

void BLDC_Stop(void)
{
    LStep = 0;
    RStep = 0;
    _Left = 0;
    _Right = 0;
}

int BLDC_StepValue(void)
{
    return LStep;
}

int BLDC_Enable(void)
{
    LStep = HS[LHall];
    RStep = HS[RHall];
}

void BLDC_Move(int left, int right)
{
    if (left > 0)
        _Left = LHall;
    else
        _Left = 0;

    if (right > 0)
        _Right = RHall;
    else
        _Right = 0;
}

void BLDC_Ticks(int left, int right)
{
    LTotal = left;
    RTotal = right;
}

void BLDC_GetTicks(int *left, int *right)
{
    *left = LTicks;
    *right = RTicks;
}

void BLDC_SetDirection(int left, int right)
{
    if (left == 0)
    {
        if(LDirection != 1)
        {
            LDirection = 1;
        }
    }
    else
    {
        if (LDirection != -1)
        {
            LDirection = -1;
        }
    }

    if (right == 0)
    {
        if (RDirection != 1)
        {
            RDirection = 1;
        }
    }
    else
    {
        if (RDirection != -1)
        {
            RDirection = -1;
        }
    }
    if (LTotal > 0)
        _Left = LHall;
    if (RTotal > 0)
        _Right = RHall;
}

void BLDC_SetSpeed(int left, int right)
{
    if (left < 10)
        left = 10;
    if (right < 10)
        right = 10;
    if (left > 40)
        left = 40;
    if (right > 40)
        right = 40;
    LIdle = left;
    RIdle = right;
}

int BLDC_Status(void)
{
    if ((_Left > 0) || (_Right > 0))
        return 1;
    else
        return 0;
}



// Driver Code 
void BLDC_Left(int *par)
{
    int i;

    int pins;
    int low, high;
    int LT;
    int Ticks;
    LHall = 0;
    _Left = 0;
    LStep = 0;

    pins = *par;
    Ticks = 0;

    high = LIdle;

    while (1)
    {
        if (high != LIdle)
            high = LIdle;
        
        for (i=pins+8;i<pins+16;i++)
            _pinl(i);

        low = MAX - high;

        usleep(low);

        // Where are we
        LHall = _pinr(pins + 5) | (_pinr(pins + 6) << 1) | (_pinr(pins + 7) << 2);

        // lets move
        if (_Left > 0)
        {
            Ticks++;
            if (LHall == _Left)
            {
                LT++;
                if (LT < LTotal)
                {
                    BLDC_LStep(LDirection);
                    _Left = SH[LStep];
                }
                else
                    _Left = 0;
            
                if (Ticks > LTicks)
                    LTicks = Ticks;
                Ticks = 0;
            }
        }
        else
        {
            LT = 0;
        }

        if (Low[LStep] == 'U')
            _pinh(pins + 8);
        if (Low[LStep] == 'V')
            _pinh(pins + 10);
        if (Low[LStep] == 'W')
            _pinh(pins + 12);
        if (Low[LStep] == 'X')
            _pinh(pins + 14);

        if (High[LStep] == 'U')
            _pinh(pins + 9);
        if (High[LStep] == 'V')
            _pinh(pins + 11);
        if (High[LStep] == 'W')
            _pinh(pins + 13);
        if (High[LStep] == 'X')
            _pinh(pins + 15);
    
        usleep(high);
    }
}

void BLDC_Right(int *par)
{
    int i;

    int pins;
    int low, high;
    int RT;
    int Ticks;
    RHall = 0;
    _Right = 0;
    RStep = 0;

    pins = *par;
    Ticks = 0;

    high = RIdle;

    while (1)
    {
        if (high != RIdle)
            high = RIdle;
        
        for (i=pins+8;i<pins+16;i++)
            _pinl(i);

        low = MAX - high;

        usleep(low);

        // Where are we
        RHall = _pinr(pins + 5) | (_pinr(pins + 6) << 1) | (_pinr(pins + 7) << 2);

        // lets move
        if (_Right > 0)
        {
            Ticks++;
            if (RHall == _Right)
            {
                RT++;
                if (RT < RTotal)
                {
                    BLDC_RStep(RDirection);
                    _Right = SH[RStep];
                }
                else
                    _Right = 0;

                if (Ticks > RTicks)
                    RTicks = Ticks;
                Ticks = 0;
            }
        }
        else
        {
            RT = 0;
        }

        if (Low[RStep] == 'U')
            _pinh(pins + 8);
        if (Low[RStep] == 'V')
            _pinh(pins + 10);
        if (Low[RStep] == 'W')
            _pinh(pins + 12);
        if (Low[RStep] == 'X')
            _pinh(pins + 14);

        if (High[RStep] == 'U')
            _pinh(pins + 9);
        if (High[RStep] == 'V')
            _pinh(pins + 11);
        if (High[RStep] == 'W')
            _pinh(pins + 13);
        if (High[RStep] == 'X')
            _pinh(pins + 15);
    
        usleep(high);
    }
}

