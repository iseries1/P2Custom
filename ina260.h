/**
 * @file ina260.h
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

enum _mode {
  INA260_SHUTDOWN,
  INA260_CURRENT_TRIGGERED,
  INA260_VOLTAGE_TRIGGERED,
  INA260_BOTH_TRIGGERED,
  INA260_POWERDOWN,
  INA260_CURRENT_CONTINOUS,
  INA260_VOLTAGE_CONTINOUS,
  INA260_BOTH_CONTINUOUS
}; // INA260_MODES;

// in microseconds
enum _conversion {
  INA260_140,
  INA260_204,
  INA260_332,
  INA260_588,
  INA260_1100,
  INA260_2116,
  INA260_4156,
  INA260_8244
}; // INA260_CONVERSION;  

// average items
enum _average {
  INA260_AVG1,
  INA260_AVG4,
  INA260_AVG16,
  INA260_AVG128,
  INA260_AVG256,
  INA260_AVG512,
  INA260_AVG1024
}; // INA260_AVERAGE;

// Mask/Enable
enum _maskenable {
  INA260_OVERCURRENTLIMT = 1 << 15,
  INA260_UNDERCURRENTLIMT = 1 << 14,
  INA260_OVERVOLTAGE = 1 << 13,
  INA260_UNDERVOLTAGE = 1 << 12,
  INA260_OVERPOWER = 1 << 11,
  INA260_CONVERSIONREADY = 1 << 10,
  INA260_LATCHMODE = 1
}; // INA260_MASKENABLE;
  
/**
 * @brief open connection to INA260 device
 * @param clock pin number
 * @param data pin number
 * @return id manufactor id
 */
unsigned short INA260_open(char clock, char data) __fromfile("libina260/ina260.c");
  
/**
 * @brief read current in milliamps
 * @return current
 */
short INA260_getCurrent(void) __fromfile("libina260/ina260.c");

/**
 * @brief read voltage in hundredths
 * @return voltage
 */
short INA260_getVoltage(void) __fromfile("libina260/ina260.c");

/**
 * @brief read power in milliwatts
 * @return power
 */
short INA260_getPower(void) __fromfile("libina260/ina260.c");

/**
 * @brief config device
 * @param mode of operation
 * @param current conversion
 * @param voltage conversion
 * @param average amount
 * @param reset device
 */
void  INA260_setConfig(char mode, char current, char voltage, char average, char reset) __fromfile("libina260/ina260.c");

/**
 * @brief read device configuration
 * @return config
 */
unsigned short INA260_getConfig(void) __fromfile("libina260/ina260.c");

/**
 * @brief mask enable register
 * @param mask value
 */
void INA260_setMask(unsigned short mask) __fromfile("libina260/ina260.c");

/**
 * @brief get mask enable value
 * @return mask value
 */
unsigned short INA260_getMask(void) __fromfile("libina260/ina260.c");

/**
 * @brief set alert limit value
 * @param alert value
 */
void INA260_setAlert(unsigned short alert) __fromfile("libina260/ina260.c");
