/**
 * @file Sbus.h
 * @brief Decode SBUS serial data from X8R receiver
 * @author Michael Burmeister
 * @date March 10, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Open port to SBUS receiver
 * @param pin sbus receiver pin
 */
void Sbus_Open(int pin) __fromfile("libSbus/Sbus.c");

/**
 * @brief Get Raw Channel value
 * @param channel number 1 to 16
 * @return value raw channel pwm
 */
uint16_t Sbus_GetChannel(int channel);

/**
 * @brief Get Adjusted Channel value
 * @param channel number 1 to 16
 * @return value adjust channel pwm
 */
uint16_t Sbus_GetAdjust(int channel);

/**
 * @brief Get Scaled Channel value
 * @param channel number 1 to 16
 * @return value scaled channel pwm
 */
uint16_t Sbus_GetScaled(int channel);

/**
 * @brief Set Scaled Channel values
 * @param channel number 1 to 16
 * @param cmin channel pwm
 * @param cmax channel pwm
 */
void Sbus_SetScaled(int channel, uint16_t cmin, uint16_t cmax);

/**
 * @brief Get Failsafe
 * @return failsafe 0 - off 
 */
int Sbus_GetFailsafe(void);
