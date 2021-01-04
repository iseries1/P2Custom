/**
 * @brief Interface to BME280 sensor
 * @author Michael Burmeister
 * @date December 14, 2017
 * @version 1.2
 * 
*/

#include "simpletools.h"
#include "BME280Reg.h"
#include "bme280.h"

static void BME280_writeByte(unsigned char , unsigned char );
static unsigned char BME280_readByte(unsigned char);
static void BME280_readBytes(unsigned char , unsigned char , unsigned char *);
static void BME280_calibration(void);


static i2c bme;
static char Buffer[40];
struct
{
  unsigned short T1;
  short T2;
  short T3;
  int fine;

  unsigned short P1;
  short P2;
  short P3;
  short P4;
  short P5;
  short P6;
  short P7;
  short P8;
  short P9;

  unsigned char H1;
  short H2;
  unsigned char H3;
  short H4;
  short H5;
  char H6;
} _cal;
  

// Open BME280 interface
int BME280_open(int scl, int sda)
{
  int i;
  
  i2c_open(&bme, scl, sda, 0);
  pause(100);
  i = BME280_getID();
  if (i != 0x60)
    return -1;
  BME280_calibration();
  return i;
}

int BME280_getID()
{
  int i = BME280_readByte(BME280_ID);
  return i;
}

void BME280_reset()
{
  BME280_writeByte(BME280_RS, 0xB6);
  pause(300);
}

int BME280_getStatus()
{
  int i;
  
  i = BME280_readByte(BME280_STATUS);
  return i;
}

void BME280_setTemp(int t)
{
  short i;
  
  i = BME280_readByte(BME280_CNTRL);
  t = t << 3;
  i = i & 0xe3;
  i = i | t;
  BME280_writeByte(BME280_CNTRL, i);
}

void BME280_setPressure(int p)
{
  short i;
  
  i = BME280_readByte(BME280_CNTRL);
  p = p << 6;
  i = i & 0x1f;
  i = i | p;
  BME280_writeByte(BME280_CNTRL, i);
}

void BME280_setHumidity(int h)
{
  
  BME280_writeByte(BME280_CH, h);
}

void BME280_setStandbyRate(int s)
{
  short i;
  
  i = BME280_readByte(BME280_CNFG);
  s = s << 5;
  i = i & 0x1f;
  i = i | s;
  BME280_writeByte(BME280_CNFG, i);
}

void BME280_setFilterRate(int f)
{
  short i;
  
  i = BME280_readByte(BME280_CNFG);
  f = f << 2;
  i = i & 0xe3;
  i = i | f;
  BME280_writeByte(BME280_CNFG, i);
}

void BME280_setMode(int m)
{
  short i;
  
  i = BME280_readByte(BME280_CNTRL);
  i = i & 0xfc;
  i = i | m;
  BME280_writeByte(BME280_CNTRL, i);
}

int BME280_getMode()
{
  short i;
  
  i = BME280_readByte(BME280_CNTRL);
  i = i & 0x03;
  return i;
}
  
int BME280_getPressure(void)
{
  int i;
  int v1, v2, v3, v4;
  unsigned int v5;
  
  BME280_readBytes(BME280_PD, 3, Buffer);
  
  i = Buffer[0];
  i = i << 8;
  i = i | Buffer[1];
  i = i << 8;
  i = i | Buffer[2];
  i = i >> 4;
//  print("Raw Pressure: %d\n", i);
  
  v1 = _cal.fine / 2 - 64000;
  v2 = v1/4 * v1/4 / 2048 * _cal.P6;
  v2 = v2 + v1 * _cal.P5 * 2;
  v2 = v2/4 + (int)_cal.P4 * 65536;
  v3 = v1/4 * v1/4 / 8192 * _cal.P3 / 8;
  v4 = _cal.P2 * v1 / 2;
  v1 = (v3 + v4)/262144;
  v1 = (32768+v1) * _cal.P1/32768;
  if (v1 == 0)
    return 30000;
  v5 = 1048576;
  v5 = v5 - i;
  v5 = (v5 - (unsigned int)(v2/4096)) * 3125;
  if (v5 < 0x80000000)
    v5 = (v5 << 1) / (unsigned int)v1;
  else
    v5 = v5 / (unsigned int)v1 / 2;
  v1 = (int)_cal.P9 * ((v5/8 * v5/8)/8192) / 4096;
  v2 = (int)v5/4 * _cal.P8/8192;
  i = (int)v5 + (v1 + v2 + _cal.P7)/16;
  
  return i;
}

