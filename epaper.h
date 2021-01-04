/**
 * @file epaper.h
 * @brief Driver for e-Paper display
 * @author Michael Burmeister
 * @date July 7, 2019
 * @version 1.0
 * 
*/


/**
 * @brief initialize epaper display
 * @param din data input
 * @param clk clock data
 * @param cs chip select
 * @param dc data/command
 * @param rst reset
 * @param busy busy output
 */
int epaper_init(char din, char clk, char cs, char dc, char rst, char busy) __fromfile("libepaper/epaper.c");

/**
 * @brief set sleep mode
 * @param sleep 0 - no, 1 - yes
 */
void epaper_sleep(char sleep) __fromfile("libepaper/epaper.c");

/**
 * @brief update display
 */
void epaper_update(void) __fromfile("libepaper/epaper.c");

/**
 * @brief clear the screen
 * @param color white/black
 */
void epaper_cls(char color) __fromfile("libepaper/epaper.c");

/**
 * @brief plot point
 * @param x coordinate
 * @param y coordinate
 * @param c color black/white
 */
void epaper_plot(short x, short y, char c) __fromfile("libepaper/epaper.c");

/**
 * @brief get buffer pointer
 * @return buffer
 */
unsigned char *epaper_buffer(void) __fromfile("libepaper/epaper.c");

/**
 * @brief write large character
 * @param x coordinate
 * @param y coordinate
 * @param ch character
 */
void epaper_writeChar(short x, short y, char ch) __fromfile("libepaper/epaper.c");

/**
 * @brief write small character
 * @param x coordinate
 * @param y coordinate
 * @param ch character
 */
void epaper_writeSChar(short x, short y, char ch) __fromfile("libepaper/epaper.c");

/**
 * @brief write extra large character 32x64
 * @param x offset
 * @param y offset
 * @param c character
 */
void epaper_writeXChar(short x, short y, char c) __fromfile("libepaper/epaper.c");

/**
 * @brief write character string
 * @param x coordinate
 * @param y coordinate
 * @param s string
 */
void epaper_writeStr(short x, short y, char *s) __fromfile("libepaper/epaper.c");

/**
 * @brief write small character string
 * @param x coordinate
 * @param y coordinate
 * @param s pointer to string
 */
void epaper_writeSStr(short x, short y, char *s) __fromfile("libepaper/epaper.c");

/**
 * @brief write extra large string 32x64
 * @param x offset
 * @param y offset
 * @param s pointer to string
 */
void epaper_writeXStr(short x, short y, char *s) __fromfile("libepaper/epaper.c");

/**
 * @brief draw line
 * @param x starting coordinate
 * @param y starting coordinate
 * @param x1 ending coordinate
 * @param y1 ending coordinate
 * @param c color of line On/Off
 */
void epaper_drawLine(short x, short y, short x1, short y1, char c) __fromfile("libepaper/epaper.c");

/**
 * @brief draw a box
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param c On/Off
 */
void epaper_drawBox(short x, short y, short x1, short y1, char c) __fromfile("libepaper/epaper.c");
