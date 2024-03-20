/**
 * @brief Driver Program for AS3935 Lightning Detector
 * @author Michael Burmeister
 * @date December 23, 2023
 * @version 1.0
 * 
*/

//enum { _clkfreq = 3840000 };

#include <stdio.h>
#include <propeller.h>
#include "as3935.h"

int d;


int main(int argc, char** argv)
{
    int i, s;

    i = AS3935_Init(0, 1, 2, 3);

    AS3935_SetFloor(6);
    //AS3935_SetLightning(0);

    AS3935_SetWatchdog(7);
    AS3935_SetAFE(0);

    printf("State: %x\n", i);
    
    s = 0;
    while (1)
    {
        i = AS3935_ReadInterrupt();
        if ((i > 0))
        {
            s++;
            printf("%d - ", s);
            if (i == 1)
                printf("Noise\n");
            if (i == 4)
                printf("Disturber\n");
            if (i == 8)
            {
                printf("Lightning ");
                d = AS3935_ReadDistance();
                printf("Distance: %d ", d);
                d = AS3935_ReadLightingEnergy();
                printf("Energy: %d\n", d);
            }
        }
        _waitms(5000);
	}
}
