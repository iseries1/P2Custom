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
int DS3231_Seconds(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read minutes value
 * @return minutes
 */
int DS3231_Minutes(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read hours value
 * @return hours
 */
int DS3231_Hour(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read day of the week value
 * @return days
 */
int DS3231_Dayofweek(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read Day number value
 * @return day
 */
int DS3231_Day(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read Month value
 * @return month
 */
int DS3231_Month(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read Year value
 * @return year
 */
int DS3231_Year(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Year value
 * @param year
 */
int DS3231_SetYear(int year) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Month value
 * @param month
 */
int DS3231_SetMonth(int month) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Day value
 * @param day
 */
int DS3231_SetDay(int day) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Dayofweek value
 * @param dayofweek
 */
int DS3231_SetDayofweek(int dayofweek) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Hours value
 * @param hour
 */
int DS3231_SetHour(int hour) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Minutes value
 * @param minutes
 */
int DS3231_SetMinutes(int minutes) __fromfile("libds3231/DS3231.c");

/**
 * @brief Write Seconds value
 * @param seconds
 */
int DS3231_SetSeconds(int seconds) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read AM/PM Value
 * @return value 0 - am, 1 - pm
 */
int DS3231_AMPM(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Set Century value
 * @param century 0 or 1
 */
void DS3231_SetCentury(int century) __fromfile("libds3231/DS3231.c");

/**
 * @brief Set date
 * @param month month number
 * @param day day number
 * @param year year 0 - 99
 */
int DS3231_SetDate(int month, int day, int year) __fromfile("libds3231/DS3231.c");

/**
 * @brief Set time
 * @param hour hour 0 - 23
 * @param minutes minutes 0 - 59
 * @param seconds seconds 0 - 59
 */
int DS3231_SetTime(int hour, int minutes, int seconds) __fromfile("libds3231/DS3231.c");

/**
 * @brief Set System date and time
 * set date time for c functions
 */
void DS3231_SetDateTime(void) __fromfile("libds3231/DS3231.c");

/**
 * @brief Read Temperature
 * @return temp in Celcius
 */
int DS3231_Temperature(void) __fromfile("libds3231/DS3231.c");
