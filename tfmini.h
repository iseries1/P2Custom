/**
 * @file tfmini.h
 * @brief TFmini LiDAR Driver
 * @author Michael Burmeister
 * @date May 7, 2020
 * @version 1.0
 * 
*/

/**
 * @brief open connection to device
 * @param Rx receive data pin
 * @param Tx transmit data pin
 * @return status
 */
int tfmini_open(int Rx, int Tx) __fromfile("libtfmini/tfmini.c");

/**
 * @brief get distance measurement
 * @return distance in centimeters
 */
int tfmini_distance(void);

/**
 * @brief get strength of measurement
 * @return strength in 
 */
int tfmini_strength(void);

/**
 * @brief get temperature of unit
 * @return temperature
 */
int tfmini_temperature(void);

/**
 * @brief set measurement units
 * @param units 1-cm, 2-mm
 */
void tfmini_setUnits(int units);

/**
 * @brief set update rate
 * @param rate 1 - 1000 Hz
 */
void tfmini_setRate(short rate);
