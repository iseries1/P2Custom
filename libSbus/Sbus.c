/**
 * @brief Decode SBUS serial data from X8R receiver
 * @author Michael Burmeister
 * @date March 10, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "sbus.h"

void DoReceiveSbus(void *);

long Stack[50];
uint16_t CMin[17];
uint16_t CMax[17];
uint16_t Channel[18];
uint8_t Ss[26];
int Lock;
uint8_t SBusPin;
uint8_t volatile FailSafe;

void Sbus_Open(int pin)
{
    for (int i=0;i<17;i++)
    {
        CMin[i] = 200;
        CMax[i] = 1811;
    }
    SBusPin = pin;
    cogstart(DoReceiveSbus, NULL, Stack, 50);

}

uint16_t Sbus_GetChannel(int channel)
{
    uint16_t v;

    if (channel < 1)
        return 0;
    if (channel > 16)
        return 0;
    
    while (!_locktry(Lock));
    v = Channel[channel - 1];
    _lockclr(Lock);
    return v;
}

uint16_t Sbus_GetAdjust(int channel)
{
    uint16_t v;

    if (channel < 1)
        return 0;
    if (channel > 16)
        return 0;
    
    while (!_locktry(Lock));
    v = Channel[channel - 1] * 10/16 + 875;
    _lockclr(Lock);
    return v;
}

uint16_t Sbus_GetScaled(int channel)
{
    uint16_t v;

    if (channel < 1)
        return 0;
    if (channel > 16)
        return 0;
    
    while (!_locktry(Lock));
    v = Channel[channel - 1];
    v = 1000 * (v - CMin[channel - 1]) / (CMax[channel - 1] - CMin[channel - 1]) + 1000;
    _lockclr(Lock);
    return v;
}

void Sbus_SetScaled(int channel, uint16_t cmax, uint16_t cmin)
{
    if (channel < 1)
        return;
    if (channel > 16)
        return;
    
    CMax[channel - 1] = cmax;
    CMin[channel - 1] = cmin;
}

void DoReceiveSbus(void *par)
{
    int i;
    uint16_t c;
    int bitperiod;
    int wcnt;
    int bit;
    int pin;
    int pos;

    bitperiod = _clkfreq / 100000;
    Lock = _locknew();
    wcnt = bitperiod / 2;
    pin = SBusPin;

    pos = 0;
    while (1)
    {
        __asm volatile {
                    mov i, #10
                    mov c, #0
                    mov bit, #1
            loop1   testp pin  wc
            if_nc   jmp #loop1
                    waitx wcnt;
            loop2   waitx bitperiod
                    testp pin  wc
            if_nc   or  c, bit
                    shl bit, #1
                    djnz i, #loop2
        }
        c = c & 0xff; // dump parity stop bits
        if (c == 0x0f)
            pos = 0;
        Ss[pos++] = c;
        if (pos == 25)
        {
            DoChannel();
        }
        if (pos > 26)
            pos = 26;
    }
}

void DoChannel()
{
    int i;
    int chn;
    int bit1;
    int bit2;

    while (!_locktry(Lock));

    chn = 0;
    bit1 = 1;
    bit2 = 1;
    i = 1;
    Channel[0] = 0;
    
    while (chn < 16)
    {
        if ((Ss[i] & bit1) == bit1)
        {
            Channel[chn] = Channel[chn] | bit2;
        }
        bit1 = bit1 << 1;
        if (bit1 > 0x80)
        {
            bit1 = 1;
            i++;
        }
        bit2 = bit2 << 1;
        if (bit2 > 0x400)
        {
            bit2 = 1;
            chn++;
            Channel[chn] = 0;
        }
    }
    _lockclr(Lock);
    if (Ss[23] & 0x1)
        Channel[17] = 1800;
    else
        Channel[17] = 1200;
    if (Ss[23] & 0x02)
        Channel[18] = 1800;
    else
        Channel[18] = 1200;
    FailSafe = Ss[23] & 0x08;
}