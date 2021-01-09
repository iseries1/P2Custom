/**
 * @file DS1822.h
 * @brief DS1822 temperature driver
 * @author Michael Burmeister
 * @date December 27, 2020
 * @version 1.0
 * 
*/


/**
 * @brief Initialization
 */
int DS1822_Init(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Write
 * @param pin pin number
 * @param state 0 or 1
 */
void DS1822_Write(int pin, int state) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Read
 * @param pin pin number
 * @return state 0 or 1
 */
int DS1822_Read(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Write byte
 * @param pin pin number
 * @param data byte to write
 */
void DS1822_WriteByte(int pin, int data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Read byte
 * @param pin pin number
 * @return data byte data
 */
int DS1822_ReadByte(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Read bytes
 * @param pin pin number
 * @param data pointer to data buffer
 * @param len number of bytes returned
 */
void DS1822_ReadBytes(int pin, char* data, int len) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Get Rom Code
 * @param pin pin number
 * @param data pointer to buffer
 */
void DS1822_ReadRom(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Search for device
 * @param pin pin number
 * @param data pointer to buffer
 */
int DS1822_SearchRom(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Match device
 * @param pin pin number
 * @param data pointer to buffer
 */
void DS1822_MatchRom(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Skip device
 * @param pin pin number
 */
void DS1822_SkipRom(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Alarm Search
 * @param pin pin number
 * @param data pointer to buffer
 */
void DS1822_AlarmSearch(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Convert temperature
 * @param pin pin number
 */
void DS1822_Convert(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Write to Scratchpad
 * @param pin pin number
 * @param data pointer to buffer
 */
void DS1822_WriteScratchpad(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Read Scratchpad
 * @param pin pin number
 * @param data pointer to buffer
 */
void DS1822_ReadScratchpad(int pin, char* data) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Copy Scratchpad
 * @param pin pin number
 */
void DS1822_CopyScratchpad(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Recall Scratchpad
 * @param pin pin number
 */
void DS1822_RecallScratchpad(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Read Power State
 * @param pin pin number
 * @return state
 */
int DS1822_ReadPower(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief CRC
 * @param data point to data
 * @param len length of data
 * @return CRC value
 */
int DS1822_CRC(char* data, int len) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Set Resolution
 * @param pin pin number
 * @param resolution 9, 10, 11, or 12 bit
 */
void DS1822_SetResolution(int pin, int resolution) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Convert Temperature times 10
 * @param buf pointer to scratchpad buffer
 * @return temp temperature in celcius
 */
int DS1822_ConvertTemperature(char* buf) __fromfile("libDS1822/ds1822.c");
