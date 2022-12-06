/**
 * @brief Drive LCD1602 Display
 * @author Michael Burmeister
 * @date Michael Burmeister
 * @version 1.0
 * 
*/

#include "lcd1602.h"
#include "LCD1602reg.h"
#include <propeller.h>
#include <string.h>
#include "simpletools.h"

int LCD1602_Read(void);
int LCD1602_Write(int);
void LCD1602_Nible(int);
void LCD1602_Send(int, int);

i2c Bus;
i2c *pbus;
int backlight;


int LCD1602_Open(int clk, int dta)
{
    int i;
    
    pbus = i2c_open(&Bus, clk, dta, 0);
    backlight = 0;
    LCD1602_Write(0x00);
    _waitms(1000);
    
    LCD1602_Nible(0x30);
    _waitus(4500);
    LCD1602_Nible(0x30);
    _waitus(4500);
    LCD1602_Nible(0x30);
    _waitus(150);
    LCD1602_Nible(0x20);
    
    LCD1602_Function(0,1,0);
    LCD1602_Display(1,0,0);
    LCD1602_Clear();
    LCD1602_Send(0x06, 0);
    
    i = LCD1602_Read();
    return i;
}

void LCD1602_Clear()
{
    LCD1602_Send(LCD1602_CLEAR, 0);
    _waitms(2);
}

void LCD1602_Home()
{
    LCD1602_Send(LCD1602_HOME, 0);
    _waitms(2);
}

void LCD1602_Display(int display, int cursor, int blink)
{
    int i;
    
    i = LCD1602_DISPLAY | (display << 2) | (cursor << 1) | blink;
    LCD1602_Send(i, 0);
}

void LCD1602_Function(int length, int lines, int font)
{
    int i;
    
    i = LCD1602_FUNCTION | (lines << 3) | (length << 4) | (font << 2);
    LCD1602_Send(i, 0);
}

int LCD1602_Status()
{
    return LCD1602_Read();
}

void LCD1602_Backlight(int on)
{
    if (on)
	    backlight = LCD1602_BACKLIGHT;
	else
		backlight = 0;
}

void LCD1602_Char(int chr)
{
    LCD1602_Send(chr, 1);
}

void LCD1602_Print(char *str)
{
    for (int i=0;i<strlen(str);i++)
    	LCD1602_Send(str[i], 1);
}

void LCD1602_Cursor(int x, int y)
{
    int i;
    
    i = x + y * 0x40;
    i = i & 0x7f;
    LCD1602_Send(LCD1602_DDADDRESS | i, 0);
}


/**
 * @brief Built in Functions
 */

int LCD1602_Read()
{
    int i;
    
    i = i2c_poll(pbus, LCD1602_ADDRESS | 1);
    i = i2c_readByte(pbus, 1);
    i2c_stop(pbus);
    return i;
}

int LCD1602_Write(int data)
{
    int i;
    
    i = 0;
    i = i2c_poll(pbus, LCD1602_ADDRESS);
    if (i != 0)
    	return -1;
    i = i2c_writeByte(pbus, data);
    i2c_stop(pbus);
    return i;
}

/**
 * Write to the Expander interface that talks to LCD1602
 * 4 bits at a time
 * Map b0 = RS, b1 = RW, b2 = CS(EN), b3 = Backlight
 */
void LCD1602_Nible(int n)
{
    LCD1602_Write(n | backlight);
    LCD1602_Write(n | LCD1602_ENABLE | backlight);
    _waitus(1);
    LCD1602_Write(n | backlight);
    _waitus(50);
}

void LCD1602_Send(int value, int mode)
{
    int i;
    
    i = value & 0xf0;
    LCD1602_Nible(i | mode);
    i = (value & 0x0f) << 4;
    LCD1602_Nible(i | mode);
}
