/**
 * @file i2c.h
 * @brief Driver for I2C devices
 * @author Michael Burmeister
 * @date January 21, 2021
 * @version 1.0
 * 
*/

#define I2C_STD 0
#define I2C_FAST 1
#define I2C_FASTP 2
#define I2C_HIGH 3

typedef int* i2c_t;

/**
 * @brief Initilize i2c driver
 * @param scl i2c clock pin
 * @param sda i2c data pin
 * @param driver speed (I2C_STD, I2C_FAST, I2C_FASTP, I2C_HIGH)
 * @return driver connection
 */
i2c_t *I2C_Init(int scl, int sda, int spd) __fromfile("libi2c/i2c.c");

/**
 * @brief Poll i2c device
 * @param x i2c device
 * @param address 7 bit address of device
 * @return status 0 - not found, 1 - found
 */
int I2C_Poll(i2c_t *x, int address);

/**
 * @brief Start i2c transmission
 * @param x i2c device
 */
void I2C_Start(i2c_t *x);

/**
 * @brief Stop i2c transmission
 * @param x i2c device
 */
void I2C_Stop(i2c_t *x);

/**
 * @brief Write byte to device
 * @param x i2c device
 * @param b byte to write
 * @return status 0 - ack, 1 - nak
 */
int I2C_WriteByte(i2c_t *x, int b);

/**
 * @brief Read byte from device
 * @param x i2c device
 * @param ack ack state
 * @return value byte value
 */
int I2C_ReadByte(i2c_t *x, int ack);

/**
 * @brief Write Data to device
 * @param x i2c device
 * @param data pointer to byte values
 * @param count number of bytes to write
 * @return bytes number of bytes returned
 */
int I2C_WriteData(i2c_t *x, char *data, int count);

/**
 * @brief Read Data from device
 * @param x i2c device
 * @param data point to byte values
 * @param count number of bytes to read
 * @return bytes number of bytes read
 */
int I2C_ReadData(i2c_t *x, char *data, int count);

/**
 * @brief I2C In
 * @param x i2c device
 * @param address address of device
 * @param reg register to access
 * @param size register size in bytes
 * @param data pointer to data buffer
 * @param count data bytes to read
 * @return amount read
 */
int I2C_In(i2c_t *x, int address, int reg, int size, char *data, int count);

/**
 * @brief I2C Out
 * @param x i2c device
 * @param address address of device
 * @param reg register to access
 * @param size register size in bytes
 * @param data pointer to data to write
 * @param count data bytes to write
 * @return amount written
 */
int I2C_Out(i2c_t *x, int address, int reg, int size, char *data, int count);
