/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/

#include "ina260_reg.h"
#include "ina260.h"
#include "simpletools.h"
#include "i2c.h"

int INA260_Read(int);
void INA260_Write(int, int);


unsigned char _INA260;
i2c_t *_INA260C;

unsigned short INA260_open(char clk, char data)
{
  int i;
  
  _INA260 = INA260_I2CADDR;

  _INA260C = I2C_Init(clk, data, I2C_STD);
  
  i = INA260_Read(INA260_MFGID);

  return i;
}

short INA260_getCurrent(void)
{
  int v;
  
  v = INA260_Read(INA260_CURRENT);
  v = v * 125;
  
  return v/100;
}

short INA260_getVoltage(void)
{
  int v;
  
  v = INA260_Read(INA260_VOLTAGE);
  v = v * 125;
  
  return v/100;
}

short INA260_getPower(void)
{
  int v;
  
  v = INA260_Read(INA260_POWER);
  v = v * 10;

  return v;
}

void INA260_setMode(int mode)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0xfff8;
  v = v | mode;

  INA260_Write(INA260_CONFIG, v);
}

int INA260_getMode(void)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0x07;

  return v;
}

void INA260_configCurrent(int time)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0xffc7;
  v = v | (time << 3);

  INA260_Write(INA260_CONFIG, v);
}

int INA260_getConfigCurrent(void)
{
  int i;
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0x0038;
  v = v >> 3;
  return v;
}

void INA260_configVoltage(int time)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0xfe3f;
  v = v | (time << 6);

  INA260_Write(INA260_CONFIG, v);
}

int INA260_getConfigVoltage(void)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0x01c0;
  v = v >> 6;
  return v;
}

void INA260_configAveraging(int number)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0xf1ff;
  v = v | (number << 9);

  INA260_Write(INA260_CONFIG, v);
}

int INA260_getConfigAveraging(void)
{
  int v;

  v = INA260_Read(INA260_CONFIG);

  v = v & 0x0e00;
  v = v >> 9;

  return v;
}

void INA260_setMask(unsigned short mask)
{
  int v;

  v = 1 << (mask + 10);

  INA260_Write(INA260_ALERTEN, v);
}

int INA260_getMask(void)
{
  int v;

  v = INA260_Read(INA260_ALERTEN);

  return v;
}

void INA260_setAlert(int alert)
{

  INA260_Write(INA260_ALERTV, alert);
}

int INA260_getAlert(void)
{
  int v;

  v = INA260_Read(INA260_ALERTV);

  return v;
}

void INA260_reset(void)
{
  int i;

  INA260_Write(INA260_CONFIG, 0x80);
}

/**
 * Interal Read Write Functions
 * 
 */

int INA260_Read(int reg)
{
  int i;
  char Data[2];
  int v;

  i = I2C_In(_INA260C, _INA260, reg, 1, Data, 2);

  v = Data[0] << 8 | Data[1];

  if (i == 0)
    return -1;
  
  return v;
}

void INA260_Write(int reg, int value)
{
  int i;
  char Data[2];

  Data[0] = value >> 8;
  Data[1] = value;
  i = I2C_Out(_INA260C, _INA260, reg, 1, Data, 2);
}
