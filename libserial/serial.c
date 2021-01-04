
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
    _pinf(txpin);
    _wrpin(txpin, P_OE | P_ASYNC_TX);
    _wxpin(txpin, bit_mode);
    _pinl(txpin); // turn smartpin on by making the pin an output
    
    // set up the receive pin
    _pinf(rxpin);
    _wrpin(rxpin, P_ASYNC_RX);
    _wxpin(rxpin, bit_mode);
    _pinl(rxpin); // turn smartpin on
   
}

void serial_close()
{
    return;
}

int serial_rxChar()
{
    int rxpin = rx_pin;
    int z = 0;
    int rxbyte;
    
    while (z == 0)
	    z = _pinr(rxpin);
    
	rxbyte = _rdpin(rxpin) >> 24; // shift down to byte
	
	return rxbyte;
}

int serial_txChar(int txbyte)
{
    int txpin = tx_pin;
    int z = 0;
    
    _wypin(txpin, txbyte);
    while (z == 0)
    	z = _pinr(txpin);
    
}
