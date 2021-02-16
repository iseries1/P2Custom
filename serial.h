
#ifndef __SERIAL_H
#define __SERIAL_H


typedef int* serial_t;

/**
 * @file serial.h
 * @brief Open a serial connection.
 * @param rxpin Serial input pin, receives serial data.
 * @param txpin Serial output pin, transmits serial data.
 * @param baudrate Bit value transmit rate, 9600, 115200, etc...
 * @returns id Serial connnection id
 */
serial_t *serial_open(int rxpin, int txpin, int baudrate) __fromfile("libserial/serial.c");

/**
 * @brief Close serial connection.  
 * @param device Serial connection id.
 */
void serial_close(serial_t *device) __fromfile("libserial/serial.c");

                         
/**
 * @brief Receive a byte.  Waits until next byte is received.
 * @param device Identifier returned by serial_open.
 * @returns receive byte 0 to 0xff or -1 if none available 
 */
int  serial_rxChar(serial_t *device)  __fromfile("libserial/serial.c");


/**
 * @brief Send a byte.
 * @param device is a previously open/started serial device.
 * @param txbyte The byte to send.
 * @returns status 0 if byte was send 
 */
int serial_txChar(serial_t *device, char txbyte) __fromfile("libserial/serial.c");

#endif
