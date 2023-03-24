/**
 * @file mdd3a.h
 * @brief Test Smart Pin Pulse Output
 * @author Michael Burmeister
 * @date February 22, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initialize MDD3A driver
 * @param m1a
 * @param m1b
 * @param m2a
 * @param m2b
 */
void mdd3a_Init(int m1a, int m1b, int m2a, int m2b) __fromfile("libmdd3a/mdd3a.c");

/**
 * @brief Set motor speed
 * @param pwm1 1000-2000
 * @param pwm2 1000-2000
 *   PWM is 1000 - 2000 1500=stop
 */
void mdd3a_SetPWM(int pwm1, int pwm2);

/**
 * @brief Stop motor driver
 */
void mdd3a_Stop(void);
