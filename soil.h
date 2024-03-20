/**
 * @file soil.h
 * @brief Sparkfun Soil Moisture Sensor
 * @author Michael Burmeister
 * @date May 24, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initialize Soil Connection
 * @param clk pin
 * @param dta pin
 * @return int 
 */
int soil_Init(int clk, int dta) __fromfile("libsoil/soil.c");

/**
 * @brief Turn LED On/Off
 * @param state 0 - off, 1 - on
 */
void soil_Led(int state);

/**
 * @brief Get Moisture Value
 * @return value of sensor
 */
int soil_Value(void);
