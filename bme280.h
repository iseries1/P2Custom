/**
 * @file bme280.h
 * @brief BME280 sensor library
 * @author Michael Burmeister
 * @date December 14, 2017
 * @version 1.2
 * 
 * @details sample code:
 * 
 * i = BME280_open(BMESCL, BMESDA);<br>
 * BME280_reset();<br>
 * BME280_setHumidity(oversample_1);<br>
 * BME280_setTemp(oversample_1);<br>
 * BME280_setPressure(oversample_1);<br>
 * BME280_setStandbyRate(standby625);<br>
 * BME280_setMode(BME280_normal);<br>
 * while (BME280_getStatus() != 0);<br>
 * BME280_getTempF();<br>
 * 
*/

// #define DODOUBLE

enum
{
  oversample_0,
  oversample_1,
  oversample_2,
  oversample_4,
  oversample_8,
  oversample_16
};
  
enum
{
  BME280_sleep,
  BME280_forced,
  BME280_forced1,
  BME280_normal
};

enum
{
  standby5,
  standby625,
  standby1250,
  standby2500,
  standby5000,
  standby10000,
  standby100,
  standby200
};

enum
{
  filter0,
  filter2,
  filter4,
  filter8,
  filter16
};

/**
 * @brief Open i2c connection to BME280
 * 
 * @param scl I2c clock pin
 * @param sda I2c data pin
 * @return 0x60 or -1 if not found
 */
int BME280_open(int scl, int sda) __fromfile("libBME280/bme280.c");

/**
 * @brief Get BME280 ID (0x60)
 * 
 * @return 0x60
 */
int BME280_getID(void);

/**
 * @brief Do soft reset of BME280
 * 
 */
void BME280_reset(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Get measurement status 
 * 
 * @return status bit 3 = measurement running, bit 0 = copying measurement
 */
int BME280_getStatus(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Forced mode standby rate
 *        .5, 62.5 125, 250, 500, 1000, 100, and 200
 * @param s Standby Item name
 */
void BME280_setStandbyRate(int s) __fromfile("libBME280/bme280.c");

/**
 * @brief Forced mode filter rate
 *        0, 2, 4, 8, 16
 * @param f Filter rate item name
 */
void BME280_setFilterRate(int f) __fromfile("libBME280/bme280.c");

/**
 * @brief Set BME280 Mode of operation
 *        Sleep, Forced, and Normal
 * @param m Mode item name
 */
void BME280_setMode(int m) __fromfile("libBME280/bme280.c");

/**
 * @brief get BME280 Mode of operation
 * 
 * @return Mode value for Sleep, Forced and Normal
 */
int BME280_getMode(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Set pressure measurement sampling
 *        0, 1, 2, 4, 8, 16
 * @param f Frequency Item Name
 */
void BME280_setPressure(int f) __fromfile("libBME280/bme280.c");

/**
 * @brief Set Temperature measurment sampling
 *        0, 1, 2, 4, 8, 16
 * @param f Frequency Item Name
 */
void BME280_setTemp(int f) __fromfile("libBME280/bme280.c");

/**
 * @brief Set Humidity measurement sampling
 *        0, 1, 2, 4, 8, 16
 * @param f Frquency Item Name
 */
void BME280_setHumidity(int f) __fromfile("libBME280/bme280.c");

/**
 * @brief Get Pressure in pascals
 * 
 * @return Pascal value
 */
int BME280_getPressure(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Get Temperature in celius
 * 
 * @return celius temperature
 */
int BME280_getTemp(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Get Humidity in percent times 100
 * 
 * @return Percent humidity time 100
 */
int BME280_getHumidity(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Get Temperature in Fahrenheit
 * 
 * @return Temperature in Fahrenheit time 100
 */
int BME280_getTempF(void) __fromfile("libBME280/bme280.c");

/**
 * @brief Get Pressure in inch of mercury
 * 
 * @return inches of mercury time 100
 */
int BME280_getPressureM(void) __fromfile("libBME280/bme280.c");

#ifdef DODOUBLE

float BME280_getTemperature(void) __fromfile("libBME280/bme280.c");

float BME280_getPressuref(void) __fromfile("libBME280/bme280.c");

float BME280_getHumidityf(void) __fromfile("libBME280/bme280.c");

#endif
