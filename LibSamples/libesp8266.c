/**
 * @brief Test ESP8266 library functions
 * @author Michael Burmeister
 * @date November 29, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "esp8266.h"

#define RX 1
#define TX 2

char *data;
char Buffer[1024];


int main(int argc, char** argv)
{
    int i;

    printf("Ready\n");
    gets(Buffer);

    esp8266_Open(RX, TX, 230400);
    
    data = esp8266_Check("module-name");
    printf("Name: %s\n", data);

    printf("Done\n");

    while (1)
    {
        _waitms(1000);
	}
}
