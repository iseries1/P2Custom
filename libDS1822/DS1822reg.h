/**
 * @brief TS1822 temperature driver
 * @author Michael Burmeister
 * @date December 27, 2020
 * @version 1.0
 * 
*/

#define DS1822_SEARCH 0xf0
#define DS1822_READ 0x33
#define DS1822_MATCH 0x55
#define DS1822_SKIP 0xcc
#define DS1822_ALARM 0xec
#define DS1822_CONVERT 0x44
#define DS1822_WRITESCRATCHPAD 0x4e
#define DS1822_READSCRATCHPAD 0xbe
#define DS1822_COPYSCRATCHPAD 0x48
#define DS1822_RECALLSCRATCHPAD 0xb8
#define DS1822_POWER 0xb4
