/**
 * @file DS3231.h
 * @brief Driver for DS3231 (HW084)
 * @author Michael Burmeister
 * @date December 25, 2020
 * @version 1.0
 * 
*/

/**
 * @brief Open connection to device
 * @param dsclk clock pin
 * @param dssda data pin
 */
void DS3231_Open(int dsclk, int dssda) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read seconds value
 * @return seconds
 */
int DS3231_Seconds(void);

/**
 * @brief Read minutes value
 * @return minutes
 */
int DS3231_Minutes(void);

/**
 * @brief Read hours value
 * @return hours
 */
int DS3231_Hour(void);

/**
 * @brief Read day of the week value
 * @return days
 */
int DS3231_Dayofweek(void);

/**
 * @brief Read Day number value
 * @return day
 */
int DS3231_Day(void);

/**
 * @brief Read Month value
 * @return month
 */
int DS3231_Month(void);

/**
 * @brief Read Year value
 * @return year
 */
int DS3231_Year(void);

/**
 * @brief Write Year value
 * @param year
 */
int DS3231_SetYear(int year);

/**
 * @brief Write Month value
 * @param month
 */
int DS3231_SetMonth(int month);

/**
 * @brief Write Day value
 * @param day
 */
int DS3231_SetDay(int day);

/**
 * @brief Write Dayofweek value
 * @param dayofweek
 */
int DS3231_SetDayofweek(int dayofweek);

/**
 * @brief Write Hours value
 * @param hour
 */
int DS3231_SetHour(int hour);

/**
 * @brief Write Minutes value
 * @param minutes
 */
int DS3231_SetMinutes(int minutes);

/**
 * @brief Write Seconds value
 * @param seconds
 */
int DS3231_SetSeconds(int seconds);

/**
 * @brief Read AM/PM Value
 * @return value 0 - am, 1 - pm
 */
int DS3231_AMPM(void);

/**
 * @brief Set Century value
 * @param century 0 or 1
 */
void DS3231_SetCentury(int century);

/**
 * @brief Set date
 * @param month month number
 * @param day day number
 * @param year year 0 - 99
 */
int DS3231_SetDate(int month, int day, int year);

/**
 * @brief Set time
 * @param hour hour 0 - 23
 * @param minutes minutes 0 - 59
 * @param seconds seconds 0 - 59
 */
int DS3231_SetTime(int hour, int minutes, int seconds);

/**
 * @brief Set System date and time
 * set date time for c functions
 */
void DS3231_SetDateTime(void);

/**
 * @brief Read Temperature
 * @return temp in Celcius
 */
int DS3231_Temperature(void);
