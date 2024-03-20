/**
 * @file wioe5.h
 * @brief Driver for Wio E5 LoraWan Device
 * @author Michael Burmeister
 * @date February 11, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initialize Wio E5 Driver
 * @param rx receive pin
 * @param tx transmit pin
 * @return status 0 - ok, -1 not found
 */
int WIOE5_Init(int rx, int tx) __fromfile("libwioe5/wioe5.c");

/**
 * @brief Get Version Number
 * @return version
 */
int WIOE5_GetVer(void);

/**
 * @brief Get Device ID
 * @return address device address
 */
int WIOE5_GetID(void);

/**
 * @brief Send Request
 * @param request
 * @param returned number of lines 
 * @return length of request
 */
int WIOE5_Request(char *request);

/**
 * @brief Get Results
 * @param buffer to hold data
 * @return length of data
 */
int WIOE5_Results(char *buffer);

/**
 * @brief Reset
*/
void WIOE5_Reset(void);

/**
 * @brief Set LoraWan Mode
 * @param mode 0 - LWABP, 1 - LWOTAA, 2 - TEST
 * @return mode
*/
int WIOE5_SetMode(int mode);

/**
 * @brief Set Class
 * @param class 0 - A, 1 - B, 2 - C
*/
void WIOE5_SetClass(int class);

/**
 * @brief Join Network
 * @return status 0 - joined, -1 - not joined
*/
int WIOE5_Join(void);

/**
 * @brief Send Message
 * @param message data
 * @return status 1 - ok, 2 - data
*/
int WIOE5_Send(char *message);

/**
 * @brief Send Confirmed Message
 * @param message data
 * @return status 1 - ok, 2 - data, -1 - failed
*/
int WIOE5_SendConfirmed(char *message);

/**
 * @brief Send Hex Message
 * @param message hex data
 * @return status 1 - ok, 2 - data, -1 - failed
*/
int WIOE5_SendHex(char *message);

/**
 * @brief Send Confirmed Hex Message
 * @param message hex data
 * @return status 1 - ok, 2 - data, -1 - failed
*/
int WIOE5_SendConfirmedHex(char *message);

/**
 * @brief Set Port number to use
 * @param port number 1 - 255
*/
void WIOE5_SetPort(int port);

/**
 * @brief Set Data Rate
 * @param rate value
*/
void WIOE5_SetDataRate(int rate);

/**
 * @brief Set Lora Mode Point to Point
 * @param mode 0 - US
 * @param freq frequency to use
 * @param sf spreading factor
 */
void WIOE5_SetLora(int mode, int freq, int sf);

/**
 * @brief Send Lora Data
 * @param data Hex Data to send
 */
void WIOE5_SendLora(char *data);

/**
 * @brief Receive Lora Data
 * @param data buffer to hold data
 * @return data length
 */
int WIOE5_GetLora(char *data);

/**
 * @brief Set Low Power
 * @param mode 0 - lowpower, 1 - lowpower Auto, 2 - lowpower auto off, 3 - wake, #ms - Milliseconds in
 */
void WIOE5_SetLowPower(int mode);

/**
 * @brief Set EEPROM Memory
 * @param address 0 - 255
 * @param value 0 - 255
 */
void WIOE5_SetMemory(char address, char value);

/**
 * @brief Get EEPROM Memory
 * @param address 0 - 255
 * @return value 
 */
char WIOE5_GetMemory(char address);

/**
 * @brief Get Return Data
 * @return data pointer in hex
 */
char *WIOE5_GetData(void);
