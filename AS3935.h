/**
 * @file as3935.h
 * @brief Driver Program for AS3935 Lightning Detector
 * @author Michael Burmeister
 * @date December 23, 2023
 * @version 1.0
 * 
*/


/**
 * @brief Initialize as3935 driver
 * @param cs spi chip select
 * @param clk spi clock
 * @param miso master in slave out
 * @param mosi master out slave in
 * @return state (10) 8 - TRCO run 4 - TRCO failed 2 - SRCO run 1 - SRCO failed
 */
unsigned char AS3935_Init(int cs, int clk, int miso, int mosi) __fromfile("libAS3935/AS3935.c");

/**
 * @brief Set power state
 * @param state 0 - on 1 - low power
 */
void AS3935_SetPower(int state);

/**
 * @brief Read power state
 * @return state 0 - on 1 - low power
 */
unsigned char AS3935_ReadPower(void);

/**
 * @brief Set AFE value default(0)
 * @param value 0 - Indoor 1 - Outdoor
 */
void AS3935_SetAFE(int value);

/**
 * @brief Read AFE state
 * @return state 0 - Indoor 1 - Outdoor
 */
unsigned char AS3935_ReadAFE(void);

/**
 * @brief Set noise floor default(2)
 * @param floor value 0 - 7
 */
void AS3935_SetFloor(int floor);

/**
 * @brief Read noise floor
 * @return value of floor 0 - 7
 */
unsigned char AS3935_ReadFloor(void);

/**
 * @brief Set watchdog default(2)
 * @param value to set 0 - 15
 */
void AS3935_SetWatchdog(int value);

/**
 * @brief Read watchdog
 * @return value 0 - 15
 */
unsigned char AS3935_ReadWatchdog(void);

/**
 * @brief Clear stats
 */
void AS3935_ClearStats(void);

/**
 * @brief Set minimum lightning strikes
 * @param strikes 0 - 3
 */
void AS3935_SetLightning(int strikes);

/**
 * @brief Read minimum lightning strikes value
 * @return value 0 - 3
 */
unsigned char AS3935_ReadLightning(void);

/**
 * @brief Set spike rejection default(2)
 * @param value 0 - 15
 */
void AS3935_SetSpikeRejection(int value);

/**
 * @brief Read lightning rejection value
 * @return value 0 - 15
 */
unsigned char AS3935_ReadSpikeRejection(void);

/**
 * @brief Set LCO divider
 * @param divider 0 - 3
 */
void AS3935_SetLCODivder(int divider);

/**
 * @brief Read LCO divider
 * @return divider 0 - 3
 */
unsigned char AS3935_ReadLCODivider(void);

/**
 * @brief Read interrupt state
 * @return state 1 - Noise, 4 - Disturber, 8 - Lightning
 */
unsigned char AS3935_ReadInterrupt(void);

/**
 * @brief Read lightning energy value
 * @return value 0 - 32767
 */
unsigned long AS3935_ReadLightingEnergy(void);

/**
 * @brief Read distance of storm
 * @return distance 
 */
unsigned char AS3935_ReadDistance(void);

/**
 * @brief Set IRQ bits
 * @param value 1 - TRCO, 2 - SRCO, 4 - LCO
 */
void AS3935_SetIRQ(int value);

/**
 * @brief Read IRQ bits
 * @return state 1 - TRCO, 2 - SRCO, 4 - LCO
 */
unsigned char AS3935_ReadIRQ(void);

/**
 * @brief Set capacitance value
 * @param value 0 - 15 in 8 pico farade steps
 */
void AS3935_SetCapacitance(int value);

/**
 * @brief Read capacitance value
 * @return value 0 - 15 in 8 pico farades
 */
unsigned char AS3935_ReadCapacitance(void);

/**
 * @brief Read calibration state
 * @return state 8 - TRCO Done, 4 - TRCO failed, 2 - SRCO Done, 1 - SRCO failed
 */
unsigned char AS3935_ReadCalibration(void);

/**
 * @brief Run Calibration
 * @return status 8 - TRCO Done, 4 - TRCO failed, 2 - SRCO Done, 1 - SRCO failed
 */
unsigned char AS3935_Calibrate(void);

/**
 * @brief Set default values
 */
void AS3935_SetDefault(void);
