/**
 * @file st7789.h
 * @brief Driver program for ST7789 LCD Display
 * @author Michael Burmeister
 * @date December 7, 2021
 * @version 1.0
 * @details Because the driver memory is 240x320 and the screen is 135x240
 * there are blank areas that do not show up on the screen IE in non display area.
 * Need to offset screen memory by 40 pixels and the row by 52/53 pixels
 * Driver is to slow for anything above 60Mhz.
*/

// Some ready-made 16-bit ('565') color settings:
#define ST7789_BLACK 0x0000
#define ST7789_WHITE 0xFFFF
#define ST7789_RED 0xF800
#define ST7789_GREEN 0x07E0
#define ST7789_BLUE 0x001F
#define ST7789_CYAN 0x07FF
#define ST7789_MAGENTA 0xF81F
#define ST7789_YELLOW 0xFFE0
#define ST7789_ORANGE 0xFC00


/**
 * @brief Initialize ST7789 Driver
 * pins are clk, miso, mosi, cs, reset, dc, cd, lite
 * @param pins starting pin number
 */
void ST7789_init(char pins) __fromfile("libst7789/st7789.c");

/**
 * @brief Set rotation
 * @param rotation 0 - 3
 */
void ST7789_Rotation(char rotation);

/**
 * @brief Clear screen
 * @param color to use
 */
void ST7789_Cls(int color);

/**
 * @brief Set windows area
 * @param sx starting x value
 * @param sy starting y value
 * @param w width of area
 * @param h height of area
 */
void ST7789_Window(int sx, int sy, int w, int h);

/**
 * @brief Fill rectangle
 * @param sx starting x value
 * @param sy starting y value
 * @param width of area
 * @param height of area
 * @param color of area to fill
 */
void ST7789_FillRectangle(int sx, int sy, int width, int height, int color);

/**
 * @brief Write color
 * @param color to write
 * @param size of color to write
 */
void ST7789_WriteColor(int color, int size);

/**
 * @brief Plot pixel color
 * @param x point
 * @param y point
 * @param color of pixel
 */
void ST7789_Plot(int x, int y, int color);

/**
 * @brief Display on/off
 * @param state 0 - off, 1 - on
 */
void ST7789_Display(int state);

/**
 * @brief Sleep on/off
 * @param state 0 - off, 1 - on
 */
void ST7789_Sleep(int state);

/**
 * @brief Set cursor
 * @param x location
 * @param y location
 */
void ST7789_SetCursor(int x, int y);

/**
 * @brief Set foreground and background color
 * @param foreground color -1 no change
 * @param background color -1 no change
 */
void ST7789_SetColor(int foreground, int background);

/**
 * @brief Write standard string
 * @param string to write
 */
void ST7789_WriteSString(char *string);

/**
 * @brief Write standard character
 * @param character to write
 */
void ST7789_WriteSCharacter(char character);

/**
 * @brief Write large character
 * @param character to write
 */
void ST7789_WriteCharacter(char character);

/**
 * @brief Write large string
 * @param string to write
 */
void ST7789_WriteString(char *string);

/**
 * @brief Write xtra large character
 * @param character to write
 */
void ST7789_WriteXCharacter(char *character);

/**
 * @brief Write xtra large string
 * @param string to write
 */
void ST7789_WriteXString(char *string);

/**
 * @brief Draw line
 * @param x start location
 * @param y start location
 * @param ex ending x location
 * @param ey ending y location
 * @param color line color
 */
void ST7789_Drawline(int x, int y, int ex, int ey, int color);

/**
 * @brief Draw box
 * @param x start location
 * @param y start location
 * @param ex ending x location
 * @param ey ending y location
 * @param color line color
 */
void ST7789_DrawBox(int x, int y, int ex, int ey, int color);

/**
 * @brief Build color value
 * @param red value
 * @param green value
 * @param blue value
 * @return color RGB 656
 */
int ST7789_BuildColor(int red, int green, int blue);
