/**
 * @file fullduplex.h
 * @brief Program purpose
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

/**
 * @brief Initialize full duplex driver
 * @param baud baudrate to use
 */
void FD_Init(int baud) __fromfile("libfullduplex/fullduplex.c");

/**
 * @brief Get character from input
 * @return character
 */
unsigned char FD_Getch(void);

/**
 * @brief Check for character on input
 * @return 1 - character available or 0
 */
int FD_Check(void);

/**
 * @brief Put character on output
 * @param character to send
 */
void FD_Putch(unsigned char character);

/**
 * @brief Put string of characters
 * @param string of characters
 */
void FD_PutStr(unsigned char *string);

/**
 * @brief Get count of characters
 * @return count
 */
int FD_Count(void);
