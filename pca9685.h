/**
 * @brief Driver Library for PCA9685 LED/Servo driver
 * @author Michael Burmeister
 * @date November 14, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Open connection to LED/Servo driver
 * @param CLK clock pin used
 * @param DTA data pin used
 */
void PCA9685_open(int CLK, int DTA) __fromfile("libPCA9685/pca9685.c");

/**
 * @brief Reset LED/Servo driver
 */
void PCA9685_reset();

/**
 * @brief Read mode register
 * @param mode mode1 or mode2 register
 * @return mode value
 */
unsigned char PCA9685_readMode(int mode);

/**
 * @brief Get Prescaler value
 * @return prescale value
 */
unsigned char PCA9685_getPrescaler(void);

/**
 * @brief Set Prescaler value
 * @param prescale value
 */
void PCA9685_setPrescaler(unsigned char prescale);

/**
 * @brief Get PWM value
 * @param LED Pin number 0 - 15
 * @return value PWM value
 */
int PCA9685_getPWM(unsigned char LED);

/**
 * @brief Set PWM value
 * @param LED pin number 0 - 15
 * @param value PWM value
 */
void PCA9685_setPWM(unsigned char LED, int value);

/**
 * @brief Set PWM all LED's
 * @param value PWM value
 */
void PCA9685_setAllPWM(int value);
