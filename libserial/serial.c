
#include <sys/vfs.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <propeller.h>
#include <smartpins.h>
#include "serial.h"

void SFDuplex(void *);

unsigned long SFDStack[200];
unsigned char _RBuff[128];
unsigned char _TBuff[128];
volatile int _RHead, _RTail;
volatile int _THead, _TTail;
volatile char _FDON = 0;


FILE *serial_open(int rxpin, int txpin, int baudrate)
{
    int i;
    int bitperiod = (_clkfreq / baudrate);
    int bit_mode;
    FILE *fd;
    struct _default_buffer *b = 0;

    for (i=3;i<_MAX_FILES;i++)
      if ((fd = __getftab(i))->state == 0)
        break;
    if (i == _MAX_FILES)
      return _seterror(EMFILE);
    
    fd->vfsdata = b;

    fd->flags = O_RDWR;
    fd->read = &serial_read;
    fd->write = &serial_write;
    fd->putcf = &serial_putcf;
    fd->getcf = &serial_getcf;
    fd->close = &serial_close;
    fd->ioctl = 0;
    fd->flush = 0;
    fd->lseek = 0;

    i = (rxpin & 0xff);
    bit_mode = i | ((txpin & 0xff) << 8); // Save the pin config here
    fd->state = (bit_mode << 16) | _VFS_STATE_INUSE | _VFS_STATE_WROK;

    // calculate smartpin mode for 8 bits per character
    bit_mode = 7 + (bitperiod << 16);
    
    // set up the transmit pin
    if (txpin >= 0)
      _pinstart(txpin, P_OE | P_ASYNC_TX, bit_mode, 0);

    // set up the receive pin
    if (rxpin >= 0)
      _pinstart(rxpin, P_ASYNC_RX, bit_mode, 0);

    return fd;
}

int serial_close(FILE *device)
{
    int i;
    int tx_pin;
    int rx_pin;

    i = device->state >> 16;
    rx_pin = i & 0xff;
    tx_pin = i >> 8;

    if (tx_pin < 64)
      _pinf(tx_pin);
    if (rx_pin < 64)
      _pinf(rx_pin);

    if (device->vfsdata != 0)
      free(device->vfsdata);

    memset(device, 0, sizeof(device));

    return 0;
}

int serial_rxReady(FILE *device)
{
    int z = 0;
    int rx_pin;

    rx_pin = device->state >> 16;
    rx_pin = rx_pin & 0xff;
    z = _pinr(rx_pin);
    
    return z;
}

int serial_rxCheck(FILE *device)
{
    int z = 0;
    int rxbyte;
    int rx_pin;

    rx_pin = device->state >> 16;
    rx_pin = rx_pin & 0xff;
    z = _pinr(rx_pin);
    if (z == 0)
      return -1;
    
    rxbyte = _rdpin(rx_pin) >> 24; // shift down to byte
    rxbyte = rxbyte & 0xff;
    return rxbyte;
}

int serial_rxChar(FILE *device)
{
    int z = 0;
    int rxbyte;
    int rx_pin;

    rx_pin = device->state >> 16;
    rx_pin = rx_pin & 0xff;

    while (z == 0)
	    z = _pinr(rx_pin);
    
	rxbyte = _rdpin(rx_pin) >> 24; // shift down to byte
	rxbyte = rxbyte & 0xff;

	return rxbyte;
}

int serial_txChar(FILE *device, int txbyte)
{
    int z = 0;
    int tx_pin;

    tx_pin = device->state >> 16;
    tx_pin = tx_pin >> 8;

    _wypin(tx_pin, txbyte);

    for (int i=0;i<100;i++)
    {
      z = _pinr(tx_pin);
      if (z != 0)
        return 0;
      usleep(50);
    }

    return -1;
}

int serial_putcf(int c, FILE *device)
{
  return serial_txChar(device, c);
}

int serial_getcf(FILE *device)
{
  return serial_rxChar(device);
}

ssize_t serial_read(FILE *device, void *buff, size_t count)
{
  unsigned int i;
  int d;
  unsigned char *b = (unsigned char*)buff;

    for (i=0;i<count;i++)
    {
      d = serial_rxChar(device);
      if (d < 0)
        return i;
      b[i] = d;
    }

    return i;
}

ssize_t serial_write(FILE *device, const void *buff, size_t count)
{
    int z = 0;
    int tx_pin;
    const unsigned char *b = (const unsigned char*)buff;

    tx_pin = device->state >> 16;
    tx_pin = tx_pin >> 8;

    for (unsigned int i=0;i < count;i++)
    {
      _wypin(tx_pin, b[i]);
      while (z = _pinr(tx_pin) == 0)
        usleep(50);
    }

    return count;
}

void serial_startFullDuplex(FILE *device)
{
    if (_FDON == 1)
        return;

    _FDON = 1;
    cogstart(SFDuplex, device, SFDStack, 50);
}

int serial_count(void)
{
    int i;

    if (_FDON == 0)
        return 0;
    
    i = _RHead - _RTail;
    if (i < 0)
        i = i + 128;
    
    return i;
}

int serial_readFull(char *data, int count)
{
    int i;

    if (_FDON == 0)
        return;

    for (i=0;i<count;i++)
    {
        data[i] = 0;
        if (_RTail == _RHead)
            return i;
        data[i] = _RBuff[_RTail++];
        _RTail = _RTail & 127;
    }
    data[i] = 0;
    return i;
}

int serial_writeFull(char *data, int count)
{
    int i;

    if (_FDON == 0)
        return 0;

    for (i=0;i<count;i++)
    {
        _TBuff[_THead++] = data[i];
        _THead = _THead & 127;
    }

    return i;
}

int serial_readFullLine(char *data)
{
    int i;

    if (_FDON == 0)
        return;

    i = 0;
    while (_RTail != _RHead)
    {
        data[i] = _RBuff[_RTail++];
        _RTail = _RTail & 127;
        if (data[i++] == '\n')
        {
            data[i-1] = 0;
            return i-1;
        }
        data[i] = 0;
    }

    return i;
}

/**
 * Full Duplex background process
 * 
 */
void SFDuplex(void *par)
{
    int ch;
    _RHead = 0;
    _RTail = 0;
    _THead = 0;
    _TTail = 0;
    FILE *f;

    f = par;

    while (_FDON)
    {
        ch = serial_rxCheck(f);
        if (ch >=0)
        {
            _RBuff[_RHead++] = ch;
            _RHead = _RHead & 127;
        }

        if (_THead != _TTail)
        {
            serial_txChar(f, _TBuff[_TTail++]);
            _TTail = _TTail & 127;
        }
    }
}