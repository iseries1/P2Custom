/**
 * @brief DS18B20 One Wire temperature driver
 * @author Michael Burmeister
 * @date December 27, 2020
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "ds1822.h"
#include "ds1822reg.h"

int _Pin;


int DS1822_Init(int pin)
{
    int i;
    
    _dirh(pin);
    _pinl(pin);
    _waitus(500);
    _dirl(pin);
    _waitus(60);
    i = _pinr(pin);
    _waitus(200);
    return (i == 0);
}

void DS1822_Write(int pin, int state)
{
    _dirh(pin);
    _pinl(pin);
    if (state)
	    _waitus(5);
	else
		_waitus(60);
	_dirl(pin);
	if (state)
		_waitus(60);
	else
		_waitus(5);
}

int DS1822_Read(int pin)
{
    int i;
    
    _dirh(pin);
    _pinl(pin);
    _waitus(2);
    _dirl(pin);
    _waitus(10);
    i = _pinr(pin);
    _waitus(55);
    return i;
}

void DS1822_WriteByte(int pin, int data)
{
    for (int i=0;i<8;i++)
    {
        DS1822_Write(pin, data & 0x01);
        data = data >> 1;
    }
}

char DS1822_ReadByte(int pin)
{
    char b;
    
    b = 0;
    for (int i=0;i<8;i++)
    	b = b | (DS1822_Read(pin) << i);
    return b;
}

void DS1822_ReadBytes(int pin, char* data, int len)
{
    for (int i=0;i < len;i++)
    {
        data[i] = DS1822_ReadByte(pin);
    }
}

void DS1822_WriteBytes(int pin, char* data, int len)
{
    for (int i=0;i<0;i++)
    {
        DS1822_WriteByte(pin, data[i]);
    }
}

void DS1822_ReadRom(int pin, char* data)
{
    DS1822_WriteByte(pin, DS1822_READ);
    DS1822_ReadBytes(pin, data, 8);
}

int DS1822_SearchRom(int pin, char* data)
{
    int i, j;
    int d, b;
    int v;
    
    DS1822_WriteByte(pin, DS1822_SEARCH);
    for (j=0;j<7;j++)
    {
        v = data[j];
        for (i=0;i<8;i++)
        {
            b = v & 0x01;
            d = DS1822_Read(pin);
            DS1822_Read(pin);
            DS1822_Write(pin, b);
            if (d != b)
            {
                j=8;
                break;
		    }
        	v = v >> 1;
        }
    }
    return 8 - j;
}

void DS1822_MatchRom(int pin, char* data)
{
    DS1822_WriteByte(pin, DS1822_MATCH);
    DS1822_WriteBytes(pin, data, 8);
}

void DS1822_SkipRom(int pin)
{
    DS1822_WriteByte(pin, DS1822_SKIP);
}

void DS1822_AlarmSearch(int pin, char* buffer)
{
    DS1822_WriteByte(pin, DS1822_ALARM);
    DS1822_ReadBytes(pin, data, 8);
}

void DS1822_Convert(int pin)
{
    int i;
    
    DS1822_WriteByte(pin, DS1822_CONVERT);
	for (i=0;i<100;i++)
	{
	    if (DS1822_Read(pin))
	    	break;
	    else
	    	_waitms(10);
	}
}

void DS1822_WriteScratchpad(int pin, char* buffer)
{
    DS1822_WriteByte(pin, DS1822_WRITESCRATCHPAD);
    DS1822_WriteBytes(pin, buffer, 3);
}

void DS1822_ReadScratchpad(int pin, char* buffer)
{
    DS1822_WriteByte(pin, DS1822_READSCRATCHPAD);
    DS1822_ReadBytes(pin, buffer, 9);
}

void DS1822_CopyScratchpad(int pin)
{
    DS1822_WriteByte(pin, DS1822_COPYSCRATCHPAD);
}

void DS1822_RecallScratchpad(int pin)
{
    DS1822_WriteByte(pin, DS1822_RECALLSCRATCHPAD);
}

int DS1822_ReadPower(int pin)
{
    DS1822_WriteByte(pin, DS1822_POWER);
    return (DS1822_Read(pin) == 0);
}

int DS1822_CRC(char* data, int len)
{
    char crc;
    char v;
    char b;
    
    crc = 0;
    for (int i=0;i<len;i++)
    {
        v = data[i];
        for (int j=0;j<8;j++)
        {
            b = (crc ^ v) & 0x01;
            crc = crc >> 1;
            if (b)
            	crc = crc ^ 0x8c;
			v = v >> 1;
		}
	}
	return crc;
}

void DS1822_SetResolution(int pin, int resolution)
{
    char buf[9];
    
    if (resolution < 9)
    	return;
    resolution = resolution - 9;
    
    DS1822_ReadScratchpad(pin, buf);
    buf[0] = buf[2];
    buf[1] = buf[3];
    buf[2] = resolution;
    DS1822_WriteScratchpad(pin, buf);
}

int DS1822_ConvertTemperature(char* buf)
{
    int t;
    int x;
    
    x = buf[0] & 0x0f;
    x = x * 625;
    t = buf[0] >> 4;
    t = t | buf[1] << 4;
    if (t & 0x80)
    	t = -((t &0x7f) * 10 + (x / 1000));
    else
	    t = t * 10 + (x / 1000);
    return t;
}
