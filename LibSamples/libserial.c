/**
 * @brief Serial Driver
 * @author Michael Burmeister
 * @date Feburary 13, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "serial.h"

#define RXPIN 37
#define TXPIN 36

char Data[256];
FILE *s;

int main(int argc, char** argv)
{
    int i;

    s = serial_open(RXPIN, TXPIN, 400000);
    
    
    Data[0] = serial_rxChar(s);
    Data[1] = serial_rxChar(s);
    Data[2] = serial_rxChar(s);
    Data[3] = serial_rxChar(s);
    
    printf("Serial: %x\n", Data[0]);
    printf("Serial2: %x\n", Data[1]);
    
    printf("done\n");

    while (1)
    {
        _waitms(1000);
	}
}
