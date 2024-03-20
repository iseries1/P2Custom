/**
 * @brief Sparkfun Soil Moisture Sensor
 * @author Michael Burmeister
 * @date May 24, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include "soil.h"
#include "i2c.h"

#define ADDRESS 0x28
#define LED_OFF 0x00
#define LED_ON  0x01
#define VALUE   0x05
#define NOTHING 0x99


i2c_t *_soil;


int soil_Init(int clk, int dta)
{
    _soil = I2C_Init(clk, dta, I2C_STD);

    return I2C_Poll(_soil, ADDRESS);
}

void soil_Led(int state)
{
    char data;

    if (state == 0)
        data = LED_OFF;
    else
        data = LED_ON;
    
    data = I2C_Out(_soil, ADDRESS, 0x00, 0, &data, 1);
    printf("Wrote: %x\n", data);
}

int soil_Value(void)
{
    int i;
    char v[2];

    i = 0;
    while (i == 0)
        i = I2C_In(_soil, ADDRESS, VALUE, 1, v, 2);
    printf("S: %x\n", i);
    i = v[0] | (v[1] << 8);
    return i;
}
