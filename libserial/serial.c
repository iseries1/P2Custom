
#include "simpletools.h"
#include "serial.h"

int rx_pin;
int tx_pin;

void serial_open(int rxpin, int txpin, int mode, int baudrate)
{
    int bitperiod = (_clkfreq / baudrate);
    int bit_mode;
    
    rx_pin = rxpin;
    tx_pin = txpin;
    
    // calculate smartpin mode for 8 bits per character
    bit_mode = 7 + (bitperiod << 16);
    
    // set up the transmit pin
    if (txpin >= 0)
      _pinstart(txpin, P_OE | P_ASYNC_TX, bit_mode, 0);

    // set up the receive pin
    if (rxpin >= 0)
      _pinstart(rxpin, P_ASYNC_RX, bit_mode, 0);
   
}

void serial_close()
{
    if (tx_pin >= 0)
      _pinf(tx_pin);
    if (rx_pin >= 0)
      _pinf(rx_pin);
    return;
}

int serial_rxChar()
{
    int z = 0;
    int rxbyte;
    
    while (z == 0)
	    z = _pinr(rx_pin);
    
	rxbyte = _rdpin(rx_pin) >> 24; // shift down to byte
	
	return rxbyte;
}

int serial_txChar(int txbyte)
{
    int z = 0;
    
    _wypin(tx_pin, txbyte);
    while (z == 0)
    	z = _pinr(tx_pin);
}
