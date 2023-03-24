/**
 * @brief BLUEIO Communications Driver
 * @author Michael Burmeister
 * @date February 8, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "blueio.h"
#include "json.h"
#include "ina260.h"

#define BLRX 20
#define BLTX 21
#define INACLK 40
#define INADTA 41


char Buffer[4096];
char *x;


int main(int argc, char** argv)
{
    int i;

    printf("Starting\n");

    i = INA260_open(INACLK, INADTA);
    if (i == 0x5449)
        printf("INA260 Found\n");
    else
        printf("Not Found\n");

    i = Blueio_Init(BLRX, BLTX);

    printf("Version:%d\n", i);

    json_init(Buffer);
    json_putDec("temp", "26.54");
    json_putDec("humid", "35.53");
    json_putDec("pressure", "97785.84");
    json_putDec("ohms", "51769.47");

    /* add the data to the Notecard */
    //i = Blueio_Add(Buffer);

    /* send/receive data from the cloud */
    Blueio_Sync();

    /* status of the Notecard */
    Blueio_Status();

    /* check if there is data from the cloud */
    i = Blueio_Check();
    printf("Check: %d\n", i);

    /* get the data from the Notecard */
    i = Blueio_Get(Buffer, 0);
    printf("Data:%s", Buffer);

    /* some test code to make sure nothing is left hanging */
    for (i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            Blueio_Receive(Buffer);
            printf(Buffer);
            printf("\n");
            break;
        }
        _waitms(1000);
    }

    printf("\nDone\n");

    while (1)
    {
        i = INA260_getCurrent();
        printf("Current: %d\n", i);
        i = INA260_getVoltage();
        printf("Voltage: %d\n", i);
        _waitms(1000);
	}
}
