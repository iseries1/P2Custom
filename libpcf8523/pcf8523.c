/**
 * @brief PCF8523 Real Time Clock Driver
 * @author Michael Burmeister
 * @version 1.0
 * @date April 2, 2024
 * 
 */

#include <stdio.h>
#include <propeller.h>
#include <i2c.h>
#include <sys/time.h>
#include <pcf8523.h>
#include <libpcf8523/pcf8523reg.h>
#include <smartpins.h>


short _MM[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

int BCDtoInt(int);
int InttoBCD(int);


i2c_t *pcf;


int PCF8523_Init(int clk, int dta)
{
    int i;
    unsigned char data;

    pcf = I2C_Init(clk, dta, I2C_STD);
    data = 0;
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_CNTRL1, 1, &data, 1);

    i = I2C_In(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
    data = data & 0x7f;
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
    I2C_In(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
    if ((data & 0x80) == 0)
        return 1;
    return -1;
}

int PCF8523_GetTime(int *seconds, int *minutes, int *hours)
{
    int i;
    unsigned char data[3];

    I2C_In(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 3);

    *seconds = BCDtoInt(data[0]);
    *minutes = BCDtoInt(data[1]);
    *hours = BCDtoInt(data[2]);

    i = *seconds + *minutes * 60 + *hours * 3600;
    return i;
}

int PCF8523_DayofWeek(void)
{
    int i;
    unsigned char data;

    I2C_In(pcf, PCF8523_ADDR, PCF8523_WEEKDAY, 1, &data, 1);

    return data;
}

int PCF8523_GetDate(int *day, int *month, int *year)
{
    int i;
    unsigned char data[4];

    I2C_In(pcf, PCF8523_ADDR, PCF8523_DAY, 1, &data, 4);

    *day = BCDtoInt(data[0]);
    *month = BCDtoInt(data[2]);
    *year = BCDtoInt(data[3]);

    i = *day - 1 + _MM[*month-1] + ((30 + *year) * 36525 + 25)/100;
    if ((*year % 4) == 0)
        if (*month > 2)
            i++;
    return i;
}

void PCF8523_SetDate(int month, int day, int year)
{
    int i;
    unsigned char data;

    data = InttoBCD(day);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_DAY, 1, &data, 1);
    data = InttoBCD(month);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_MONTH, 1, &data, 1);
    data = InttoBCD(year - 2000);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_YEAR, 1, &data, 1);
}

void PCF8523_SetTime(int hours, int minutes, int seconds)
{
    int i;
    unsigned char data;

    data = InttoBCD(seconds);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
    data = InttoBCD(minutes);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_MINUTES, 1, &data, 1);
    data = InttoBCD(hours);
    I2C_Out(pcf, PCF8523_ADDR, PCF8523_HOUR, 1, &data, 1);
}

int PCF8523_SetDateTime(void)
{
    int i, j, k;
    int t;
    struct timeval tv;

    PCF8523_GetDate(&i, &j, &k);
    t = ((30 + k) * 36525 + 25)/100;
    t = t + _MM[j-1] + i - 1;
    if ((k % 4) == 0)
        if (j > 2)
            t++;

    PCF8523_GetTime(&i, &j, &k);

    t = t * 24 + k;
    t = t * 60 + j;
    t = t * 60 + i;

    tv.tv_usec = 0;
    tv.tv_sec = t;
    settimeofday(&tv, 0);
    return t;    
}

int PCF8523_Control(void)
{
    int i;
    unsigned char data[3];

    I2C_In(pcf, PCF8523_ADDR, PCF8523_CNTRL1, 1, data, 3);

    i = data[0] | (data[1] << 8) | (data[2] << 16);

    return i;
}

void PCF8523_SetControl(int control)
{
    int i;
    unsigned char data[3];

    data[0] = control;
    data[1] = (control >> 8);
    data[2] = (control >> 16);

    I2C_Out(pcf, PCF8523_ADDR, PCF8523_CNTRL1, 1, data, 3);
}

void PCF8523_SetAlarm(int minutes, int hours, int day, int dayofweek)
{
    int i;
    unsigned char data[4];

    if (minutes >= 0)
        data[0] = InttoBCD(minutes);
    else
        data[0] = 0x80;
    
    if (hours >= 0)
        data[1] = InttoBCD(hours);
    else
        data[1] = 0x80;
    
    if (day >= 0)
        data[2] = InttoBCD(day);
    else
        data[2] = 0x80;
    
    if (dayofweek >= 0)
        data[3] = InttoBCD(dayofweek);
    else
        data[3] = 0x80;

    i = I2C_Out(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, data, 4);

}

int PCF8523_GetAlarm(int *minute, int *hour, int *day, int *weekday)
{
    int i, j;
    unsigned char data[4];

    j = 0x80;

    i = I2C_In(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, data, 4);


    if ((data[0] & j) == 0)
        *minute = BCDtoInt(data[0]);
    else
        *minute = -1;
    
    if ((data[1] & j) == 0)
        *hour = BCDtoInt(data[1]);
    else
        *hour = -1;

    if ((data[2] & j) == 0)
        *day = BCDtoInt(data[2]);
    else
        *day = -1;
    
    if ((data[3] & j) == 0)
        *weekday = BCDtoInt(data[3]);
    else
        *weekday = -1;

    I2C_In(pcf, PCF8523_ADDR, PCF8523_CNTRL2, 1, data, 1);

    i = (data[0] >> 3) & 0x01;

    return i;
}

void PCF8523_SetOffset(int offset)
{
    int i;
    unsigned char data;

    data = offset;

    I2C_Out(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, &data, 1);
}

void PCF8523_ClearFlags(int flags)
{
    int i;
    unsigned char data;

    I2C_In(pcf, PCF8523_ADDR, PCF8523_CNTRL2, 1, &data, 1);

    data = data & ~flags;

    I2C_Out(pcf, PCF8523_ADDR, PCF8523_CNTRL2, 1, &data, 1);
}

int PCF8523_GetFlags(void)
{
    int i;
    unsigned char data;

    I2C_In(pcf, PCF8523_ADDR, PCF8523_CNTRL2, 1, &data, 1);

    return data & 0xf8;
}

void PCF8523_SetPower(int option)
{
    int i;
    unsigned char data;

    I2C_In(pcf, PCF8523_ADDR, PCF8523_CNTRL3, 1, &data, 1);

    data = data & 0x1f;
    data = data | (option << 5);

    I2C_Out(pcf, PCF8523_ADDR, PCF8523_CNTRL3, 1, &data, 1);
}


/* Built in functions */

int BCDtoInt(int bcd)
{
    int i, j;

    i = bcd & 0x7f;
    j = i >> 4;
    i = j * 10 + (i & 0x0f);
    return i;
}

int InttoBCD(int value)
{
    int i, j;
    
    j = value % 10;
    i = value / 10;
    i = i << 4 | j;
    return i;
}

