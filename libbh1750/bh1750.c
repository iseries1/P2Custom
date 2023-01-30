/**
 * @brief bh1750 light sensor driver
 * @author Michael Burmeister
 * @date January 28, 2023
 * @version 1.0
 * 
*/

//#define DEBUG

#include <stdio.h>
#include "bh1750.h"
#include "i2c.h"

#define BH1750_ADDRESS_LOW 0x23
#define BH1750_ADDRESS_HIGH 0x5C


i2c_t *bh;
int bh_addr;

int BH1750_Init(int clk, int sda)
{
    int i;

    bh_addr = BH1750_ADDRESS_LOW;

    bh = I2C_Init(clk, sda, I2C_STD);

    i = I2C_Poll(bh, bh_addr);

    return i;
}

void BH1750_Cmd(char cmd)
{
    int i;

    i = I2C_Out(bh, bh_addr, 0, 0, &cmd, 1);
}

int BH1750_Read(void)
{
    int i;
    char _Buffer[4];

    _Buffer[0] = 0;
    _Buffer[1] = 0;

    i = I2C_In(bh, bh_addr, 0, 0, _Buffer, 2);

    i = _Buffer[0] << 8 | _Buffer[1];
    i = i / 12;
    i = i * 10;

    return i;
}
