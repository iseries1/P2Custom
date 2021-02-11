/**
 * @brief Test Flash Driver
 * @author Michael Burmeister
 * @date January 26, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "flash.h"

#define MOSI 59
#define MISO 58
#define CLK  60
#define CS   61

flash_t *flash;

uint8_t Buffer[2048];


int main(int argc, char** argv)
{
    int i;
    
    printf("Starting\n");
    
    flash = Flash_Init(MOSI, MISO, CLK, CS);
    
    if (flash == NULL)
    {
        printf("flash not found!\n");
        while (1)
        	_waitms(1000);
    }
    
	//Flash_Erase(flash, 0xf80000, 65536);
	
	i = Flash_Busy(flash);
		
	printf("Busy: %x\n", i);
	
    Dump(0xf80000, 32768);
    
	printf("Done\n");
	
    while (1)
    {
        _waitms(1000);
	}
}

void Dump(int address, int size)
{
    char buffer[257];
    int s = 0;
    
    while (s < size)
    {
        Flash_Read(flash, address, buffer, 256);
        
    	for (int i=0;i<256;i++)
    	{
        	if ((i & 0x0f) == 0)
        		printf("%8x: ", address + i);
        	printf("%02x ", buffer[i]);
        	if ((i & 0x0f) == 0x0f)
        		printf("\n");
 		}
 		
 		address += 256;
 		s += 256;
 	}
 
}
