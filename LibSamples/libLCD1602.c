/**
 * @brief LCD1602 display driver
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "lcd1602.h"


#define LCDCLK 6
#define LCDDTA 7


int main(int arc, char* argv)
{
    int i;
    
    i = LCD1602_Open(LCDCLK, LCDDTA);
    
    LCD1602_Backlight(1);
    
    LCD1602_Display(1,0,0);
    LCD1602_Clear();
    
    LCD1602_Cursor(5, 0);
    LCD1602_Print("0123456789012345");
    LCD1602_Cursor(0, 1);
    LCD1602_Print("0123456789012345");
    printf("done\n");
    
    while (1)
    {
        _waitms(1000);
	}
}
