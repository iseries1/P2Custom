/**
 * @brief Drive LCD1602 Display
 * @author Michael Burmeister
 * @date Michael Burmeister
 * @version 1.0
 * 
*/

#define LCD1602_ADDRESS 0x4e
#define LCD1602_CLEAR 0x01
#define LCD1602_HOME 0x02
#define LCD1602_ENTRY 0x04
#define LCD1602_DISPLAY 0x08
#define LCD1602_SHIFT 0x10
#define LCD1602_FUNCTION 0x20
#define LCD1602_CGADDRESS 0x40
#define LCD1602_DDADDRESS 0x80

/**
 * Expander values
 */
#define LCD1602_ENABLE 0x04
#define LCD1602_BACKLIGHT 0x08
#define LCD1602_RW 0x02
#define LCD1602_RS 0x01
