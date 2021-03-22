/**
 * @file Stepper.h
 * @brief Drive Stepper Motors 
 * @author Michael Burmeister
 * @date March 11, 2021
 * @version 1.0
 * 
*/


/**
 * @brief Start Stepper Motor driver
 * @param enable pin number
 * @param direction pin number
 * @param step pin number
 * @return motor driver
 */
int Stepper_Start(int enable, int direction, int step) __fromfile("libStepper/stepper.c");

/**
 * @brief Enable Stepper Motor
 * @param motor driver
 * @param enable 0 - disable, 1 - enable
 */
void Stepper_Enable(int motor, int enable);

/**
 * @brief Set Stepper Motor direction
 * @param motor driver
 * @param direction 0 - clockwise, 1 - counter clockwise
 */
void Stepper_Direction(int motor, int direction);

/**
 * @brief Set Stepper Speed
 * @param motor driver
 * @param speed in 10msec increments
 */
void Stepper_Speed(int motor, int speed);
