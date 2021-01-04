/**
 * @brief DS18B20 One Wire temperature driver
 * @author Michael Burmeister
 * @date December 27, 2020
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "simpletools.h"
#include "ds1822.h"

#define DS 8

char Buffer[12];

int main()
{
    int i;
    
    i = DS1822_Init(DS);
    printf("Device: %d -> ", i);
    DS1822_ReadRom(DS, Buffer);

    printf("Values: ");
    for (int i=0;i<8;i++)
    {
        printf("%x ", Buffer[i]);
    }
	i = DS1822_CRC(Buffer, 7);
	printf("(%x)\n", i);
	
	i = DS1822_Init(DS);
	i = DS1822_SearchRom(DS, Buffer);
	if (i)
		DS1822_Convert(DS);

	printf("Search: %d\n", i);
//	i = DS1822_Init(DS);
//	DS1822_SkipRom(DS);
	
    i = DS1822_Init(DS);
    printf("Device: %d -> ", i);
    DS1822_SkipRom(DS);
    DS1822_ReadScratchpad(DS, Buffer);
    printf("Values: ");
    for (int i=0;i<9;i++)
    {
        printf("%x ", Buffer[i]);
    }
    i = DS1822_CRC(Buffer, 8);
    printf("(%x)\n", i);
    i = DS1822_ConvertTemperature(Buffer);
    printf("Temperature: %d (%d)\n", i, i*9/5+320);
    while (1)
    {
        _pinl(57);
        _waitms(1000);
        _pinh(57);
        _waitms(1000);
	}
}
