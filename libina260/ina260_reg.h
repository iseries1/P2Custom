/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/

#define INA260_I2CADDR 0x40
#define INA260_CONFIG  0x00
#define INA260_CURRENT 0x01
#define INA260_VOLTAGE 0x02
#define INA260_POWER   0x03
#define INA260_ALERTEN 0x04
#define INA260_ALERTV  0x05
#define INA260_MFGID   0xFE
#define INA260_DIEID   0xFF
