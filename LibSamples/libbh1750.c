/**
 * @brief bh1750 light sensor driver
 * @author Michael Burmeister
 * @date January 28, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "bh1750.h"

#define BHCLK 36
#define BHDTA 37


int main(int argc, char** argv)
{
    int i;

    i = BH1750_Init(BHCLK, BHDTA);

    printf("Found: %d\n", i);
    
    BH1750_Cmd(BH1750_PWR_UP);

    BH1750_Cmd(BH1750_CHRM);

    while (1)
    {
        i = BH1750_Read();
        printf("Value:%d\n", i);       
        _waitms(1000);
	}
}
