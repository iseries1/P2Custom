/**
 * @file veml7700.h
 * @brief VEML7700 Light Sensor Driver
 * @author Michael Burmeister
 * @version 1.0
 * @date December 02, 2023
 */


/**
 * @brief Initalize VEML7700 driver
 * @param clk clock pin
 * @param dta data pin
 * @return status
 */
int VEML7700_Init(int clk, int dta) __fromfile("libveml7700/veml7700.c");

/**
 * @brief Set operating mode
 * @param sense sensitivty mode 0 - 3
 * @param inte integration time 25, 50, 100, 200, 400, 800
 * @param pers persistance 0 - 3
 * @param inter interupt enable 0/1
 * @param power power mode 0/1
 */
void VEML7700_Mode(int sense, int inte, int pers, int inter, int power);

/**
 * @brief Set high/low threshold values
 * @param high value
 * @param low value
 */
void VEML7700_Threshold(int high, int low);

/**
 * @brief Set power saving mode
 * @param mode 1 - 4
 * @param enable 0/1
 */
void VEML7700_PowerMode(int mode, int enable);

/**
 * @brief Get ALS value
 * @return als value
 */
int VEML7700_GetALS(void);

/**
 * @brief Get White value
 * @return white value
 */
int VEML7700_GetWhite(void);

/**
 * @brief Get Lux value
 * @return lux
 */
int VEML7700_GetLux(void);

