
#ifndef __SERIAL_H
#define __SERIAL_H

#include "libsimpletext/simpletext.h"


/**
 * @brief Open a simple (half duplex) serial connection.  
 *
 * @param rxpin Serial input pin, receives serial data.
 * 
 * @param txpin Serial output pin, transmits serial data.
 * 
 * @param mode Unused mode field (for FdSerial compatibility)
 * 
 * @param baudrate Bit value transmit rate, 9600, 115200, etc...
 *
 * @returns serial pointer for use as an identifier for serial 
 * and simpletext library functions that have serial or text_t 
 * parameter types.  
 */
void serial_open(int rxpin, int txpin, int mode, int baudrate) __fromfile("libserial/serial.c");

/**
 * @brief Close serial connection.  
 *
 * @param *device Identifier returned by serial_open.
 */
void serial_close(void) __fromfile("libserial/serial.c");

                         
/**
 * @brief Receive a byte.  Waits until next byte is received.
 *
 * @param *device Identifier returned by serial_open.
 *
 * @returns receive byte 0 to 0xff or -1 if none available 
 */
int  serial_rxChar(void)  __fromfile("libserial/serial.c");


/**
 * @brief Send a byte.
 * 
 * @param *device is a previously open/started serial device.
 * 
 * @param txbyte The byte to send.
 * 
 * @returns Byte that was transmitted. 
 */
int  serial_txChar(int txbyte) __fromfile("libserial/serial.c");

#endif
