/**
 * @brief Driver for DS3231 (HW084)
 * @author Michael Burmeister
 * @date December 25, 2020
 * @version 1.0
 * 
*/

#include <propeller.h>
#include "simpletools.h"
#include "ds3231.h"
#include "ds3231reg.h"
#include <sys/time.h>

int DS3231_BCD(int);
int DS3231_Read(int);
int DS3231_DECIMAL(int);
int DS3231_Write(int);

short _MM[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
i2c *pbus;
i2c Bus;

void DS3231_Open(int dsclk, int dssda)
{
    pbus = i2c_open(&Bus, dsclk, dssda, 0);
}

int DS3231_Seconds()
{
    int i;
    
    i = DS3231_Read(DS3231_SECONDS);
    return DS3231_BCD(i);
}

int DS3231_Minutes()
{
    int i;
    
    i = DS3231_Read(DS3231_MINUTES);
    return DS3231_BCD(i);
}

int DS3231_Hour()
{
    int i;
    
    i = DS3231_Read(DS3231_HOUR);
    if (i & 0x40) // 12 hour
    {
        i = DS3231_BCD(i & 0x1f);
	}
	else
	{
	    i = DS3231_BCD(i);
	}
	return i;
}

int DS3231_Dayofweek()
{
    int i;
    
    i = DS3231_Read(DS3231_DAY);
    return i;
}

int DS3231_Day()
{
    int i;
    
    i = DS3231_Read(DS3231_DATE);
    return DS3231_BCD(i);
}

int DS3231_Month()
{
    int i;
    
    i = DS3231_Read(DS3231_MONTH);
    return DS3231_BCD(i & 0x1f);
}

int DS3231_Year()
{
    int i;
    
    i = DS3231_Read(DS3231_YEAR);
    return DS3231_BCD(i);
}

int DS3231_SetYear(int year)
{
    int i;
    
    i = DS3231_Write(DS3231_YEAR, DS3231_DECIMAL(year));
    return i;
}

int DS3231_SetMonth(int month)
{
    int i;
    
    i = DS3231_Write(DS3231_MONTH, DS3231_DECIMAL(month));
    return i;
}

int DS3231_SetDay(int day)
{
    int i;
    
    i = DS3231_Write(DS3231_DATE, DS3231_DECIMAL(day));
    return i;
}

int DS3231_SetDayofweek(int dayofweek)
{
    int i;
    
    i = DS3231_Write(DS3231_DAY, DS3231_DECIMAL(dayofweek));
    return i;
}

int DS3231_SetHour(int hour)
{
    int i;
    
    i = DS3231_Write(DS3231_HOUR, DS3231_DECIMAL(hour));
    return i;
}

int DS3231_SetMinutes(int minutes)
{
    int i;
    
    i = DS3231_Write(DS3231_MINUTES, DS3231_DECIMAL(minutes));
    return i;
}

int DS3231_SetSeconds(int seconds)
{
    int i;
    
    i = DS3231_Write(DS3231_SECONDS, DS3231_DECIMAL(seconds));
    return i;
}

int DS3231_AMPM()
{
    int i;
    
    i = DS3231_Read(DS3231_HOUR);
    i = i >> 5;
    i = i & 0x01;
    return i;
}

void DS3231_SetCentury(int century)
{
    int i;
    
    i = DS3231_Read(DS3231_MONTH);
    i = i & 0x7f;
    i = i | (century << 7);
    DS3231_Write(DS3231_MONTH, i);
}

int DS3231_SetDate(int month, int day, int year)
{
    int i;
    
    i = DS3231_SetYear(year);
    i |= DS3231_SetMonth(month);
    i |= DS3231_SetDay(day);
    return i;
}

int DS3231_SetTime(int hour, int minutes, int seconds)
{
    int i;
    
    i = DS3231_SetHour(hour);
    i |= DS3231_SetMinutes(minutes);
    i |= DS3231_SetSeconds(seconds);
    return i;
}

void DS3231_SetDateTime()
{
    struct timeval tv;
    int i;
    
    i = (30 + DS3231_Year()) * 36525/100;
    i = i + _MM[DS3231_Month()-1] + DS3231_Day()-1;
    if ((DS3231_Year() % 4) == 0)
    	if (DS3231_Month() > 2)
    		i++;
    i = i * 24 + DS3231_Hour();
    i = i * 60 + DS3231_Minutes();
    i = i * 60 + DS3231_Seconds();
    tv.tv_usec = 0;
    tv.tv_sec = i;
    settimeofday(&tv, 0);
}

int DS3231_Temperature()
{
    int i;
    
    i = DS3231_Read(DS3231_TEMPERATURE);
    return i;
}


/**
 * @brief Built in Functions
 */

int DS3231_BCD(int value)
{
    int i, j;
    
    i = value & 0x7f;
    j = i >> 4;
    i = j * 10 + (i & 0x0f);
    return i;
}

int DS3231_DECIMAL(int value)
{
    int i, j;
    
    j = value % 10;
    i = value / 10;
    i = i << 4 | j;
    return i;
}

int DS3231_Read(int reg)
{
    int i;
    
    i = i2c_poll(pbus, DS3231_ADDRESS);
    if (i != 0)
    	return -1;
    i = i2c_writeByte(pbus, reg);
    i = i2c_poll(pbus, DS3231_ADDRESS | 1);
    i = i2c_readByte(pbus, 1);
    i2c_stop(pbus);
    return i;
}

int DS3231_Write(int reg, int value)
{
    int i;
    
    i = 0;
    i = i2c_poll(pbus, DS3231_ADDRESS);
    if (i != 0)
    	return -1;
    i = i2c_writeByte(pbus, reg);
    if (i != 0)
    	return -1;
    i = i2c_writeByte(pbus, value);
    i2c_stop(pbus);
    return i;
}