int BME280_getTemp(void)
{
  int i;
  int v1, v2;
  
  BME280_readBytes(BME280_TD, 3, Buffer);
  
  i = Buffer[0];
  i = i << 8;
  i = i | Buffer[1];
  i = i << 8;
  i = i | Buffer[2];
  i = i >> 4;
  
  v1 = i / 8 - _cal.T1 * 2;
  v1 = v1 * _cal.T2 / 2048;
  v2 = i / 16 - _cal.T1;
  v2 = v2 * v2 / 4096 * _cal.T3 / 16384;
  v1 = v1 + v2;
  _cal.fine = v1;
  v1 = (v1 * 5 + 128) / 256;
  //printi("T: %d, t1: %d, t2: %d, t3: %d\n", i, _cal.T1, _cal.T2, _cal.T3);
  
  return v1;
}

int BME280_getHumidity(void)
{
  int i;
  int v1, v2, v3, v4, v5;
  
  BME280_readBytes(BME280_HD, 2, Buffer);
  
  i = Buffer[0];
  i = i << 8;
  i = i | Buffer[1];
//  print("Raw Humidity: %d\n", i);
  
  v1 = _cal.fine - 76800;
  v2 = i * 16384;
  v3 = (int)_cal.H4 * 1048576;
  v4 = v1 * (int)_cal.H5;
  v5 = (v2 - v3 - v4 + 16384)/32768;
  v2 = v1 * (int)_cal.H6 / 1024;
  v3 = v1 * _cal.H3 / 2048;
  v4 = v2 * (v3 + 32768) / 1024 + 2097152;
  v2 = (v4 * _cal.H2 + 8192) / 16384;
  v3 = v5 * v2;
  v4 = v3 / 32768;
  v4 = v4 * v4 / 128;
  v5 = v3 - v4 * _cal.H1 / 16;
  if (v5 < 0)
    v5 = 0;
  if (v5 > 419430400)
    v5 = 419430400;
  i = v5 / 4096;

  i = i*100 / 1024;
  
  return i;
}

int BME280_getTempF()
{
  int i;
  
  i = BME280_getTemp();
  i = i * 9/5 + 3200;
  return i;
}

int BME280_getPressureM()
{
  int i;
  
  i = BME280_getPressure();
  i = i*100/3386;
  return i;
}

void BME280_calibration(void)
{
  short i;
  unsigned short j;
  
  BME280_readBytes(BME280_T1, 6, Buffer);
  j = Buffer[1];
  j = j << 8;
  j = j | Buffer[0];
  _cal.T1 = j;
  i = Buffer[3];
  i = i << 8;
  i = i | Buffer[2];
  _cal.T2 = i;
  i = Buffer[5];
  i = i << 8;
  i = i | Buffer[4];
  _cal.T3 = i;
//  print("T1: %d, T2: %d, T3: %d\n", _cal.T1, _cal.T2, _cal.T3);
  
  BME280_readBytes(BME280_P1, 18, Buffer);
  j = Buffer[1];
  j = j << 8;
  j = j | Buffer[0];
  _cal.P1 = j;
  i = Buffer[3];
  i = i << 8;
  i = i | Buffer[2];
  _cal.P2 = i;
  i = Buffer[5];
  i = i << 8;
  i = i | Buffer[4];
  _cal.P3 = i;
  i = Buffer[7];
  i = i << 8;
  i = i | Buffer[6];
  _cal.P4 = i;
  i = Buffer[9];
  i = i << 8;
  i = i | Buffer[8];
  _cal.P5 = i;
  i = Buffer[11];
  i = i << 8;
  i = i | Buffer[10];
  _cal.P6 = i;
  i = Buffer[13];
  i = i << 8;
  i = i | Buffer[12];
  _cal.P7 = i;
  i = Buffer[15];
  i = i << 8;
  i = i | Buffer[14];
  _cal.P8 = i;
  i = Buffer[17];
  i = i << 8;
  i = i | Buffer[16];
  _cal.P9 = i;
  
//  print("P1: %d, P2: %d, P3: %d, P4: %d, P5: %d,\nP6: %d, P7: %d, P8: %d, P9: %d\n",
//    _cal.P1, _cal.P2, _cal.P3, _cal.P4, _cal.P5, _cal.P6, _cal.P7, _cal.P8, _cal.P9);
    
  j = BME280_readByte(BME280_H1);
  _cal.H1 = j;
  
  BME280_readBytes(BME280_H2, 7, Buffer);
  i = Buffer[1];
  i = i << 8;
  i = i | Buffer[0];
  _cal.H2 = i;
  _cal.H3 = Buffer[2];
  i = Buffer[3];
  i = i << 4;
  j = Buffer[4] & 0x0f;
  i = i | j;
  _cal.H4 = i;
  i = Buffer[5];
  i = i << 8;
  i = i | Buffer[4];
  i = i >> 4;
  _cal.H5 = i;
  _cal.H6 = Buffer[6];
  
//  print("H1: %d, H2: %d, H3: %d, H4: %d, H5: %d, H6: %d\n", 
//    _cal.H1, _cal.H2, _cal.H3, _cal.H4, _cal.H5, _cal.H6);
    
}
      
