/**
 * @brief Driver for DS3221 (HW084)
 * @author Michael Burmeister
 * @date December 25, 2020
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "ds3231.h"

#define DSCLK 17
#define DSSDA 16

time_t tm;

int main()
{
    int i;
    
    DS3231_Open(DSCLK, DSSDA);
    
//    DS3231_SetDate(1,6,21);
//    DS3231_SetTime(6,41,0);
    
	DS3231_SetDateTime();
		
    while (1)
    {
    	time(&tm);
    	i = DS3231_Temperature();
    	printf("Temp %d, Date: %s", i, asctime(localtime(&tm)));
        _waitms(1000);
	}
}
