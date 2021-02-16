/**
 * @brief Driver for CH559 USB Host device
 * @author Michael Burmeister
 * @date Feburary 11, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Open Driver port to ch559
 * @param rxpin recieve pin
 * @param txpin transmit pin
 */
 void CH559_Open(int rxpin, int txpin) __fromfile("libch559/ch559.c");

/**
 * @brief Get serial data
 * @param data buffer to receive data in
 * @param size size of buffer
 * @return bytes number of bytes read
 */
int CH559_Recieve(char *data, int size);
