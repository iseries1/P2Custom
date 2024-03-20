/**
 * @brief Driver for AS3935 Lightning Detector 
 * @author Michael Burmeister
 * @date December 23, 2023
 * @version 1.0
 * 
 */


#define AS3935_AFE_GB 0x00
#define AS3935_NOISE 0x01
#define AS3935_STATS 0x02
#define AS3935_MASK 0x03
#define AS3935_LIGHTNINGL 0x04
#define AS3935_LIGHTNINGH 0x05
#define AS3935_ENERGY 0x06
#define AS3935_DISTANCE 0x07
#define AS3935_TUNE 0x08
#define AS3935_TRCO 0x3A
#define AS3935_SRCO 0x3B
#define AS3935_DEFAULTS 0x3C
#define AS3935_CALIBRATE 0x3D
#define AS3935_COMMAND 0x96
