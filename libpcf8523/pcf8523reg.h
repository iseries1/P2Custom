/**
 * @brief Real Time Clock Driver
 * @author Michael Burmeister
 * @date April 2, 2024
 * @version 1.0
 * 
*/


#define PCF8523_ADDR     0x68
#define PCF8523_CNTRL1   0x00
#define PCF8523_CNTRL2   0x01
#define PCF8523_CNTRL3   0x02
#define PCF8523_SECONDS  0x03
#define PCF8523_MINUTES  0x04
#define PCF8523_HOUR     0x05
#define PCF8523_DAY      0x06
#define PCF8523_WEEKDAY  0x07
#define PCF8523_MONTH    0x08
#define PCF8523_YEAR     0x09

#define PCF8523_AMINUTES 0x0A
#define PCF8523_AHOUR    0x0B
#define PCF8523_ADAY     0x0C
#define PCF8523_AWEEKDAY 0x0D

