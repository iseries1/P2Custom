/**
 * @file servos.h
 * @brief Servo library driver
 * @author Michael Burmeister
 * @date January 8, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Enable servo output on pin
 * @param pin pin number to use
 * @param position default position (1500)
 * @param refresh output time 20 miliseconds
 */
void Servo_Enable(int pin, int position, int refresh) __fromfile("libServo/Servos.c");


/**
 * @brief set servo output value
 * @param pin pin number to change
 * @param position 400-2400 typical
 */
void Servo_Set(int pin, int position) __fromfile("libServo/Servos.c");
