/**
 * @file ws2812.h
 * @brief Set Neo Pixel colors for WS2812 LEDs
 * @author Michael Burmeister
 * @date November 10, 2020
 * @version 1.0
 * 
*/

#define COLOR(r, g, b)      (((r) << 16) | ((g) << 8) | (b))
#define SCALE(x, l)         ((x) * (l) / 255)
#define COLORX(r, g, b, l)  ((SCALE(r, l) << 16) | (SCALE(g, l) << 8) | SCALE(b, l))

//                         RRGGBB
#define COLOR_BLACK      0x000000
#define COLOR_RED        0xFF0000
#define COLOR_GREEN      0x00FF00
#define COLOR_BLUE       0x0000FF
#define COLOR_WHITE      0xFFFFFF
#define COLOR_CYAN       0x00FFFF
#define COLOR_MAGENTA    0xFF00FF
#define COLOR_YELLOW     0xFFFF00
#define COLOR_CHARTREUSE 0x7FFF00
#define COLOR_ORANGE     0xFF6000
#define COLOR_AQUAMARINE 0x7FFFD4
#define COLOR_PINK       0xFF5F5F
#define COLOR_TURQUOISE  0x3FE0C0
#define COLOR_REALWHITE  0xC8FFFF
#define COLOR_INDIGO     0x3F007F
#define COLOR_VIOLET     0xBF7FBF
#define COLOR_MAROON     0x320010
#define COLOR_BROWN      0x0E0600
#define COLOR_CRIMSON    0xDC283C
#define COLOR_PURPLE     0x8C00FF

/**
 * @brief program n number of led's
 * @param pin pin to use
 * @param leds array of long values to set each Neo Pixel
 * @param num number of led's to set
*/
void ws2812_set(int pin, unsigned long *leds, int num) __fromfile("libws2812/ws2812.c");
