/**
 * @file ds1302.h
 * @brief WaveShare Clock Calender device
 * @author Michael Burmeister
 * @date January 14, 2017
 * @version 1.2
 * 
*/

/**
 * @brief open connection to clock chip
 * @param mosi Master out slave in pin
 * @param cs Chip Select pin
 * @param sclk System Clock pin
 * @param miso Master in slave out pin
 *
*/
void DS1302_open(int mosi, int cs, int sclk, int miso) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get seconds
 * @return seconds
 *
*/
int DS1302_getSeconds(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get minutes
 * @return minutes
*/
int DS1302_getMinutes(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get hours
 * @return seconds
 *  returns the hours in 24 hour format
 *  or 12 hour format.  In 12 hour format use getAMPM
 *  to return a string with AM/PM value.
*/
int DS1302_getHours(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get am/pm string
 * @return ampm AM/PM string
 */
char *DS1302_getAMPM(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get day
 * @return day
*/
int DS1302_getDay(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get month
 * @return month
*/
int DS1302_getMonth(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get day of the week
 * @return day
 */
int DS1302_getWeekDay(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief Get year value 
 * @return year only last 2 digits
 */
int DS1302_getYear(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set Date 
 * @param year last two digits only
 * @param month
 * @param day
 */
void DS1302_setDate(int year, int month, int day) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set year
 * @param year only the last 2 digits of the year
 */
void DS1302_setYear(int year) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set month
 * @param month
 */
void DS1302_setMonth(int month) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set day
 * @param day
 */
void DS1302_setDay(int day) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set day of the week
 * @param weekday number from 1-sunday, 7 - saturday
 */
void DS1302_setWeekDay(int weekday) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set time
 * @param hours
 * @param minutes
 * @param seconds
 *  hours are in 24 hour format
 */
void DS1302_setTime(int hours, int minutes, int seconds) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set hours
 * @param hour
 *  Must be in 24 hour format
 */
void DS1302_setHour(int hour) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set 12 hour format
 * @param hour in 12 hour format
 * @param AmPm use A for AM and P for PM
 */
void DS1302_set12Hour(int hour, char AmPm) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set minutes
 * @param minutes
 */
void DS1302_setMinute(int minutes) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set seconds
 * @param seconds
 */
void DS1302_setSecond(int seconds) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get write protect state
 * @return 0 - false 1 - true
 */
int DS1302_getWriteProtect(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set write protect state
 *  prevents any register from
 *  being written to
 */
void DS1302_setWriteProtect(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief clear write protect state
 *  must be called before changing
 *  any date/time value or message
 */
void DS1302_clearWriteProtect(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief set propeller date/time
 *  This sets the tick value for
 *  unix date time functions used
 *  in the propeller libraries and the
 *  time must be accessed before every
 *  54 seonds or time will be lost
 */
void DS1302_setDateTime(void) __fromfile("libDS1302/ds1302.c");

/**
 * @brief save message in ram
 * @param msg
 *  Save a short message to 
 *  ram 31 bytes max
 */
void DS1302_setMessage(char *msg) __fromfile("libDS1302/ds1302.c");

/**
 * @brief get message from ram
 * @return message
 */
char *DS1302_getMessage(void) __fromfile("libDS1302/ds1302.c");