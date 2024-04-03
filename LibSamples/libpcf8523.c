/**
 * @brief Library functions for PCF8523 Real Time Clock
 * @author Michael Burmeister
 * @date April 2, 2024
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include <pcf8523.h>


#define PCFCLK 36
#define PCFDTA 37

time_t tm;


int main(int argc, char** argv)
{
    int i;
    int h, m, s;
    int mn, d, y, w;

    i = PCF8523_Init(PCFCLK, PCFDTA);
    if (i < 0)
    {
        printf("Error\n");
        while (1)
            _waitms(1000);
    }

    i = PCF8523_Control();

    printf("Control: %x\n", i);

    //PCF8523_SetTime(6,14,0);
    //PCF8523_SetDate(4,3,2024);

    i = PCF8523_GetTime(&s, &m, &h);
    printf("Seconds: %d\n", i);

    i = PCF8523_GetDate(&d, &mn, &y);
    printf("Days: %d\n", i);

    printf("Time: %d:%d:%d, Date: %d/%d/%d\n", h, m, s, mn, d, y);

    PCF8523_SetDateTime();

    //PCF8523_SetAlarm(17,-1,-1,-1);

    i = PCF8523_GetAlarm(&m, &h, &d, &w);

    printf ("Alarm(%d) = %d, %d, %d, %d\n", i, m, h, d, w);

    i = PCF8523_GetFlags();
    printf("Flags: %x\n", i);

    //Wait();

    printf("Done\n");

    while (1)
    {
    	time(&tm);
    	printf("Date: %s", asctime(localtime(&tm)));
        _waitms(1000);
	}
}

void Wait()
{
    int i;

    printf("Waiting....\n");
    while (1)
    {
        i = PCF8523_GetFlags();
        if ((i & PCF8523_AF) != 0)
        {
            PCF8523_ClearFlags(PCF8523_AF);
            break;
        }
    }
}