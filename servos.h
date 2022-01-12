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
void Servo_Enable(int pin, int position, int refresh) __fromfile("libServos/Servos.c");


/**
 * @brief set servo output value
 * @param pin pin number to change
 * @param position 400-2400 typical
 */
void Servo_Set(int pin, int position);

/**
 * @brief set servo high low values
 * @param high high pulse value
 * @param low low pulse value
 */
void Servo_SetHighLow(int high, int low);

/**
 * @brief set servo angle
 * @param pin pin number to change
 * @param angle angle 0 - 180
 */
void Servo_SetAngle(int pin, int angle);
