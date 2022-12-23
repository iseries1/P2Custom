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
 * @param panels number of 64 panels
 */
void Panel_Start(int panels) __fromfile("libpanel64/panel64.c");

/**
 * @brief Combine color value
 * @param red red color
 * @param green green color
 * @param blue blue color
 * @return color value
 */
unsigned int Panel_Color(char red, char green, char blue);

/**
 * @brief Set Pixel Color at point
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param color value
 */
void Panel_SetPixel(int panel, int x, int y, int color);

/**
 * @brief Clear Panel with color
 * @param panel number 0 - last-1
 * @param color value
 *
 */
void Panel_Clear(int panel, int color);

/**
 * @brief Set text color
 * @param foreground
 * @param background
 */
void Panel_TextColor(int foreground, int background);

/**
 * @brief Write Character
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param character to write
 */
void Panel_WriteChar(int panel, int x, int y, int character);

/**
 * @brief Write Large Characters
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param character to write
 */
void Panel_WriteXStr(int panel, int x, int y, int character);

/**
 * @brief Write String
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param string to write
 */
void Panel_WriteStr(int panel, int x, int y, char *string);

/**
 * @brief Write small Characters
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param character to write
 */
void Panel_WriteSChar(int panel, int x, int y, char character);

/**
 * @brief Write small text
 * @param panel number 0 - last-1
 * @param x (0 - 63)
 * @param y (0 - 63)
 * @param string to write
 */
void Panel_WriteSStr(int panel, int x, int y, char *string);

/**
 * @brief Draw line art
 * @param panel number 0 - last-1
 * @param x1 start point
 * @param y1 start point
 * @param x2 ending point
 * @param y2 ending point
 * @param color of line
 */
void Panel_DrawLine(int panel, int x1, int y1, int x2, int y2, int color);

/**
 * @brief Draw Box art
 * @param panel number 0 - last-1
 * @param x1 start point
 * @param y1 start point
 * @param x2 end bottom corner
 * @param y2 end bottom corner
 * @param color of line
 */
void Panel_DrawBox(int panel, int x1, int y1, int x2, int y2, int color);

/**
 * @brief Draw Circle
 * @param panel number 0 - last-1
 * @param x starting point
 * @param y starting point
 * @param radius 
 * @param color 
 */
void Panel_DrawCircle(int panel, int x, int y, int radius, int color);

/**
 * @brief Scroll Up/down
 * @param panel number 0 - last-1
 * @param amount to scroll
 */
void Panel_ScrollVertical(int panel, int amount);

/**
 * @brief Scroll Left/Right
 * @param panel number 0 - last-1
 * @param amount to scroll
 */
void Panel_ScrollHorizontal(int panel, int amount);

/**
 * @brief Get pixel Value
 * @param panel number 0 - last-1
 * @param x point
 * @param y point
 */
int Panel_GetPixel(int panel, int x, int y);
