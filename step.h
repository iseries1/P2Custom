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
void Step_Step(int motor, int steps) __fromfile("libStep/step.c");

/**
 * @brief wait for motor
 */
void Step_Wait(void) __fromfile("libStep/step.c");

/**
 * @brief disable motor
 */
void Step_Disable(void) __fromfile("libStep/step.c");
