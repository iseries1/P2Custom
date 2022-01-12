/**
 * @brief Driver Library for PCA9685 LED/Servo driver
 * @author Michael Burmeister
 * @date November 14, 2021
 * @version 1.0
 * 
*/

#include "PCA9685.h"
#include "pca9685reg.h"
#include "i2c.h"
#include <stdio.h>
#include <propeller.h>

void PCA9685_WriteByte(int, unsigned char);
void PCA9685_WriteBytes(int, unsigned char*, int);
unsigned char PCA9685_ReadByte(int);
int PCA9685_ReadBytes(int, unsigned char*, int);

unsigned char _Buffer[256];
i2c_t *PCA9685dev;


void PCA9685_open(int CLK, int DTA)
{
    PCA9685dev = I2C_Init(CLK, DTA, I2C_FAST);
    PCA9685_reset();
}

void PCA9685_reset()
{
    PCA9685_WriteByte(PCA9685_MODE1, MODE1_RESTART | MODE1_AUTOINC);
    _waitms(10);
}

unsigned char PCA9685_readMode(int mode)
{
    int i;

    i = 0;

    if (mode == 1)
        i = PCA9685_ReadByte(PCA9685_MODE1);
    if (mode == 2)
        i = PCA9685_ReadByte(PCA9685_MODE2);
    
    return i;
}

unsigned char PCA9685_getPrescaler()
{
    int i;

    i = PCA9685_ReadByte(PCA9685_PRESCALE);

    return i;
}

void PCA9685_setPrescaler(unsigned char prescale)
{
    int i;

    i = PCA9685_readMode(1);
    PCA9685_WriteByte(PCA9685_MODE1, i | MODE1_SLEEP);
    PCA9685_WriteByte(PCA9685_PRESCALE, prescale);
    PCA9685_WriteByte(PCA9685_MODE1, i);
    _waitms(5);
}

int PCA9685_getPWM(unsigned char LED)
{
    int i;

    i = LED * 4;
    PCA9685_ReadBytes(PCA9685_LED0_ON_L + i, _Buffer, 4);

    i = _Buffer[2] | (_Buffer[3] << 8);

    return i;
}

void PCA9685_setAllPWM(int value)
{
    int i;

    _Buffer[0] = 0;
    _Buffer[1] = 0;
    _Buffer[2] = value;
    _Buffer[3] = value >> 8;
    PCA9685_WriteBytes(PCA9685_ALLLED_ON_L, _Buffer, 4);
}

void PCA9685_setPWM(unsigned char LED, int value)
{
    int i;

    i = LED * 4;
    _Buffer[0] = 0;
    _Buffer[1] = 0;
    _Buffer[2] = value;
    _Buffer[3] = value >> 8;

    PCA9685_WriteBytes(PCA9685_LED0_ON_L + i, _Buffer, 4);
}


/**
 * Low level IO code
 */

void PCA9685_WriteByte(int reg, unsigned char dta)
{
    int i;

    i = I2C_Out(PCA9685dev, PCA9685_ADDRESS, reg, 1, &dta, 1);
}

void PCA9685_WriteBytes(int reg, unsigned char *dta, int len)
{
    int i;

    i = I2C_Out(PCA9685dev, PCA9685_ADDRESS, reg, 1, dta, len);
}

unsigned char PCA9685_ReadByte(int reg)
{
    int i;

    i = I2C_In(PCA9685dev, PCA9685_ADDRESS, reg, 1, _Buffer, 1);

    return _Buffer[0];
}

int PCA9685_ReadBytes(int reg, unsigned char *dta, int len)
{
    int i;
    
    i = I2C_In(PCA9685dev, PCA9685_ADDRESS, reg, 1, dta, len);

    return i;
}
