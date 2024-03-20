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
 * @brief pin number
 * @return state 1
 */
int DS1822_Init(int pin) __fromfile("libDS1822/ds1822.c");

/**
 * @brief Write
 * @param pin pin number
 * @param state 0 or 1
 */
void DS1822_Write(int state);

/**
 * @brief Read
 * @return state 0 or 1
 */
int DS1822_Read();

/**
 * @brief Write byte
 * @param data byte to write
 */
void DS1822_WriteByte(int data);

/**
 * @brief Read byte
 * @return data byte data
 */
int DS1822_ReadByte(void);

/**
 * @brief Read bytes
 * @param data pointer to data buffer
 * @param len number of bytes returned
 */
void DS1822_ReadBytes(char* data, int len);

/**
 * @brief Get Rom Code
 * @param data pointer to buffer
 */
void DS1822_ReadRom(char* data);

/**
 * @brief Search for device
 * @param data pointer to buffer
 */
int DS1822_SearchRom(char* data);

/**
 * @brief Match device
 * @param data pointer to buffer
 */
void DS1822_MatchRom(char* data);

/**
 * @brief Skip device
 */
void DS1822_SkipRom(void);

/**
 * @brief Alarm Search
 * @param data pointer to buffer
 */
void DS1822_AlarmSearch(char* data);

/**
 * @brief Convert temperature
 */
void DS1822_Convert(void);

/**
 * @brief Write to Scratchpad
 * @param data pointer to buffer
 */
void DS1822_WriteScratchpad(char* data);

/**
 * @brief Read Scratchpad
 * @param data pointer to buffer
 */
void DS1822_ReadScratchpad(char* data);

/**
 * @brief Copy Scratchpad
 */
void DS1822_CopyScratchpad(void);

/**
 * @brief Recall Scratchpad
 */
void DS1822_RecallScratchpad(void);

/**
 * @brief Read Power State
 * @return state
 */
int DS1822_ReadPower(void);

/**
 * @brief CRC
 * @param data point to data
 * @param len length of data
 * @return CRC value
 */
int DS1822_CRC(char* data, int len);

/**
 * @brief Set Resolution
 * @param resolution 9, 10, 11, or 12 bit
 */
void DS1822_SetResolution(int resolution);

/**
 * @brief Convert Temperature times 10
 * @param buf pointer to scratchpad buffer
 * @return temp temperature in celcius
 */
int DS1822_ConvertTemperature(char* buf);
