/**
 * @file icm20948.h
 * @author Michael Burmeister
 * @brief ICM-20948 9DOF IMU
 * @version 1.0
 * @date January 15, 2023
 */


/**
 * @brief Initialize device driver
 * @param icmclk clock pin
 * @param icmdta data pin
 * @return 0 - found device
 */
int ICM20948_Init(int icmclk, int icmdta) __fromfile("libicm20948/icm20948.c");

/**
 * @brief Set Mode of Operation
 * @param mode 
 * 1 - Sleep
 * 2 - Low Power
 * 3 - Low Noise
 * 4 - Gyro Mode
 * 5 - Mag Mode
 * 6 - Accel & Gyro Mode
 * 7 - Accel & Mag Mode
 * 8 - 9 Axis Mode
 */
void ICM20948_Mode(int mode);

/**
 * @brief Enable DMP
 * @param enable 0 - off, 1 - on
 */
void ICM20948_DMP(int enable);

/**
 * @brief Enable FIFO
 * @param enable 0 - off, 1 - on
 */
void ICM20948_FIFO(int enable);

/**
 * @brief Enable I2C Master
 * @param enable 0 - off, 1 - on
 */
void ICM20948_I2CMaster(int enable);

/**
 * @brief Reset Unit
 */
void ICM20948_Reset(void);

/**
 * @brief Sleep Mode
 * @param mode 0 - Sleep Mode off, 1 - On
 */
void ICM20948_Sleep(int mode);

/**
 * @brief Enable Low Power Mode
 * @param mode 0 - Disable Low Power, 1 - Enable Low Power
 */
void ICM20948_EnableLowPower(int mode);

/**
 * @brief Set Clock Source
 * @param source 0 - 20Mhz, 1-5 Internal, 6 - 20Mhz, 7 - Stop Clock
 */
void ICM20948_SetClock(int source);

/**
 * @brief Interupt Status
 * @return status
 * b0 - Master
 * b1 - DMP
 * b2 - PLL
 * b3 - Motion
 */
int ICM20948_Interupts(void);

/**
 * @brief Set Bypass Mode
 * @param mode 0 - off 1 - on
 */
void ICM20948_ByPass(int mode);

/**
 * @brief Get Delay Time
 * @return delay
 */
int ICM20948_Delay(void);

/**
 * @brief Get Accel Values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 */
void ICM20948_Accel(int *x, int *y, int *z);

/**
 * @brief Get Gyro Values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 */
void ICM20948_Gyro(int *x, int *y, int *z);

/**
 * @brief Get Temperature
 * @return temp in celsius
 */
int ICM20948_Temp(void);

/**
 * @brief Set Hardware Fix
 * @param fix value
 */
void ICM20948_SetHW(int fix);

/**
 * @brief Set FIFO Priority
 * @param priority 
 */
void ICM20948_SetFIFOPriority(int priority);

/**
 * @brief Reset FIFO
 */
void ICM20948_ResetFifo(void);

/**
 * @brief Config Gyro
 * @param filter 0 - 7
 * @param range 0 - 250dps, 1 - 500dps, 2 - 1000dps, 3 - 2000dps
 * @param enable filter
 */
void ICM20948_ConfigGyro(int filter, int range, int enable);

/**
 * @brief Config Accelerometer
 * @param filter 0 - 7
 * @param range 0 - 2g, 1 - 4g, 2 - 8g, 3 - 16g
 * @param enable filter
 */
void ICM20948_ConfigAccel(int filter, int range, int enable);

/**
 * @brief Set DMP Address
 * @param addr - DMP starting address 0x1000
 */
void ICM20948_SetDMPAddress(int addr);

/**
 * @brief I2C Multi-Master Control
 * @param enable 0 - off, 1 - on
 */
void ICM20948_I2CMultiMaster(int enable);

/**
 * @brief I2C Master ODR
 * @param odr 0 - 15 
 * 1.1k/2^(odr)
 */
void ICM20948_I2CMasterODR(int odr);

/**
 * @brief I2C Master Clock Frequency
 * @param freq
 * 0 - 370K
 * 1 - 432k
 * 2 - 345k
 * 3 - 304k
 * 4 - 471k
 */
void ICM20948_I2CMasterClock(int freq);

/**
 * @brief Get Mag Who Am I
 * @return value 0x09
 */
int ICM20948_MagWhoAmI(void);

/**
 * @brief Get Mag values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 * @return status data overflow
 */
int ICM20948_Mag(int *x, int *y, int *z);

/**
 * @brief Get Mag Control
 * @return mode
 * 0 - Power Down
 * 1 - Single Measure
 * 2 - Continuous mode 1
 * 4 - Continuous mode 2
 * 6 - Continuous mode 3
 * 8 - Continuous mode 4
 * 16 - Self Test
 */
int ICM20948_MagCtrl(void);

/**
 * @brief Set Mag Mode
 * @param mode
 * 0 - Power Down
 * 1 - Single Measure
 * 2 - Continuous mode 1
 * 4 - Continuous mode 2
 * 6 - Continuous mode 3
 * 8 - Continuous mode 4
 * 16 - Self Test
 */
void ICM20948_MagMode(int mode);

/**
 * @brief Get Mag Hidden
 * @param x axis
 * @param y axis
 * @param z axis
 * @return status
 */
int ICM20948_MagHidden(short *x, short *y, short *z);

/**
 * @brief Set Memory Bank
 * @param bank 0 - 4
 */
void ICM20948_SetBank(int bank);

/**
 * @brief Write Memory Data
 * @param addr - starting address 0x00 - 0xff
 * @param data - 16 bytes of data
 */
void ICM20948_WriteMemory(short addr, char *data);

/**
 * @brief Read Memory Data
 * @param addr - address to start reading 0x00 - 0xff
 * @param data - array of 16 bytes of data
 */
void ICM20948_ReadMemory(short addr, char *data);

/**
 * @brief Set Memory Bank
 * @param bank 0x00 - 0xff
 */
void ICM20948_SetMemBank(int bank);

/**
 * @brief Setup Slave i2c ports
 * @param slave to configure 0 - 4
 * @param addr i2c address
 * @param in 1 - slave is a read, 0 - slave is a write
 * @param reg register to start with
 * @param read 0 - disabled, 1 - enable reading at sample rate
 * @param swap 0 - disable swap, 1 - swap bytes
 * @param write 0 - don't write register value, 1 - write register
 * @param grp 0 - no group, 1 - grouped
 * @param len 0 to 16 bytes
 * @param data to write to slave 0 to 0xff
 */
void ICM20948_SetSlave(int slave, int addr, int in, int reg, int read, int swap, int write, int grp, int len, int data);

/**
 * @brief Enable DMP
 * @param enable 0 - disable, 1 - enable
 */
void ICM20948_DMPEnable(int enable);
