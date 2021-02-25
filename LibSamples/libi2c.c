/**
 * @brief Driver for I2C devices
 * @author Michael Burmeister
 * @date January 21, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "i2c.h"

#define CLK 23
#define DAT 22


i2c_t *x;
char buffer[256];


int main(int argc, char** argv)
{
	int i;
	    
    x = I2C_Init(CLK, DAT, I2C_FAST);
    
    printf("What: %x\n", (int)*x);
    
    i = I2C_Poll(x, 0x77<<1);
    
    printf("Poll: %x\n", i);
    
    i = I2C_In(x, 0x77, 0xd0, 1, buffer, 1);
    
    printf("Data: %x, i: %d\n", buffer[0], i);
    
    while (1)
    {
        _waitms(1000);
	}
}
