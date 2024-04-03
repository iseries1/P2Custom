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

#define BLRX 40
#define BLTX 41
#define BLAT 42
#define INACLK 8
#define INADTA 9


char Buffer[4096];
char *x;
time_t tm;


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

    /* status of the Notecard */
    for (int j=0;j<120;j++)
    {
        i = Blueio_Status();
        if (i > 0)
        {
            printf("Wait:%d seconds\n", j);
            break;
        }
        _waitms(1000);
    }
    printf("Status:%d\n", i);

    json_init(Buffer);
    json_putDec("temp", "26.54");
    json_putDec("humid", "35.53");
    json_putDec("pressure", "97785.84");
    json_putDec("ohms", "51769.47");

    /* add the data to the Notecard */
    //i = Blueio_Add(Buffer, NULL);

    /* send/receive data from the cloud */
    //Blueio_Sync();

    i = Blueio_GetTime();
    printf("Time: %d\n", i);
    tm = i-18000;

    /* get temperature */
    i = Blueio_GetTemperature();
    printf("Temperature: %d\n", i);

    /* check if there is data from the cloud */
    i = Blueio_Check();
    printf("Check: %d\n", i);

    /* get the data from the Notecard */
    i = Blueio_GetData(Buffer, 0);
    printf("Data:%s", Buffer);

    i = Blueio_Receive(Buffer);
    if (i > 0)
        printf("Left Over: %s\n", Buffer);

    printf("\n");
    printf(asctime(localtime(&tm)));

    printf("\nDone\n");

    while (1)
    {
        i = INA260_getCurrent();
        printf("Current: %d\n", i);
        i = INA260_getVoltage();
        printf("Voltage: %d\n", i);
        _waitms(5000);
	}
}

