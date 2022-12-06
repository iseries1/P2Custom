/**
 * @file lcd1602.h
 * @brief Drive LCD1602 Display
 * @author Michael Burmeister
 * @date 
 * @version 1.0
 * 
*/


/**
 * @brief Open display driver
 * @param clk clock pin
 * @param dta data pin
 */
int LCD1602_Open(int clk, int dta) __fromfile("liblcd1602/lcd1602.c");

/**
 * @brief Clear display
 */
void LCD1602_Clear(void);

/**
 * @brief Home cursor
 */
void LCD1602_Home(void);

/**
 * @brief Set display
 * @param display 1/0 on or off
 * @param cursor 1/0 on or off
 * @param blink 1/0 on or off
 */
void LCD1602_Display(int display, int cursor, int blink);

/**
 * @brief Setup display functions
 * @param length data length 1 - 8 bit 0 - 4 bit
 * @param lines set number of lines 1 - 2 lines 0 - 1 line
 * @param font set 0 - 5x8 or 1 - 5x10 
 */
void LCD1602_Function(int length, int lines, int font);

/**
 * @brief Get status
 * @return status
 */
int LCD1602_Status(void);

/**
 * @brief Set Backlight
 * @param on 0 - off 1 - on
 */
void LCD1602_Backlight(int on);

/**
 * @brief Write Character
 * @param chr character to write
 */
void LCD1602_Char(int chr);

/**
 * @brief Write a string
 * @param str string to write
 */
void LCD1602_Print(char *str);

/**
 * @brief Set Cursor Postion
 * @param x x position starting at 0
 * @param y y position 0, 1
 */
void LCD1602_Cursor(int x, int y);
