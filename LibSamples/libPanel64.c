/**
 * @brief Test Panel64 functions
 * @author Michael Burmeister
 * @date April 28, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "Panel64.h"


int main(int argc, char** argv)
{
    int c;
    
    Panel_Start(3);

    c = Panel_Color(1, 1, 0);

    Panel_TextColor(c, 0);
    Panel_WriteSStr(10,10, "Hello");
    Panel_WriteSStr(10,18, "World");
    Panel_DrawLine(10, 26, 50, 26, c);
    _waitms(5000);
    Panel_ScrollVertical(8);
    _waitms(5000);
    Panel_ScrollHorizontal(8);

    while (1)
    {
        _waitms(1000);
	}
}
