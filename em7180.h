/**
 * @file em7180.h
 * @brief Library for EM7180 sensor fusion
 * @author Michael Burmeister
 * @date January 25, 2019
 * @version 1.0
 * 
*/

/**
 * @brief open connection to EM7180 device
 * @param CLK i2c clock pin
 * @param SDA i2c data pin
 * @return em7180 value
 */
int Em7180_open(int CLK, int SDA) __fromfile("libem7180/em7180.c");

/**
 * @brief get em7180 status
 * @return status
 */
int Em7180_status(void);

/**
 * @brief get error status
 * @return error
 */
char Em7180_error(void);

/**
 * @brief get software version
 * @return version
 */
short Em7180_version(void);

/**
 * @brief get product ID
 * @return ID
 */
short Em7180_productID(void);

/**
 * @brief get sensors
 * @return ID
 */
char Em7180_sensors(void);

/**
 * @brief reset
 * @param type
 */
void Em7180_reset(char type);

/**
 * @brief load firmware in EM7180
 */
void Em7180_loadfw(void);

/**
 * @brief setup with default settings
 */
void Em7180_setupdefault(void);

/**
 * @brief setup sensors
 * @param accBW
 * @param gyroBW
 * @param accFS
 * @param gyroFS
 * @param magFS
 * @param QRtDiv
 * @param magRT
 * @param accRT
 * @param gyroRT
 * @param baroRT
 */
void Em7180_setup(char accBW, char gyroBW, short accFS, short gyroFS, short magFS, char QRtDiv, char magRT, char accRT, char gyroRT, char baroRT);

/**
 * @brief set gyro full scale
 * @param fs gyro offset
 */
void Em7180_setgyrofs(short fs);

/**
 * @brief set mag and accelerometer
 * @param mag
 * @param acc
 */
void Em7180_setmagaccfs(short mag, short acc);

/**
 * @brief set integer parameter
 * @param parameter
 * @param value
 */
void Em7180_setintparam(char parameter, int value);

/**
 * @brief set float parameter
 * @param parameter
 * @param value
 */
void Em7180_setfloatparam(char parameter, float value);

/**
 * @brief long to float
 * @param value
 * @return float value
 */
float Em7180_float(long value);

/**
 * @brief float to long
 * @param value
 * @return long value
 */
long Em7180_long(float value);

/**
 * @brief read Quaterion values
 * @param *Qs
 */
void Em7180_readquaternions(float *Qs);

/**
 * @brief read accelerometer values
 * @param *acc
 */
void Em7180_readaccelerometer(short *acc);

/**
 * @brief read gyro values
 * @param *gyro
 */
void Em7180_readgyro(short *gyro);

/**
 * @brief read magnetometer values
 * @param *mag
 */
void Em7180_readmagnetometer(short *mag);

/**
 * @brief read barometer value
 * @return value
 */
short Em7180_readbarometer(void);

/**
 * @brief read temperature value
 * @return temperature
 */
short Em7180_readtemperature(void);

/**
 * @brief Put SENtral in passthrou mode
 */
void Em7180_setPassThroughMode(void);
