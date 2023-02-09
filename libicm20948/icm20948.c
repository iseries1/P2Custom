/**
 * @file icm20948.c
 * @author Michael Burmeister
 * @brief ICM-20948 9DOF IMU
 * @version 1.0
 * @date January 15, 2023
 */

#include <stdio.h>
#include "icm20948_reg.h"
#include "icm20948.h"
#include "i2c.h"

#define ICM_DEV_WHO_AM_I  0xEA
#define ICM_ADDRESS_LOW   0x68
#define ICM_ADDRESS_HIGH  0x69
#define ICM_ADDRESS_MAG   0x0C


int icm_addr;
int mag_addr;
i2c_t *icm;
char _Buffer[12];


int ICM20948_Init(int icmclk, int icmdta)
{
    int i;

    icm_addr = ICM_ADDRESS_HIGH;
    mag_addr = ICM_ADDRESS_MAG;

    icm = I2C_Init(icmclk, icmdta, I2C_FAST);
    
    i = I2C_In(icm, icm_addr, ICM_WHO_AM_I, 1, _Buffer, 1);

    if (_Buffer[0] != ICM_DEV_WHO_AM_I)
        return -1;
    
    ICM20948_Mode(8); // 9 Axis Mode
    ICM20948_I2CMaster(0);
    ICM20948_DMP(0);
    ICM20948_FIFO(0);
    ICM20948_EnableLowPower(0); // full power

}

void ICM20948_Mode(int mode)
{
    int i;

    _Buffer[0] = mode;

    i = I2C_Out(icm, icm_addr, ICM_FIFO_MODE, 1, _Buffer, 1);

}

void ICM20948_DMP(int enable)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0x7f;
    
    if (enable)
        _Buffer[0] = _Buffer[0] | 0x80;
    
    i = I2C_Out(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_FIFO(int enable)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xbf;

    if (enable)
        _Buffer[0] = _Buffer[0] | 0x40;
    
    i = I2C_Out(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_I2CMaster(int enable)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
    if (enable)
        _Buffer[0] = _Buffer[0] | 0x20;
    else
        _Buffer[0] = _Buffer[0] & 0xdf;
    
    i = I2C_Out(icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_Reset()
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] | 0x80;

    i = I2C_Out(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

void ICM20948_Sleep(int mode)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0x3f;
    if (mode)
        _Buffer[0] = _Buffer[0] | 0x40;
    
    i = I2C_Out(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

void ICM20948_EnableLowPower(int mode)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xdf;
    if (mode)
        _Buffer[0] = _Buffer[0] | 0x20;
    
    i = I2C_Out(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

void ICM20948_SetClock(int source)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xf8;
    _Buffer[0] = _Buffer[0] | (source & 0x07);
    
    i = I2C_Out(icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

int ICM20948_Interupts(void)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_INT_STATUS, 1, _Buffer, 4);

    i = _Buffer[0];
    return i;
}

void ICM20948_ByPass(int mode)
{
    int i;

    _Buffer[0] = mode << 1;

    i = I2C_Out(icm, icm_addr, ICM_INT_PIN_CFG, 1, _Buffer, 1);
}

int ICM20948_Delay(void)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_DELAY_TIME, 1, _Buffer, 2);

    i = _Buffer[0] << 8 | _Buffer[1];

    return i;
}

void ICM20948_Accel(int *x, int *y, int *z)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_ACCEL_XOUT, 1, _Buffer, 6);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

}

void ICM20948_Gyro(int *x, int *y, int *z)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_GYRO_XOUT, 1, _Buffer, 6);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

}

int ICM20948_Temp(void)
{
    int i;

    i = I2C_In(icm, icm_addr, ICM_TEMP_OUT, 1, _Buffer, 2);

    i = _Buffer[0] << 8 | _Buffer[1];

    return i;
}

void ICM20948_SetHW(int fix)
{
    int i;

    _Buffer[0] = fix;
    i = I2C_Out(icm, icm_addr, ICM_HW_FIX, 1, _Buffer, 1);
}

void ICM20948_SetFIFOPriority(int priority)
{
    int i;

    _Buffer[0] = priority;
    i = I2C_Out(icm, icm_addr, ICM_FIFO_PRIORITY, 1, _Buffer, 1);
}