/**
 * @brief I2C read write routines
 * @param address device address to write to
 * @param subAddress device register or location on device
 * @param data to write
*/
void BME280_writeByte(unsigned char subAddress, unsigned char data)
{
  i2c_out(&bme, BME280_ADDRESS, subAddress, 1, &data, 1);
}

/**
 * @brief I2C read routine
 * @param address address of device
 * @param subAddress device register or location on device
 * @return byte value
*/
unsigned char BME280_readByte(unsigned char subAddress)
{
  int i;
  unsigned char data;

  i = i2c_in(&bme, BME280_ADDRESS, subAddress, 1, &data, 1);
  if (i == 0)
    return -1;
  return data;
}

/**
 * @brief I2C read routine
 * @param address of device
 * @param subAddress device register or location on device
 * @param cnt number of bytes to read
 * @param dest returned byte of data from device
*/
void BME280_readBytes(unsigned char subAddress, unsigned char cnt, unsigned char *dest)
{
  int i;
  
  i = i2c_in(&bme, BME280_ADDRESS, subAddress, 1, dest, cnt);
  if (i == 0)
    dest[0] = 0;
}

/**
 * @brief define double to enable floating point calcs
*/
#ifdef DODOUBLE

float BME280_getTemperature()
{
  int t;
  double v1, v2;
  
  BME280_readBytes(BME280_TD, 3, Buffer);
  
  t = Buffer[0];
  t = t << 8;
  t = t | Buffer[1];
  t = t << 8;
  t = t | Buffer[2];
  t = t >> 4;

  v1 = (double)t/16384.0-(double)_cal.T1/1024.0;
  v1 = v1*(double)_cal.T2;
  v2 = (double)t/131072.0-(double)_cal.T1/8192.0;
  v2 = v2*v2*(double)_cal.T3;
  _cal.fine = (int)v1+v2;
  v1 = (v1+v2)/5120.0;
  
  if (v1 < -40)
    v1 = -40;
  if (v1 > 85)
    v1 = 85;
  
  return (float)v1;
}

float BME280_getPressuref()
{
  int p;
  double v1, v2, v3;

  BME280_readBytes(BME280_PD, 3, Buffer);
  
  p = Buffer[0];
  p = p << 8;
  p = p | Buffer[1];
  p = p << 8;
  p = p | Buffer[2];
  p = p >> 4;
  
  v1 = (double)_cal.fine/2-64000.0;
  v2 = v1*v1*(double)_cal.P6/32768.0;
  v2 = v2+v1*(double)_cal.P5*2.0;
  v2 = v2/4.0+(double)_cal.P4*65536.0;
  v3 = (double)_cal.P3*v1*v1/524288.0;
  v1 = (v3+(double)_cal.P2*v1)/524288.0;
  v1 = (1.0+v1/32768.0)*(double)_cal.P1;
  if (v1 == 0)
    return 30000.0;
  v3 = 1048576.0-(double)p;
  v3 = (v3-v2/4096.0)*6250.0/v1;
  v1 = (double)_cal.P9*v3*v3/2147483648.0;
  v2 = v3*(double)_cal.P8/32678.0;
  v3 = v3 + (v1+v2+(double)_cal.P7)/16.0;
  
  if (v3 < 30000)
    v3 = 30000;
  if (v3 > 110000)
    v3 = 110000;
  
  return (float)v3;
}

float BME280_getHumidityf()
{
  int h;
  double v1, v2, v3, v4, v5, v6;
  
  BME280_readBytes(BME280_HD, 2, Buffer);
  
  h = Buffer[0];
  h = h << 8;
  h = h | Buffer[1];

  v1 = (double)_cal.fine-76800.0;
  v2 = (double)_cal.H4*64.0+(double)_cal.H5/16384.0*v1;
  v3 = (double)h-v2;
  v4 = (double)_cal.H2/65536.0;
  v5 = 1.0+(double)_cal.H3/67108864.0*v1;
  v6 = 1.0+(double)_cal.H6/67108864.0*v1*v5;
  v6 = v3*v4*v5*v6;
  v1 = v6*(1.0-(double)_cal.H1*v6/524288.0);
  
  if (v1 > 100)
    v1 = 100;
  if (v1 < 0)
    v1 = 0;
  
  return (float)v1;
}

#endif
