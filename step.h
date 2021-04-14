/**
 * @file step.h
 * @brief Control Stepper motors
 * @author Michael Burmeister
 * @date November 29, 2020
 * @version 1.0
 * 
*/

/**
 * @brief start step driver
 * @param enable enable pin
 * @param direction direction pin
 * @param step step pin
 * @return driver number
 */
int Step_Start(int enable, int direction, int step) __fromfile("libStep/step.c");

/**
 * @brief step motor in direction
 * @param motor driver number
 * @param steps number of steps needed
 */
void Step_Step(int motor, int steps);

/**
 * @brief wait for motor
 */
void Step_Wait(void);

/**
 * @brief disable motor
 * @param motor driver number
 */
void Step_Disable(int motor);

/**
 * @brief enable motor
 * @param motor driver number
 */
void Step_Enable(int motor);

/**
 * @brief get motor step number
 * @param motor driver number
 * @return steps current step number
 */
int Step_Number(int motor);

/**
 * @brief clear current step count
 * @param motor driver number
 */
void Step_Clear(int motor);
