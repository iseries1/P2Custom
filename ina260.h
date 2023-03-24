/**
 * @file ina260.h
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/


/**
 * @brief open connection to INA260 device
 * @param clk pin number
 * @param data pin number
 * @return id - manufactor id (0x5449)
 */
unsigned short INA260_open(char clk, char data) __fromfile("libina260/ina260.c");
  
/**
 * @brief read current in milliamps
 * @return current
 */
short INA260_getCurrent(void);

/**
 * @brief read voltage in millivolts
 * @return voltage
 */
short INA260_getVoltage(void);

/**
 * @brief read power in milliwatts
 * @return power
 */
short INA260_getPower(void);

/**
 * @brief set mode value
 * @param mode
 * 0 - Shutdown
 * 1 - Current Triggered
 * 2 - Voltage Triggered
 * 3 - Both Triggered
 * 4 - Shutdown
 * 5 - Continues Current
 * 6 - Continues Voltage
 * 7 - Continues Both (default)
*/
void INA260_setMode(int mode);

/**
 * @brief get mode value
 * @return mode 0 - 7
*/
int INA260_getMode(void);

/**
 * @brief config current conversion time
 * @param time value
 * 0 -> 140us
 * 1 -> 204us
 * 2 -> 332us
 * 3 -> 588us
 * 4 -> 1.1ms
 * 5 -> 2.1ms
 * 6 -> 4.1ms
 * 7 -> 8.2ms
 */
void INA260_configCurrent(int time);

/**
 * @brief get current config time
 * @return value 0 - 7
*/
int INA260_getConfigCurrent(void);

/**
 * @brief config voltage conversion time
 * @param time value
 * 0 -> 140us
 * 1 -> 204us
 * 2 -> 332us
 * 3 -> 588us
 * 4 -> 1.1ms
 * 5 -> 2.1ms
 * 6 -> 4.1ms
 * 7 -> 8.2ms
*/
void INA260_configVoltage(int time);

/**
 * @brief get voltage config time
 * @return value 0 - 7
*/
int INA260_getConfigVoltage(void);

/**
 * @brief config averaging
 * @param number of samples
 * 0 -> 1
 * 1 -> 4
 * 2 -> 16
 * 3 -> 64
 * 4 -> 128
 * 5 -> 256
 * 6 -> 512
 * 7 -> 1024
*/
void INA260_configAveraging(int number);

/**
 * @brief get config averaging
 * @return value 0 - 7 values averaged
*/
int INA260_getConfigAveraging(void);

/**
 * @brief mask enable register
 * @param mask values
 * 0 -> Conversion ready
 * 1 -> Power over Limit
 * 2 -> Voltage under limit
 * 3 -> Voltage over limit
 * 4 -> Current under limit
 * 5 -> Current over limit
 */
void INA260_setMask(unsigned short mask);

/**
 * @brief get mask enable value
 * @return mask value
 */
unsigned short INA260_getMask(void);

/**
 * @brief set alert limit value
 * @param alert value
 */
void INA260_setAlert(int alert);

/**
 * @brief get alert limit value
 * @return alert value
*/
int INA260_getAlert(void);

/**
 * @brief reset device to default
 */
void INA260_reset(void);
