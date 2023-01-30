/**
 * @file ens160.c 
 * @author Michael Burmeister
 * @brief ENS160 Air Quality Device Driver
 * @version 1.0
 * @date January 13, 2023
 */

#include "libens160/ens160_regs.h"
#include "ens160.h"
#include "i2c.h"

#define ENS160_ADDRESS_LOW  0x52
#define ENS160_ADDRESS_HIGH 0x53

#define ENS160_DEVICE_ID 0x0160


i2c_t *Ens;
char _Buffer[12];
int EnsAddr;

int ENS160_Init(int enclk, int endta)
{
    int i;

	Ens = I2C_Init(enclk, endta, I2C_FAST);

    EnsAddr = ENS160_ADDRESS_HIGH;

    i = I2C_In(Ens, EnsAddr, ENS160_PARTID, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];

    if (i != ENS160_DEVICE_ID)
        return -1;
    
    _Buffer[0] = 0;
    // clear config register (interupts)
    i = I2C_Out(Ens, EnsAddr, ENS160_CONFIG, 1, _Buffer, 1);

    _Buffer[0] = 0xcc;
    // clear output registers
    i = I2C_Out(Ens, EnsAddr, ENS160_COMMAND, 1, _Buffer, 1);

    _waitms(500);

    return 0;
}

int ENS160_Status(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DEVICE_STATUS, 1, _Buffer, 1);

    i = _Buffer[0];

    return i;
}

void ENS160_SetTemperature(int temp)
{
    int i;

    // Convert Celsius to Kelvin
    temp = (temp + 273) * 64;
    _Buffer[1] = temp >> 8;
    _Buffer[0] = temp;

    i = I2C_Out(Ens, EnsAddr, ENS160_TEMP_IN, 1, _Buffer, 2);
}

int ENS160_GetTemperature(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_T, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];
    // Convert Kelvin to Celsius
    i = i / 64 - 273;

    return i;
}

void ENS160_SetHumidity(int humidity)
{
    int i;

    humidity = humidity * 512;
    _Buffer[1] = humidity >> 8;
    _Buffer[0] = humidity;

    i = I2C_Out(Ens, EnsAddr, ENS160_RH_IN, 1, _Buffer, 2);

}

int ENS160_GetHumidity(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_RH, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];
    i = i / 512;
    return i;
}

void ENS160_SetMode(int mode)
{
    int i;

    if (mode == 3)
        mode = 0xf0;
    
    _Buffer[0] = mode;

    i = I2C_Out(Ens, EnsAddr, ENS160_OP_MODE, 1, _Buffer, 1);

    _waitms(500);
}

int ENS160_GetMode(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_OP_MODE, 1, _Buffer, 1);

    i = _Buffer[0];
    return i;
}

int ENS160_GetAQI(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_AQI, 1, _Buffer, 1);

    i = _Buffer[0];

    return i;
}

int ENS160_GetTVOC(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_TVOC, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];

    return i;
}

int ENS160_GetCO2(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_ECO2, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];

    return i;
}

int ENS160_GetETOH(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DATA_ETOH, 1, _Buffer, 2);

    i = _Buffer[1] << 8 | _Buffer[0];

    return i;
}

char *ENS160_GetWrite(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_GPR_WRITE, 1, _Buffer, 8);

    return _Buffer;
}

void ENS160_SetWrite(char *values)
{
    int i;

    i = I2C_Out(Ens, EnsAddr, ENS160_GPR_WRITE, 1, values, 8);

}

char *ENS160_GetRead(void)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_GPR_READ, 1, _Buffer, 8);

    return _Buffer;
}

short ENS160_Raw(unsigned short *r1, unsigned short *r2)
{
    int i;

    i = I2C_In(Ens, EnsAddr, ENS160_DEVICE_STATUS, 1, _Buffer, 1);

    if ((_Buffer[0] & 0x01) == 0)
        return 1;

    i = I2C_In(Ens, EnsAddr, ENS160_GPR_READ, 1, _Buffer, 8);

    *r1 = _Buffer[1] << 8 | _Buffer[0];
    *r2 = _Buffer[7] << 8 | _Buffer[6];

    return 0;
}


