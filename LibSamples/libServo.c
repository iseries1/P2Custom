/**
 * @brief Program purpose
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "servos.h"

#define SERVO1 16


int main()
{
    
    Servo_Enable(SERVO1, 1500, 20000);
    
    while (1)
    {
        _waitms(1000);
        Servo_Set(SERVO1, 400);
        _waitms(1000);
        Servo_Set(SERVO1, 2400);
	}
}
