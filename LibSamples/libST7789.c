/**
 * @brief Driver program for ST7789 LCD Display
 * @author Michael Burmeister
 * @date December 7, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "ST7789.h"


int main(int argc, char** argv)
{
    int i;


    ST7789_init(8);

    ST7789_Display(0);

    ST7789_Cls(ST7789_RED);

    ST7789_Display(1);

    _waitms(5000);

    ST7789_Cls(ST7789_BLACK);

    ST7789_FillRectangle(0, 0, 1, 1, ST7789_RED);

    ST7789_SetCursor(1, 10);

    ST7789_WriteSString("Test");

    ST7789_SetCursor(10, 30);

    ST7789_WriteString("Test");

    ST7789_WriteXString("Test");

    ST7789_Drawline(1, 100, 200, 100, ST7789_RED);

    printf("Done\n");

    while (1)
    {
        _waitms(1000);
	}
}
