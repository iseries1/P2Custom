/**
 * @file HX8357.h
 * @brief HX8357 320x480 display panel
 * @author Michael Burmeister
 * @date March 11, 2019
 * @version 1.0
 * 
*/

// Color definitions
#define HX8357_BLACK   0x0000
#define HX8357_BLUE    0x001F
#define HX8357_RED     0xF800
#define HX8357_GREEN   0x07E0
#define HX8357_CYAN    0x07FF
#define HX8357_MAGENTA 0xF81F
#define HX8357_YELLOW  0xFFE0  
#define HX8357_WHITE   0xFFFF

/**
 * @brief set connection parameters
 * @param Clk
 * @param MISO
 * @param MOSI
 * @param CS
 * @param DC
 * @param RST
 * @param LITE
 * @return open
 */
int HX8357_open(char Clk, char MISO, char MOSI, char CS, char DC, char RST, char LITE) __fromfile("libHX8357/HX8357.c");

/**
 * @brief get control value
 * @return value
 */
int HX8357_control(void) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set rotation
 * @param rotation
 */
void HX8357_rotation(char rotation) __fromfile("libHX8357/HX8357.c");

/**
 * @brief invert display
 * @param yes
 */
void HX8357_invert(char yes) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set window location
 * @param x
 * @param y
 * @param width
 * @param height
 */
void HX8357_window(short x, short y, short width, short height) __fromfile("libHX8357/HX8357.c");

/**
 * @brief push color
 * @brief color
 */
void HX8357_pushColor(short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write pixel color
 * @param color
 */
void HX8357_writePixel(short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write color
 * @param color
 * @param len
 */
void HX8357_writeColor(short color, int len) __fromfile("libHX8357/HX8357.c");

/**
 * @brief plot point color
 * @param x
 * @param y
 * @param color
 */
void HX8357_plot(short x, short y, short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief fill rectangle
 * @param x
 * @param y
 * @param width
 * @param height
 * @param color
 */
void HX8357_fillRectangle(short x, short y, short width, short height, short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief draw pixel color
 * @param x
 * @param y
 * @param color
 */
void HX8357_drawPixel(short x, short y, short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief clear screen
 * @param color
 */
void HX8357_cls(short color) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set display on
 * @param mode 0/1 off/on
 */
void HX8357_displayOn(char mode) __fromfile("libHX8357/HX8357.c");

/**
 * @brief put display to sleep
 * @param sleep 0/1 off/on
 */
void HX8357_sleepOn(char sleep) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set inverse on/off
 * @param inverse 0/1 on/off
 */
void HX8357_inverse(char inverse) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set all pixels on/off
 * @param set 0/1 on/off
 */
void HX8357_allPixels(char set) __fromfile("libHX8357/HX8357.c");

/**
 * @brief display mode normal/partial
 * @brief mode 0/1 normal/partial
 */
void HX8357_displayMode(char mode) __fromfile("libHX8357/HX8357.c");

/**
 * @brief set text color
 * @param fgcolor
 * @param bgcolor
 */
void HX8357_textColor(short fgcolor, short bgcolor) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write small string 8x8 (5x7)
 * @param x
 * @param y
 * @param text
 */
void HX8357_writeSStr(short x, short y, char *text) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write small character 8x8 (5x7)
 * @param x
 * @param y
 * @param character
 */
void HX8357_writeSChar(short x, short y, char character) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write character 16x32
 * @param x offset
 * @param y offset
 * @param c character
 */
void HX8357_writeChar(short x, short y, char c) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write string 16x32
 * @param x offset
 * @param y offset
 * @param s pointer to string
 */
void HX8357_writeStr(short x, short y, char* s) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write extra large character 32x64
 * @param x offset
 * @param y offset
 * @param c character
 */
void HX8357_writeXChar(short x, short y, char c) __fromfile("libHX8357/HX8357.c");

/**
 * @brief write extra large string 32x64
 * @param x offset
 * @param y offset
 * @param s pointer to string
 */
void HX8357_writeXStr(short x, short y, char *s) __fromfile("libHX8357/HX8357.c");

/*
 * @brief draw line 
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color
 */
void HX8357_drawLine(short x, short y, short x1, short y1, short color) __fromfile("libHX8357/HX8357.c");

/*
 * @brief draw a box
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color On/Off
 */
void HX8357_drawBox(short x, short y, short x1, short y1, short color) __fromfile("libHX8357/HX8357.c");

/* @brief build 888 rgb color value
 * @param red 8 bits
 * @param green 8 bits
 * @param blue 8 bits
 * @return color
 */
unsigned short HX8357_color(char red, char green, char blue) __fromfile("libHX8357/HX8357.c");
