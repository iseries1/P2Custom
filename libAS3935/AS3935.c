/**
 * @brief Driver Program for AS3935 Lightning Detector
 * @author Michael Burmeister
 * @date December 23, 2023
 * @version 1.0
 * 
 */

#include <stdio.h>
#include <propeller.h>
#include <simpletools.h>
#include "as3935.h"
#include "AS3935_reg.h"

unsigned char ASRead(int);
void ASWrite(int, int);


unsigned char _AScs;
unsigned char _ASclk;
unsigned char _ASmosi;
unsigned char _ASmiso;


unsigned char AS3935_Init(int cs, int clk, int miso, int mosi)
{
    int i;

    _AScs = cs;
    _ASclk = clk;
    _ASmiso = miso;
    _ASmosi = mosi;

    _pinh(_AScs);
    _pinl(_ASclk);
    
    i = AS3935_Calibrate();
    _pinl(56);
    AS3935_ClearStats();
    _pinl(57);
    AS3935_SetDefault();

    return i;
}

void AS3935_SetPower(int state)
{
    int i;

    i = ASRead(AS3935_AFE_GB);
    i = i & 0xfe;
    i = i | state;
    ASWrite(AS3935_AFE_GB, i);
}

unsigned char AS3935_ReadPower(void)
{
    int i;

    i = ASRead(AS3935_AFE_GB);
    i = i & 0xfe;
    return i;
}

void AS3935_SetAFE(int value)
{
    int i;

    i = ASRead(AS3935_AFE_GB);
    i = i & 0x3E;
    if (value == 0)
        i = i | 0x24;
    else
        i = i | 0x1C;
    ASWrite(AS3935_AFE_GB, i);
}

unsigned char AS3935_ReadAFE(void)
{
    int i;

    i = ASRead(AS3935_AFE_GB);
    printf("What: %x\n", i);
    i = i & 0x3E;
    if (i == 0x24)
        i = 0;
    else
        i = 1;
    return i;
}

void AS3935_SetFloor(int floor)
{
    int i;

    i = ASRead(AS3935_NOISE);
    i = i & 0x8f;
    i = i | (floor << 4);
    ASWrite(AS3935_NOISE, i);
}

unsigned char AS3935_ReadFloor(void)
{
    int i;

    i = ASRead(AS3935_NOISE);
    i = i & 0x70;
    i = i >> 4;
    return i;
}

void AS3935_SetWatchdog(int value)
{
    int i;

    i = ASRead(AS3935_NOISE);
    i = i & 0xf0;
    i = i | value;
    ASWrite(AS3935_NOISE, i);
}

unsigned char AS3935_ReadWatchdog(void)
{
    int i;

    i = ASRead(AS3935_NOISE);
    i = i & 0x0f;
    return i;
}

void AS3935_ClearStats(void)
{
    int i;

    i = ASRead(AS3935_STATS);
    i = i & 0xbf;
    i = i | 0x40;
    ASWrite(AS3935_STATS, i);
}

void AS3935_SetLightning(int strikes)
{
    int i;

    i = ASRead(AS3935_STATS);
    i = i & 0xcf;
    i = i | (strikes << 4);
    ASWrite(AS3935_STATS, i);
}

unsigned char AS3935_ReadLightning(void)
{
    int i;

    i = ASRead(AS3935_STATS);
    i = i & 0x30;
    i = i >> 4;
    return i;
}

void AS3935_SetSpikeRejection(int value)
{
    int i;

    i = ASRead(AS3935_STATS);
    i = i & 0xf0;
    i = i | value;
    ASWrite(AS3935_STATS, i);
}

unsigned char AS3935_ReadSpikeRejection(void)
{
    int i;

    i = ASRead(AS3935_STATS);
    i = i & 0x0f;
    return i;
}

void AS3935_SetLCODivder(int divider)
{
    int i;

    i = ASRead(AS3935_MASK);
    i = i & 0x3f;
    i = i | (divider << 6);
    ASWrite(AS3935_MASK, i);
}

unsigned char AS3935_ReadLCODivider(void)
{
    int i;

    i = ASRead(AS3935_MASK);
    i = i & 0xc0;
    i = i >> 6;
    return i;
}

unsigned char AS3935_ReadInterrupt(void)
{
    int i;

    i = ASRead(AS3935_MASK);
    i = i & 0x0f;
    return i;
}

unsigned long AS3935_ReadLightingEnergy(void)
{
    int i;

    i = ASRead(AS3935_ENERGY);
    i = i & 0x1f;
    i = i << 8;
    i = i | ASRead(AS3935_LIGHTNINGH);
    i = i << 8;
    i = i | ASRead(AS3935_LIGHTNINGL);
    return i;
}

unsigned char AS3935_ReadDistance(void)
{
    int i;

    i = ASRead(AS3935_DISTANCE);
    i = i & 0x3f;
    return i;
}

void AS3935_SetIRQ(int value)
{
    int i;

    i = ASRead(AS3935_TUNE);
    i = i & 0x1f;
    i = i | (value << 5);
    ASWrite(AS3935_TUNE, i);
}

unsigned char AS3935_ReadIRQ(void)
{
    int i;

    i = ASRead(AS3935_TUNE);
    i = i & 0xe0;
    i = i >> 5;
    return i;
}

void AS3935_SetCapacitance(int value)
{
    int i;

    i = ASRead(AS3935_TUNE);
    i = i & 0xf0;
    i = i | value;
    ASWrite(AS3935_TUNE, i);
}

unsigned char AS3935_ReadCapacitance(void)
{
    int i;

    i = ASRead(AS3935_TUNE);
    i = i & 0x0f;
    return i;
}

unsigned char AS3935_ReadCalibration(void)
{
    int i;

    i = ASRead(AS3935_TRCO);
    i = i & 0xc0;
    i = i << 2;
    i = i | ASRead(AS3935_SRCO);
    i = i >> 6;
    return i;
}

unsigned char AS3935_Calibrate(void)
{
    ASWrite(AS3935_CALIBRATE, AS3935_COMMAND);
    _waitms(2);
    AS3935_SetIRQ(2);
    _waitms(2);
    AS3935_SetIRQ(0);
    return AS3935_ReadCalibration();
}

void AS3935_SetDefault(void)
{
    ASWrite(AS3935_DEFAULTS, AS3935_COMMAND);
}


// Low level functions

unsigned char ASRead(int reg)
{
    unsigned char v;

    reg = reg | 0x40; // read code
    _pinl(_AScs);
    shift_out(_ASmosi, _ASclk, MSBFIRST, 8, reg);
    v = shift_in(_ASmiso, _ASclk, MSBPRE, 9);
    _pinh(_AScs);
    _pinl(_AScs);
    _pinh(_AScs);
    return v;
}

void ASWrite(int reg, int data)
{
    reg = reg | 0x00;
    _pinl(_AScs);
    shift_out(_ASmosi, _ASclk, MSBFIRST, 8, reg);
    shift_out(_ASmosi, _ASclk, MSBFIRST, 8, data);
    _pinh(_AScs);
}

