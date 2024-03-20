/**
 * @brief Test Smart Pin Pulse Output
 * @author Michael Burmeister
 * @date February 22, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "Mega5.h"
#include "Mega5_def.h"


int RegisterRead(unsigned char);
int RegisterWrite(unsigned char, unsigned char);
unsigned int SPI(unsigned char);


int _MClk, _MMiso, _MMosi, _MCs;


int Mega5_Init(int clk, int miso, int mosi, int cs)
{
    int i;

    _MClk = clk;
    _MMiso = miso;
    _MMosi = mosi;
    _MCs = cs;

    i = RegisterWrite(CAM_REG_SENSOR_RESET, CAM_SENSOR_RESET_ENABLE);
    i = RegisterRead(CAM_REG_SENSOR_STATE);
    printf("i: %x\n", i);
    _waitms(10);

    i = RegisterRead(CAM_REG_SENSOR_ID);
    printf("i: %x\n", i);

    i = RegisterRead(CAM_REG_YEAR_ID);
    printf("i: %x\n", i);

    i = RegisterRead(CAM_REG_MONTH_ID);
    printf("i: %x\n", i);

    i = RegisterRead(CAM_REG_DAY_ID);
    printf("i: %x\n", i);

    i = RegisterRead(CAM_REG_FPGA_VERSION_NUMBER);
    printf("i: %x\n", i);

    return i;
}

/**
 * @brief Low level functions
 * 
 */
int RegisterRead(unsigned char addr)
{
    int i;

    _pinl(_MCs);
    i = SPI(addr);
    i = SPI(0x00);
    i = SPI(0x00);
    _pinh(_MCs);
}

int RegisterWrite(unsigned char addr, unsigned char value)
{
    int i;

    _pinl(_MCs);
    i = SPI(addr | 0x80);
    i = SPI(value);
    _pinh(_MCs);
}

unsigned int SPI(unsigned char cmd)
{
    unsigned int r;

    r = 0;
    for (int i=0;i<8;i++)
    {
        if ((cmd & 0x80) == 0)
            _pinl(_MMosi);
        else
            _pinh(_MMosi);
        _waitus(10);
        _pinh(_MClk);
        _waitus(10);
        r = r << 1;
        r = r | _pinr(_MMiso);
        _pinl(_MClk);
        _waitus(10);
        cmd = cmd << 1;
    }
    return r;
}
