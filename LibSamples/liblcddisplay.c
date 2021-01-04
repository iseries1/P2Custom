/*
 * @brief LCD Display Library for Parallax LCD Display
 * @date: December 25, 2014
 * @author: Michael Burmeister 
 * @version: 1.0
*/

#include <stdio.h>
#include <propeller.h>
#include "simpletools.h"
#include "lcddisplay.h"

#define Tx 16
#define Baud 19200


int main()
{
  printf("Starting\n");
  
  Lcd_Open(Tx, Baud);
  Lcd_BackLight(1);
  pause(1000);
  Lcd_PosCursor(3, 0);
  Lcd_Chars("Back Light On");
  pause(2000);
  Lcd_BackLight(0);
  Lcd_PosCursor(5, 0);
  Lcd_Clr();
  Lcd_Chars("Display Off");
  pause(5000);
  Lcd_Set(0, 1, 1);
  pause(2000);
  Lcd_Set(1, 1, 1);
  pause(2000);
  Lcd_Clr();
  Lcd_PlayNote(0, 6);
  pause(1000);
  Lcd_Close();
  
  printf("Done\n");
}
