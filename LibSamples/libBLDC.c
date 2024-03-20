/**
 * @brief Test BLDC Motor Driver
 * @author Michael Burmeister
 * @date October 30, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <propeller.h>
#include <bldc.h>

int l, r;

int main(int argc, char** argv)
{
    int i;
    
    i = BLDC_Init(32, 16);

    printf("Starting: %d\n", i);

    BLDC_SetSpeed(32,31);

    BLDC_Tick(90);
    BLDC_SetDirection(0, 1); //Forwards

//    BLDC_Move(1, 1);
    _waitms(15000);

    BLDC_Stop();

    BLDC_GetTicks(&l, &r);

    printf("Left: %d, Right: %d\n", l, r);

    printf("Done\n");

    while (1)
    {
        _waitms(1000);
	}
}


