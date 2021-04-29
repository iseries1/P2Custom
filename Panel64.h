/**
 * @file Panel64.h
 * @brief Panel Driver for P2 P2
 * @author Michael Burmeister
 * @date April 28, 2021
 * @version 1.0
 * 
*/

/**
 * @brief start panel display driver
 */
void Panel_Start(void) __fromfile("libpanel64/panel64.c");

/**
 * @brief Combine color value
 * @param red red color
 * @param green green color
 * @param blue blue color
 * @return color value
 */
unsigned int Panel_Color(char red, char green, char blue);

/**
 * @brief Plot point
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param color value
 */
void Panel_Plot(int x, int y, int color);

/**
 * @brief Set text color
 * @param foreground
 * @param background
 */
void Panel_TextColor(int foreground, int background);

/**
 * @brief Write Character
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param character to write
 */
void Panel_WriteChar(int x, int y, int character);

/**
 * @brief Write String
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param string to write
 */
void Panel_WriteStr(int x, int y, char *string);

/**
 * @brief Write small Characters
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param character to write
 */
void Panel_WriteSChar(int x, int y, char character);

/**
 * @brief Write small text
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param string to write
 */
void Panel_WriteSStr(int x, int y, char *string);

/**
 * @brief Draw line art
 * @param x1 start point
 * @param y1 start point
 * @param x2 ending point
 * @param y2 ending point
 * @param color of line
 */
void Panel_DrawLine(int x1, int y1, int x2, int y2, int color);

/**
 * @brief Draw Box art
 * @param x1 start point
 * @param y1 start point
 * @param x2 end bottom corner
 * @param y2 end bottom corner
 * @param color of line
 */
void Panel_DrawBox(int x1, int y1, int x2, int y2, int color);

/**
 * @brief Scroll Up/down
 * @param amount to scroll
 */
void Panel_ScrollVertical(int amount);

/**
 * @brief Scroll Left/Right
 * @param amount to scroll
 */
void Panel_ScrollHorizontal(int amount);