void ICM20948_ResetFifo(void)
{
    int i;

    _Buffer[0] = 0x1f;
    i = I2C_Out(icm, icm_addr, ICM_FIFO_RST, 1, _Buffer, 1);

    _Buffer[0] = 0x1e;
    i = I2C_Out(icm, icm_addr, ICM_FIFO_RST, 1, _Buffer, 1);
}

void ICM20948_ConfigGyro(int filter, int range, int enable)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = filter << 3 | range << 1 | enable;

    i = I2C_Out(icm, icm_addr, ICM_GYRO_CONFIG, 1, _Buffer, 1);
}

void ICM20948_ConfigAccel(int filter, int range, int enable)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = filter << 3 | range << 1 | enable;

    i = I2C_Out(icm, icm_addr, ICM_ACCEL_CONFIG, 1, _Buffer, 1);
}

void ICM20948_SetDMPAddress(int addr)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = addr >> 8;
    _Buffer[1] = addr;
    i = I2C_Out(icm, icm_addr, ICM_DMP_ADDR, 1, _Buffer, 2);

    ICM20948_SetBank(0);
}

void ICM20948_I2CMultiMaster(int enable)
{
    int i;

    ICM20948_SetBank(3);
    i = I2C_In(icm, icm_addr, ICM_I2C_MASTER, 1, _Buffer, 1);

    if (enable)
        _Buffer[0] = _Buffer[0] | 0x80;
    else
        _Buffer[0] = _Buffer[0] & 0x7f;

    i = I2C_Out(icm, icm_addr, ICM_I2C_MASTER, 1, _Buffer, 1);

    ICM20948_SetBank(0);
}

void ICM20948_I2CMasterODR(int odr)
{
    int i;

    ICM20948_SetBank(3);
    
    _Buffer[0] = odr;

    i = I2C_Out(icm, icm_addr, ICM_I2C_MST_ODR, 1, _Buffer, 1);

    ICM20948_SetBank(0);
}

