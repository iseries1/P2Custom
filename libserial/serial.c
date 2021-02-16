
#include <stdlib.h>
#include <stdio.h>
#include <propeller.h>
#include "serial.h"

serial_t *serial_open(int rxpin, int txpin, int baudrate)
{
    int bitperiod = (_clkfreq / baudrate);
    int bit_mode;
    serial_t *x;

    x = malloc(sizeof(int));

    bit_mode = rxpin | (txpin << 8);
    *x = (serial_t)bit_mode;

    // calculate smartpin mode for 8 bits per character
    bit_mode = 7 + (bitperiod << 16);
    
    // set up the transmit pin
    if (txpin >= 0)
      _pinstart(txpin, P_OE | P_ASYNC_TX, bit_mode, 0);

    // set up the receive pin
    if (rxpin >= 0)
      _pinstart(rxpin, P_ASYNC_RX, bit_mode, 0);
   
    return x;
}

void serial_close(serial_t *device)
{
    int i;
    int tx_pin;
    int rx_pin;

    i = (int)*device;
    rx_pin = i & 0xff;
    tx_pin = i >> 8;

    if (tx_pin < 64)
      _pinf(tx_pin);
    if (rx_pin < 64)
      _pinf(rx_pin);

    free(device);

    return;
}

int serial_rxChar(serial_t *device)
{
    int z = 0;
    int rxbyte;
    int rx_pin;

    rx_pin = (int)*device;
    rx_pin = rx_pin & 0xff;

    while (z == 0)
	    z = _pinr(rx_pin);
    
	rxbyte = _rdpin(rx_pin) >> 24; // shift down to byte
	rxbyte = rxbyte & 0xff;

	return rxbyte;
}

int serial_txChar(serial_t *device, int txbyte)
{
    int z = 0;
    int tx_pin;

    tx_pin = (int)*device;
    tx_pin = tx_pin >> 8;

    _wypin(tx_pin, txbyte);

    for (int i=0;i<100;i++)
    {
      z = _pinr(tx_pin);
      if (z != 0)
        return 0;
      usleep(1000);
    }

    return -1;
}
