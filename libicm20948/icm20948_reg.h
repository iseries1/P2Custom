/**
 * @file icm20948_reg.h
 * @author Michael Burmeister
 * @brief ICM-20948 9DOF IMU
 * @version 1.0
 * @date January 15, 2023
 */

#define ICM_WHO_AM_I       0x00
#define ICM_USER_CTRL      0x03
#define ICM_LP_CONFIG      0x05
#define ICM_PWR_MGMT_1     0x06
#define ICM_PWR_MGMT_2     0x07
#define ICM_INT_PIN_CFG    0x0f
#define ICM_INT_ENABLE     0x10
#define ICM_INT_ENABLE_1   0x11
#define ICM_INT_ENABLE_2   0x12
#define ICM_INT_ENABLE_3   0x13
#define ICM_I2C_MST_STATUS 0x17
#define ICM_INT_STATUS     0x19
#define ICM_INT_STATUS_1   0x1a
#define ICM_INT_STATUS_2   0x1b
#define ICM_INT_STATUS_3   0x1c
#define ICM_FIFO_PRIORITY  0x26
#define ICM_DELAY_TIME     0x28
#define ICM_ACCEL_XOUT     0x2d
#define ICM_ACCEL_YOUT     0x2f
#define ICM_ACCEL_ZOUT     0x31
#define ICM_GYRO_XOUT      0x33
#define ICM_GYRO_YOUT      0x35
#define ICM_GYRO_ZOUT      0x37
#define ICM_TEMP_OUT       0x39
#define ICM_FIFO_EN_1      0x66
#define ICM_FIFO_EN_2      0x67
#define ICM_FIFO_RST       0x68
#define ICM_FIFO_MODE      0x69
#define ICM_FIFO_COUNT     0x70
#define ICM_FIFO_RW        0x72
#define ICM_DATA_RDY       0x74
#define ICM_HW_FIX         0x75
#define ICM_FIFO_CFG       0x76

#define ICM_MEM_START      0x7C
#define ICM_MEM_RW         0x7D
#define ICM_MEM_BANK       0x7E
#define ICM_BANK_SELECT    0x7F

#define ICM_I2C_MST_ODR    0x00
#define ICM_I2C_MASTER     0x01

#define ICM_GYRO_CONFIG    0x01
#define ICM_ACCEL_CONFIG   0x14
#define ICM_DMP_ADDR       0x50

#define ICM_MAG_ID         0x01
#define ICM_MAG_RSV2       0x03
#define ICM_MAG_STATUS     0x10
#define ICM_MAG_STATUS2    0x18
#define ICM_MAG_XOUT       0x11
#define ICM_MAG_YOUT       0x13
#define ICM_MAG_ZOUT       0x15
#define ICM_MAG_CTRL2      0x31
#define ICM_MAG_CTRL3      0x32
