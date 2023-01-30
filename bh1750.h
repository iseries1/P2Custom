/**
 * @file bh1750.h
 * @brief bh1750 light sensor driver
 * @author Michael Burmeister
 * @date January 28, 2023
 * @version 1.0
 * 
*/

#define BH1750_PWR_DWN 0x00 
#define BH1750_PWR_UP  0x01 
#define BH1750_RESET   0x07 
#define BH1750_CHRM    0x10 
#define BH1750_CHRM2   0x11
#define BH1750_CLRM    0x13
#define BH1750_OHRM    0x20
#define BH1750_OHRM2   0x21
#define BH1750_OLRM    0x23


/**
 * @brief Initialize driver
 * @param clk i2c clock pin
 * @param sda i2c data pin
 * @return status 0 - Not Found, 1 - Found
 */
int BH1750_Init(int clk, int sda) __fromfile("libbh1750/bh1750.c");

/**
 * @brief Send Command
 * @param cmd command to send
 */
void BH1750_Cmd(char cmd);

/**
 * @brief Read Value
 * @return value 
 */
int BH1750_Read(void);
