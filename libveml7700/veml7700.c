/**
 * @author Michael Burmeister
 * @brief VEML7700 Light Sensor Driver
 * @version 1.0
 * @date December 02, 2023
 */

#include <stdio.h>
#include <propeller.h>
#include "i2c.h"
#include "veml7700.h"

#define VEMLADDRESS 0x10


int SG[] = {2304, 1152, 18432, 9216};

i2c_t *veml;


int VEML7700_Init(int clk, int dta)
{
    int i;

    veml = I2C_Init(clk, dta, I2C_FAST);

    i = I2C_Poll(veml, VEMLADDRESS);
    if (i != 0)
        return i;
    
    i = 0x00;
    i = i | 00 << 12; // Sensitivity mode selection 1
    i = i | 00 << 9;  // ALS integration time setting 100ms
    i = i | 00 << 5;  // ALS persistence protect number setting 1
    i = i | 00 << 1;  // ALS interrupt enable setting disabled
    i = i | 00 << 0;  // ALS shut down setting power on

    I2C_Out(veml, VEMLADDRESS, 0x00, 1, i, 2);

    return 1;
}

void VEML7700_Mode(int sense, int inte, int pers, int inter, int power)
{
    int value;
    int i;

    value = sense << 12;

    switch(inte)
    {
        case 25: i = 12;
            break;
        case 50: i = 8;
            break;
        case 100: i = 0;
            break;
        case 200: i = 1;
            break;
        case 400: i = 2;
            break;
        case 800: i = 3;
            break;
        default: i = 0;
    }

    value = value | i << 9;
    value = value | pers << 5;
    value = value | inter << 1;
    value = value | power;

    I2C_Out(veml, VEMLADDRESS, 0x00, 1, i, 2);

}

void VEML7700_Threshold(int high, int low)
{
    I2C_Out(veml, VEMLADDRESS, 0x01, 1, high, 2);
    I2C_Out(veml, VEMLADDRESS, 0x02, 1, low, 2);
}

void VEML7700_PowerMode(int mode, int enable)
{

    mode = mode - 1;
    mode = mode << 1;
    mode = mode | enable;

    I2C_Out(veml, VEMLADDRESS, 0x03, 1, mode, 2);
}

int VEML7700_GetALS(void)
{
    int value;

    I2C_In(veml, VEMLADDRESS, 0x04, 1, &value, 2);

    return value;
}

int VEML7700_GetWhite(void)
{
    int value;

    I2C_In(veml, VEMLADDRESS, 0x05, 1, &value, 2);

    return value;
}

int VEML7700_GetLux(void)
{
    int value;
    int i;
    int lux;

    I2C_In(veml, VEMLADDRESS, 0, 1, &value, 2);

    i = value >> 11;
    lux = SG[i];

    i = value >> 6;
    i = i & 0x0f;

    switch (i)
    {
        case 12: lux = lux;
            break;
        case 8: lux = lux >> 1;
            break;
        case 0: lux = lux >> 2;
            break;
        case 1: lux = lux >> 3;
            break;
        case 2: lux = lux >> 4;
            break;
        case 3: lux = lux >> 5;
            break;
        default: lux = lux;
    }

    value = VEML7700_GetALS();
    value = value * lux / 10000;

    return value;
}

