/**
 * @brief Driver for I2C devices
 * @author Michael Burmeister
 * @date January 21, 2021
 * @version 1.0
 * 
*/

enum { _clkfreq = 3840000};

#include <stdio.h>
#include <propeller.h>
#include <smartpins.h>
#include "i2c.h"

int Find(void);


#define CLK 36
#define DAT 37


i2c_t *x;
char buffer[256];


int main(int argc, char** argv)
{
	int i, j;
	
    j = 0x78;

    x = I2C_Init(CLK, DAT, I2C_STD);
    
    i = I2C_Poll(x, j);

    printf("Poll(%x): %x\n", j, i);
    
    //i = I2C_In(x, j, 0x01, 1, buffer, 1);
    
    printf("Data: %x, i: %d\n", buffer[0], i);
    
    i = Find();
    if (i == 0)
        printf("No Device Found!\n");

    printf("Done\n");

    while (1)
    {
        _waitms(1000);
	}
}

int Find()
{
    int s;
    int f;

    f = 0;
    for (int i=0;i<0x7f;i++)
    {
        s = I2C_Poll(x, i);
        I2C_Stop(x);
        if (s == 0)
        {
            printf("Addr:%x found\n", i);
            f = 1;
        }
    }
    return f;
}
