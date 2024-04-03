/**
 * @file pcf8523.h
 * @brief Driver for PCF8523 Real Time Clock Module
 * @author Michael Burmeister
 * @version 1.0
 * @date April 2, 2024
 * 
 */

#define PCF8523_AF       0x08
#define PCF8523_SF       0x10
#define PCF8523_CTBF     0x20
#define PCF8523_CTAF     0x40
#define PCF8523_WTAF     0x80


/**
 * @brief Initialize Real Time clock Driver
 * @param clk clock pin to use
 * @param dta data pin to use
 * @param status (1 - ok, -1 - error)
 */
int PCF8523_Init(int clk, int dta)  __fromfile("libpcf8523/pcf8523.c");

/**
 * @brief Get Time values
 * @param seconds pointer value
 * @param minutes pointer value
 * @param hours pointer value
 * @return seconds
*/
int PCF8523_GetTime(int *seconds, int *minutes, int *hours);

/**
 * @brief Get Day Of The Week
 * @return dow
 */
int PCF8523_WeekDay(void);

/**
 * @brief Get Date values
 * @param day pointer value
 * @param month pointer value
 * @param year pointer value
 * @return days value
*/
int PCF8523_GetDate(int *day, int *month, int *year);

/**
 * @brief Set Date
 * @param month (1 - 12)
 * @param day (1 - 31)
 * @param year (2000 - 2099)
 * 
 */
void PCF8523_SetDate(int month, int day, int year);

/**
 * @brief Set Time
 * @param hours (0 - 23)
 * @param minutes (0 - 59)
 * @param seconds (0 - 59)
 * 
 */
void PCF8523_SetTime(int hours, int minutes, int seconds);

/**
 * @brief Set System Date Time
 * @return time serial number
 */
int PCF8523_SetDateTime(void);

/**
 * @brief Get Control Value
 * @return control (1 - 3)
 */
int PCF8523_Control(void);

/**
 * @brief Set Control Value
 * @param control value (1 - 3)
 */
void PCF8523_SetControl(int control);

/**
 * @brief Set Alarm Value
 * @param minutes -1 to disable
 * @param hours  -1 to disable
 * @param day -1 to disable
 * @param dayofweek -1 to disable
 * 
 */
void PCF8523_SetAlarm(int minutes, int hours, int day, int dayofweek);

/**
 * @brief Get Alarm Value
 * @param minute pointer value
 * @param hour pointer value
 * @param day pointer value
 * @param weekday pointer value
 * @return status of alarm
 */
int PCF8523_GetAlarm(int *minute, int *hour, int *day, int *weekday);

/**
 * @brief Set Time Offset
 * @param offset (0 to disable)
 */
void PCF8523_SetOffset(int offset);

/**
 * @brief Clear Flags
 * @param flags AF, SF, CTBF, CTAF, WTAF
 */
void PCF8523_ClearFlags(int flags);

/**
 * @brief Get Flags
 * @return flags (AF, SF, CTBF, CTAF, WTAF)
*/
int PCF8523_GetFlags(void);

/**
 * @brief Set Power option
 * @param option (0 - battery, 3 - no battery)
 */
void PCF8523_SetPower(int option);
