/**
 * @brief Arducam Mega 5 Driver
 * @author Michael Burmeister
 * @date May 2, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "Mega5.h"

#define MEGCLK 16
#define MEGDI  17
#define MEGDO  18
#define MEGCS  19



int main(int argc, char** argv)
{
    int i;


    i = Mega5_Init(MEGCLK, MEGDI, MEGDO, MEGCS);

    printf("ID: %X\n", i);

    while (1)
    {
        _waitms(500);
	}
}
