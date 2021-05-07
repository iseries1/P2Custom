
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
 * @param device file descripter for serial connnection.
 */
int serial_close(FILE *device) __fromfile("libserial/serial.c");

                         
/**
 * @brief Receive a byte.  Waits until next byte is received.
 * @param device file descripter for serial connnection.
 * @returns receive byte 0 to 0xff or -1 if none available 
 */
int  serial_rxChar(FILE *device)  __fromfile("libserial/serial.c");


/**
 * @brief Send a byte.
 * @param device file descripter for serial connection.
 * @param txbyte The byte to send.
 * @returns status 0 if byte was send 
 */
int serial_txChar(FILE *device, char txbyte) __fromfile("libserial/serial.c");

#endif