void ICM20948_I2CMasterClock(int freq)
{
    int i;

    ICM20948_SetBank(3);
    i = I2C_In(icm, icm_addr, ICM_I2C_MASTER, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0x70;

    switch (freq)
    {
        case 0 : _Buffer[0] | 0x00;
            break;
        case 1 : _Buffer[0] | 0x03;
            break;
        case 2 : _Buffer[0] | 0x07;
            break;
        case 3 : _Buffer[0] | 0x08;
            break;
        case 4 : _Buffer[0] | 0x0C;
            break;
    }

    i = I2C_Out(icm, icm_addr, ICM_I2C_MASTER, 1, _Buffer, 1);

    ICM20948_SetBank(0);
}

int ICM20948_MagWhoAmI(void)
{
    int i;

    _Buffer[0] = 0;
    i = I2C_In(icm, mag_addr, ICM_MAG_ID, 1, _Buffer, 1);

    i = _Buffer[0];
    return i;
}

int ICM20948_Mag(short *x, short *y, short *z)
{
    int i;

    i = I2C_In(icm, mag_addr, ICM_MAG_XOUT, 1, _Buffer, 6);

    *x = _Buffer[1] << 8 | _Buffer[0];
    *y = _Buffer[3] << 8 | _Buffer[2];
    *z = _Buffer[5] << 8 | _Buffer[4];

    i = I2C_In(icm, mag_addr, ICM_MAG_STATUS2, 1, _Buffer, 1);
    i = (_Buffer[0] & 0x08) >> 3;

    return i;
}

int ICM20948_MagCtrl(void)
{
    int i;

    i = I2C_In(icm, mag_addr, ICM_MAG_CTRL2, 1, _Buffer, 1);

    i = _Buffer[0];
    return i;
}

void ICM20948_MagMode(int mode)
{
    int i;

    _Buffer[0] = mode;
    i = I2C_Out(icm, mag_addr, ICM_MAG_CTRL2, 1, _Buffer, 1);
}

int ICM20948_MagHidden(short *x, short *y, short *z)
{
    int i, j;

    j = 0;
    while (j == 0)
    {
        i = I2C_In(icm, mag_addr, ICM_MAG_RSV2, 1, _Buffer, 8);

        j = _Buffer[1]; // mirror of ICM_MAG_STATUS
    }

    *x = _Buffer[3] << 8 | _Buffer[2];
    *y = _Buffer[5] << 8 | _Buffer[4];
    *z = _Buffer[7] << 8 | _Buffer[6];

    return j;
}

void ICM20948_SetBank(int bank)
{
    int i;

    _Buffer[0] = bank << 4;

    i = I2C_Out(icm, icm_addr, ICM_BANK_SELECT, 1, _Buffer, 1);
}

void ICM20948_WriteMemory(short addr, char *data)
{
    int i;

    _Buffer[0] = addr;
    i = I2C_Out(icm, icm_addr, ICM_MEM_START, 1, _Buffer, 1);

    i = I2C_Out(icm, icm_addr, ICM_MEM_RW, 1, data, 16);
}

void ICM20948_WriteMemorySize(short addr, char *data, short size)
{
    int i;

    _Buffer[0] = addr;
    i = I2C_Out(icm, icm_addr, ICM_MEM_START, 1, _Buffer, 1);

    i = I2C_Out(icm, icm_addr, ICM_MEM_RW, 1, data, size);
}

void ICM20948_ReadMemory(short addr, char *data)
{
    int i;

    _Buffer[0] = addr;
    i = I2C_Out(icm, icm_addr, ICM_MEM_START, 1, _Buffer, 1);

    i = I2C_In(icm, icm_addr, ICM_MEM_RW, 1, data, 16);
}

void ICM20948_SetMemBank(int bank)
{
    int i;

    _Buffer[0] = bank;
    i = I2C_Out(icm, icm_addr, ICM_MEM_BANK, 1, _Buffer, 1);
}

void ICM20948_SetSlave(int slave, int addr, int in, int reg, int read, int swap, int write, int grp, int len, int data)
{
    int i, j;

    j = slave * 4 + 3;

    ICM20948_SetBank(3);

    // Slave Address
    _Buffer[0] = in << 7 | addr;
    i = I2C_Out(icm, icm_addr, j, 1, _Buffer, 1);

    // Slave Register
    _Buffer[0] = reg;
    i = I2C_Out(icm, icm_addr, j + 1, 1, _Buffer, 1);

    // Slave Control
    _Buffer[0] = read << 7 | swap << 6 | write << 5 | grp << 4 | len;
    i = I2C_Out(icm, icm_addr, j + 2, 1, _Buffer, 1);

    // Slave Data Out value
    _Buffer[0] = data;
    i = I2C_Out(icm, icm_addr, j + 3, 1, _Buffer, 1);

    ICM20948_SetBank(0);
}

void ICM20948_DMPEnable(int enable)
{

    // Read Mag values
    ICM20948_SetSlave(0, mag_addr, 1, ICM_MAG_RSV2, 1, 1, 1, 1, 10, 0);
    // Do Single Mag Update
    ICM20948_SetSlave(1, mag_addr, 0, ICM_MAG_CTRL2, 1, 0, 1, 0, 1, 1);
    // Set ODR to 68Hz
    ICM20948_I2CMasterODR(0x04);
    ICM20948_SetClock(1);
    ICM20948_FIFO(0);
    ICM20948_DMP(0);
    ICM20948_ConfigGyro(0, 3, 1);
    ICM20948_ConfigAccel(0, 1, 1);
    ICM20948_ResetFifo();
    ICM20948_SetDMPAddress(0x1000);
    ICM20948_SetHW(0x48);
    ICM20948_ReadMemory(0x1e0, _Buffer);
    _Buffer[0] = 0x04;
    _Buffer[1] = 0x00;
    _Buffer[2] = 0x00;
    _Buffer[3] = 0x00;
    ICM20948_WriteMemory(0x1e0, _Buffer);
    ICM20948_ReadMemory(0x4f0, _Buffer);
    _Buffer[4] = 0x00;
    _Buffer[5] = 0x04;
    _Buffer[6] = 0x00;
    _Buffer[7] = 0x00;
    ICM20948_WriteMemory(0x4f0, _Buffer);
    
}

