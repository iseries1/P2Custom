/**
 * @file LcdDisplay.h
 * @author Michael Burmeister
 * @date January 15, 2015
 * @brief This library adds functions for using the Parallax LCD Display
 * These functions convert the byte code data into functions for easy reference
 * 
*/

#include "simpletools.h"

/**
 * @brief Open a Connection to the LCD Display
 * @param Tx Transmitt data Pin.
 * @param Baud Baud rate of LCD Display
 *
*/
void Lcd_Open(char Tx, int Baud) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Position cursor on the LCD display.
 *
 * @param Col Column number from 0
 * @param Row Row number from 0
 *
*/
void Lcd_PosCursor(int Col, int Row) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Play a note form A to G for a given length of time
 *
 * @param Note Note to play from 0 to 6
 * @param Length Length of time to play note 64 - full
 *
*/
void Lcd_PlayNote(int Note, int Length) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Clear the LCD display and place the cursor at 0,0 with underline.
 *
 *
*/
void Lcd_Clr(void) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Set LCD display to turn display on/off, Cursor on/off, and Blink on/off
 *
 * @param On Turns the LCD Display On or Off
 * @param Cursor Set the Cursor Character On or Off
 * @param Blink Set the Cursor Character to Blink
 *
*/
void Lcd_Set(int On, int Cursor, int Blink) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Turn LCD backlight on or off
 *
 * @param OnOff Turns Backlight on/off (0/1).
 *
*/
void Lcd_BackLight(int OnOff) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Send a set of characters to the LCD display
 *
 * @param String Character string to display on LCD null terminated
 *
*/
void Lcd_Chars(char *String) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Send a single character to the LCD display
 *
 * @param c Character to display on LCD
 *
*/
void Lcd_Char(char c) __fromfile("liblcddisplay/lcddisplay.c");

/**
 * @brief Close Connection to the LCD Display.
 *
 *
*/
void Lcd_Close(void) __fromfile("liblcddisplay/lcddisplay.c");

