/**
 * @file servo360.h
 * @brief Driver for Servo 360
 * @author Michael Burmeister
 * @date Feburary 20, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Start Servo 360 Processing
 * @param servo transmit pin
 * @param feedback receive pin
 * @return servo number assigned
 */
int Servo360_Start(int servo, int feedback) __fromfile("libservo360/servo360.c");

/**
 * @brief Add Server to the list
 * @param servo transmit pin
 * @param feedback receive pin
 * @return servo number assigned
 */
int Servo360_Add(int servo, int feedback);

/**
 * @brief Remove Servo from the list
 * @brief servo number
 */
void Servo360_Remove(int servo);

/**
 * @brief Get Servo Angle
 * @param servo number
 * @return angle in degrees
 */
int Servo360_Angle(int servo);

/**
 * @brief Set Servo Angle
 * @param servo number
 * @param angle to move servo to
 */
void Servo360_SetAngle(int servo, int angle);

/**
 * @brief Get Servo Turn Count
 * @param servo number
 * @return count number of turns
 */
int Servo360_GetTurns(int servo);

/**
 * @brief Zero Turns
 * @param servo number
 */
void Servo360_ZeroTurns(int servo);

/**
 * @brief Set PWM
 * @param servo number
 * @param pwm value 1000-2000
 */
void Servo360_SetPWM(int servo, int pwm);

/**
 * @brief Get Status
 * @param servo number
 * @return status 0 - not busy
 */
int Servo360_Status(int servo);

/**
 * @brief Enable/Disable Servo
 * @param servo number
 * @param enable 0 - disable, 1 - enable
 */
void Servo360_Enable(int servo, int enable);
