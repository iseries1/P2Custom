/**
 * @brief Test Smart Pin Pulse Output
 * @author Michael Burmeister
 * @date February 22, 2023
 * @version 1.0
 * 
*/

#define ARDUCHIP_FRAMES     0x01
#define ARDUCHIP_TEST1      0x00 // TEST register
#define ARDUCHIP_FIFO       0x04 // FIFO and I2C control
#define ARDUCHIP_FIFO_2     0x07 // FIFO and I2C control
#define FIFO_CLEAR_ID_MASK  0x01
#define FIFO_START_MASK     0x02

#define FIFO_RDPTR_RST_MASK 0x10
#define FIFO_WRPTR_RST_MASK 0x20
#define FIFO_CLEAR_MASK     0x80

#define ARDUCHIP_TRIG       0x44 // Trigger source
#define VSYNC_MASK          0x01
#define SHUTTER_MASK        0x02
#define CAP_DONE_MASK       0x04

#define FIFO_SIZE1          0x45 // Camera write FIFO size[7:0] for burst to read
#define FIFO_SIZE2          0x46 // Camera write FIFO size[15:8]
#define FIFO_SIZE3          0x47 // Camera write FIFO size[18:16]

#define BURST_FIFO_READ     0x3C // Burst FIFO read operation
#define SINGLE_FIFO_READ    0x3D // Single FIFO read operation

#define CAPRURE_MAX_NUM                            0xff

#define CAM_REG_POWER_CONTROL                      0X02
#define CAM_REG_SENSOR_RESET                       0X07
#define CAM_REG_FORMAT                             0X20
#define CAM_REG_CAPTURE_RESOLUTION                 0X21
#define CAM_REG_BRIGHTNESS_CONTROL                 0X22
#define CAM_REG_CONTRAST_CONTROL                   0X23
#define CAM_REG_SATURATION_CONTROL                 0X24
#define CAM_REG_EV_CONTROL                         0X25
#define CAM_REG_WHILEBALANCE_MODE_CONTROL          0X26
#define CAM_REG_COLOR_EFFECT_CONTROL               0X27
#define CAM_REG_SHARPNESS_CONTROL                  0X28
#define CAM_REG_AUTO_FOCUS_CONTROL                 0X29
#define CAM_REG_IMAGE_QUALITY                      0x2A
#define CAM_REG_EXPOSURE_GAIN_WHILEBALANCE_CONTROL 0X30
#define CAM_REG_MANUAL_GAIN_BIT_9_8                0X31
#define CAM_REG_MANUAL_GAIN_BIT_7_0                0X32
#define CAM_REG_MANUAL_EXPOSURE_BIT_19_16          0X33
#define CAM_REG_MANUAL_EXPOSURE_BIT_15_8           0X34
#define CAM_REG_MANUAL_EXPOSURE_BIT_7_0            0X35
#define CAM_REG_BURST_FIFO_READ_OPERATION          0X3C
#define CAM_REG_SINGLE_FIFO_READ_OPERATION         0X3D
#define CAM_REG_SENSOR_ID                          0x40
#define CAM_REG_YEAR_ID                            0x41
#define CAM_REG_MONTH_ID                           0x42
#define CAM_REG_DAY_ID                             0x43
#define CAM_REG_SENSOR_STATE                       0x44
#define CAM_REG_FPGA_VERSION_NUMBER                0x49
#define CAM_REG_DEBUG_DEVICE_ADDRESS               0X0A
#define CAM_REG_DEBUG_REGISTER_HIGH                0X0B
#define CAM_REG_DEBUG_REGISTER_LOW                 0X0C
#define CAM_REG_DEBUG_REGISTER_VALUE               0X0D

#define CAM_REG_SENSOR_STATE_IDLE                  (1 << 1)
#define CAM_SENSOR_RESET_ENABLE                    (1 << 6)
#define CAM_FORMAT_BASICS                          (0 << 0)
#define CAM_SET_CAPTURE_MODE                       (0 << 7)
#define CAM_SET_VIDEO_MODE                         (1 << 7)

#define SET_WHILEBALANCE                           0X02
#define SET_EXPOSURE                               0X01
#define SET_GAIN                                   0X00

#define CAMERA_TYPE_NUMBER                         2

#define RESOLUTION_160X120                         (1 << 0)
#define RESOLUTION_320X240                         (1 << 1)
#define RESOLUTION_640X480                         (1 << 2)
#define RESOLUTION_800X600                         (1 << 3)
#define RESOLUTION_1280X720                        (1 << 4)
#define RESOLUTION_1280X960                        (1 << 5)
#define RESOLUTION_1600X1200                       (1 << 6)
#define RESOLUTION_1920X1080                       (1 << 7)
#define RESOLUTION_2048X1536                       (1 << 8)
#define RESOLUTION_2592X1944                       (1 << 9)
#define RESOLUTION_320x320                         (1 << 10)
#define RESOLUTION_128x128                         (1 << 11)
#define RESOLUTION_96x96                           (1 << 12)

#define SPECIAL_NORMAL                             (0 << 0)
#define SPECIAL_BLUEISH                            (1 << 0)
#define SPECIAL_REDISH                             (1 << 1)
#define SPECIAL_BW                                 (1 << 2)
#define SPECIAL_SEPIA                              (1 << 3)
#define SPECIAL_NEGATIVE                           (1 << 4)
#define SPECIAL_GREENISH                           (1 << 5)
#define SPECIAL_OVEREXPOSURE                       (1 << 6)
#define SPECIAL_SOLARIZE                           (1 << 7)
#define SPECIAL_YELLOWISH                          (1 << 8)
