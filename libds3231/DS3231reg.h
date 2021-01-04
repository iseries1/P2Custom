/**
 * @brief Driver for DS3231 (HW084)
 * @author Michael Burmeister
 * @date December 25, 2020
 * @version 1.0
 * 
*/

#define DS3231_ADDRESS 0xd0
#define DS3231_SECONDS 0x00
#define DS3231_MINUTES 0x01
#define DS3231_HOUR 0x02
#define DS3231_DAY 0x03
#define DS3231_DATE 0x04
#define DS3231_MONTH 0x05
#define DS3231_YEAR 0x06
#define DS3231_ALARM1_SECONDS 0x07
#define DS3231_ALARM1_MINUTES 0x08
#define DS3231_ALARM1_HOURS 0x09
#define DS3231_ALARM1_DAY 0x0a
#define DS3231_ALARM2_MINUTES 0x0b
#define DS3231_ALARM2_HOURS 0x0c
#define DS3231_ALARM2_DAY 0x0d
#define DS3231_CONTROL 0x0e
#define DS3231_STATUS 0x0f
#define DS3231_AGING 0x10
#define DS3231_TEMPERATURE 0x11
