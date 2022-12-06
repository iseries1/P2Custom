/**
 * @file ssd1331.h
 * @brief Colored Oled Display Driver
 * @author Michael Burmeister
 * @date December 11, 2018
 * @version 1.0
 * 
*/

/* @brief Open connection to Oled Display
 * @param DIN data in
 * @param CLK clock pin
 * @param CS chip select
 * @param DC data or command
 * @param RES reset pin
*/
void SSD1331_init(char DIN, char CLK, char CS, char DC, char RES) __fromfile("libSSD1331/SSD1331.c");

/* @brief set rotation
 * @param rotation
 */
void SSD1331_rotation(char rotation);

/* @brief clear screen
 */
void SSD1331_cls(void);

/*
 * @brief Invert display
 * @param state 0=normal, 1=invert, 2=all on, 3=all off
 */
void SSD1331_invert(short state);

/* @brief build 565 rgb color value
 * @param red 5 bits
 * @param green 6 bits
 * @param blue 5 bits
 * @return color
 */

unsigned short SSD1331_color(char red, char green, char blue);

/*
 * @brief plot a point
 * @param x offset
 * @param y offset
 * @param color value
 */
void SSD1331_plot(short x, short y, unsigned short color);

/*
 * @brief set foreground and background
 * @param foreground
 * @param background
 */
void SSD1331_textColor(unsigned short foreground, unsigned short background);

/*
 * @brief write char
 * @param x offset
 * @param y offset
 * @param c character
 */
void SSD1331_writeChar(char x, char y, char c);

/*
 * @brief write string
 * @param x offset
 * @param y offset
 * @param s pointer to string
 */
void SSD1331_writeStr(char x, char y, char* s);

/*
 * @brief write small 5x7 char
 * @param x offset
 * @param y offset
 * @param c character
 */
void SSD1331_writeSChar(char x, char y, char c);

/*
 * @brief write small 5x7 string
 * @param x offset
 * @param y offset
 * @param c pointer to string
 */
void SSD1331_writeSStr(char x, char y, char* c);

/*
 * @brief draw line 
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color
 */
void SSD1331_drawLine(short x, short y, short x1, short y1, unsigned short color);

/*
 * @brief draw a box
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color
 */
void SSD1331_drawBox(short x, short y, short x1, short y1, unsigned short color);

/*
 * @brief draw a box filled
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color
 * @param fill color
 */
void SSD1331_drawFilledBox(short x, short y, short x1, short y1, unsigned short color, unsigned short fill);

/*
 * @brief display on or off
 * @param state
 */
void SSD1331_display(char state);

/*
 * @brief Scroll right
 * @param amount 1 - 47
 * @param start row
 * @param end row
 * @param speed 0, 1, 2, or 3 slowest
 */
void SSD1331_scrollRight(char amount, char start, char end, char speed);

/*
 * @brief Scroll left
 * @param amount 1 - 47
 * @param start row
 * @param end row
 * @param speed 0, 1, 2, or 3 slowest
 */
void SSD1331_scrollLeft(char amount, char start, char end, char speed);

/*
 * @brief Scroll up
 * @param amount 1 - 31
 * @param speed 0, 1, 2, or 3 slowest
 */
void SSD1331_scrollUp(char amount, char speed);

/*
 * @brief Scroll down
 * @param amount 1 - 31
 * @param speed 0, 1, 2, or 3 slowest
 */
void SSD1331_scrollDown(char amount, char speed);

/*
 * @brief Scroll stop
 */
void SSD1331_scrollStop(void);
