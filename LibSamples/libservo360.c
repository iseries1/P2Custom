/**
 * @brief Driver for Servo 360
 * @author Michael Burmeister
 * @date Feburary 20, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "servo360.h"

#define SERVO 8
#define FEEDBACK 9


int main(int argc, char** argv)
{
    int s, s1;
    int i;

    printf("Starting\n");

    s = Servo360_Start(SERVO, FEEDBACK);
    s1 = Servo360_Add(20, 21);

    printf("Servo: %d %d\n", s, s1);

    _waitms(500);

    Servo360_Enable(s, 1);
    Servo360_Enable(s1, 1);

    i = Servo360_Angle(s);

    printf("angle: %d\n", i);

    Servo360_SetAngle(s, i - 280);
    Servo360_SetAngle(s1, i + 280);

    while (1)
    {
        i = Servo360_Angle(s);

        printf("Angle %d Status: %d\n", i, Servo360_Status(s));
        _waitms(1000);
	}
}
