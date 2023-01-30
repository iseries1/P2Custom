/**
 * @file ens160.h
 * @author Michael Burmeister
 * @brief  ENS160 Air Quality Sensor
 * @version 1.0
 * @date January 13, 2023
 */


/**
 * @brief Initialize ENS160 device
 * @param enclk i2c clock pin
 * @param endta i2c data pin
 * @return 0 - device found -1 - not found
 */
int ENS160_Init(int enclk, int endta) __fromfile("libens160/ens160.c");

/**
 * @brief Get device status
 * @return status register 
 */
int ENS160_Status(void);

/**
 * @brief Set Temperature in Kelvin
 * @param temp in Celsius
 */
void ENS160_SetTemperature(int temp);

/**
 * @brief Get Temperature in Kelvin
 * @return temp - temperature value in Celsius
 */
int ENS160_GetTemperature(void);

/**
 * @brief Set Relative Humidity Percent
 * @param humidity
 */
void ENS160_SetHumidity(int humidity);

/**
 * @brief Get Relative Humidity Percent
 * @return humidity Percent
 */
int ENS160_GetHumidity(void);

/**
 * @brief Set Operating Mode
 * @param mode - 0->Deep sleep 1->Idle 2->Standard 3->Reset 
 */
void ENS160_SetMode(int mode);

/**
 * @brief Get Operating Mode
 * @return mode - 0-Sleep, 1-Idle, 2-Standard
 */
int ENS160_GetMode(void);

/**
 * @brief Get AQI value
 * @return aqi - 0 - 300+ 
 * 1 - (0 - 50) Good
 * 2 - (51 - 100) Moderate
 * 3 - (101 - 150) Unhealthy
 * 4 - (151 - 200) Unhealthy
 * 5 - (201 - 300) Very Unhealthy
 */
int ENS160_GetAQI(void);

/**
 * @brief Get Total Volative Compounds in ppb
 * @return tvoc
 */
int ENS160_GetTVOC(void);

/**
 * @brief Get CO2 gas in ppm
 * @return CO2
 */
int ENS160_GetCO2(void);

/**
 * @brief Get Ethanol consentration in ppb
 * @return ethanol
 */
int ENS160_GetETOH(void);

/**
 * @brief Read Write Register Values
 * @return register pointer
 */
char *ENS160_GetWrite(void);

/**
 * @brief Write Write Register Values
 * @param values arraw of 8 values
 */
void ENS160_SetWrite(char *values);

/**
 * @brief Get Read Registers
 * @return register pointer
 */
char *ENS160_GetRead(void);

/**
 * @brief Get Raw Resistance
 * @param r1 pointer of raw 1 value unsigned
 * @param r2 pointer of raw 2 value unsigned
 * @return status 0 - ok, 1 - no data
 * logarthmic value returned
 */
short ENS160_Raw(short &r1, short &r2);

