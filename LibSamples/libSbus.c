/**
 * @brief Decode SBUS serial data from X8R receiver
 * @author Michael Burmeister
 * @date March 10, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "Sbus.h"

#define SBPIN 8


int main(int argc, char** argv)
{
    int role, pitch, speed, yaw;

    Sbus_Open(SBPIN);

    printf("Role Pitch, Speed, Yaw\r\n");

    while (1)
    {
        role = Sbus_GetChannel(1);
        pitch = Sbus_GetChannel(2);
        speed = Sbus_GetChannel(3);
        yaw = Sbus_GetChannel(4);

        printf("%d, %d, %d, %d\r\n", role, pitch, speed, yaw);
        _waitms(1000);
	}
}
