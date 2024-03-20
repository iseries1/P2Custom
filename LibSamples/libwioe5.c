/**
 * @brief Program purpose
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "wioe5.h"

#define WTX 20
#define WRX 21

char Buffer[256];


int main(int argc, char** argv)
{
    int i;
    float t = 20.25;
    float h = 45.5;
    float p = 29.20;
    int v = 7450;
    int c = 2;

    printf("Starting...\n");

    i = WIOE5_Init(WRX, WTX);
    
    printf("Ready\n");

    printf("Ver: %d\n", i);

    //i = WIOE5_GetID();

    //printf("%x -> %d\n", i, i);

    //i = WIOE5_Join();
    printf("Joined: %d\n", i);

    WIOE5_SetLora(0, 915, 8);

    Buffer[0] = 0;
    Hex(&t);
    Hex(&h);
    Hex(&p);
    Hex(&v);
    Hex(&c);
    //i = WIOE5_SendConfirmedHex(Buffer);

    WIOE5_SendLora(Buffer);
    i = 0; //i = WIOE5_GetLora(Buffer);
    if (i > 0)
    {
        for (int j=0;j<i;j++)
            printf("%2x:", Buffer[j]);
    }
    printf("\n");

    printf("Done\n");

    while (1)
    {
        _waitms(1000);
	}
}

void Hex(void *d)
{
    char data[10];
    char *x = d;

    sprintf(data, "%2.2x%2.2x%2.2x%2.2x", x[0], x[1], x[2], x[3]);
    strcat(Buffer, data);
}

