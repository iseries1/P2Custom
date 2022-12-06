
#ifndef __SERIAL_H
#define __SERIAL_H


/**
 * @file serial.h
 * @brief Open a serial connection.
 * @param rxpin Serial input pin, receives serial data.
 * @param txpin Serial output pin, transmits serial data.
 * @param baudrate Bit value transmit rate, 9600, 115200, etc...
 * @returns FILE a pointer to file discripter
 */
FILE *serial_open(int rxpin, int txpin, int baudrate) __fromfile("libserial/serial.c");

/**
 * @brief Close serial connection.  
 * @param device file descriptor for serial connnection.
 */
int serial_close(FILE *device) __fromfile("libserial/serial.c");

/**
 * @brief Check if a character is available and return it
 * @param device file descriptor for serial connection.
 * @return serial byte -1 if no character is available
 */
int serial_rxCheck(FILE *device);

/**
 * @brief Check if a byte is available to be read
 * @param device file descriptor for serial connection.
 * @return status none zero if a byte is available
 */
int serial_rxReady(FILE *device);

/**
 * @brief Receive a byte.  Waits until next byte is received.
 * @param device file descriptor for serial connnection.
 * @return receive byte 0 to 0xff or -1 if none available 
 */
int serial_rxChar(FILE *device);

/**
 * @brief Send a byte.
 * @param device file descriptor for serial connection.
 * @param txbyte The byte to send.
 * @return status 0 if byte was send 
 */
int serial_txChar(FILE *device, char txbyte);

/**
 * @brief Put file character
 * @param c byte to send
 * @param device FILE descriptor for serial connection
 * @return status 0 if byte was sent
 */
int serial_putcf(int c, FILE *device);

/**
 * @brief Get file character
 * @param device file descriptor for serial connection
 * @return character received
 */
int serial_getcf(FILE *device);

/**
 * @brief Read number of bytes from device
 * @param device file descriptor for serial connection
 * @param buffer to hold results
 * @param count number of bytes to read
 * @return size number of bytes read
 */
ssize_t serial_read(FILE *device, void *buff, size_t count);

/**
 * @brief Write number of bytes to device
 * @param device file descriptor for serial connection
 * @param buffer of data to write
 * @param count of data to write from buffer
 * @return size of data written to device
 */
ssize_t serial_write(FILE *device, const void *buff, size_t count);

#endif
