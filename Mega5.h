/**
 * @file Mega5.h
 * @brief Arducam Mega 5MP camera driver
 * @author Michael Burmeister
 * @date May 2, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initialize Arducam Camera
 * @param clk clock pin for SPI
 * @param miso Data in pin
 * @param mosi Data out pin
 * @param cs chip select
 * @return handle
 */
int Mega5_Init(int clk, int miso, int mosi, int cs) __fromfile("libMega5/Mega5.c");

