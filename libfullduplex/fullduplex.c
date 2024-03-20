/**
 * @brief Full Duplex Driver for standard in/out
 * @author Michael Burmeister
 * @date April 25, 2023
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "fullduplex.h"

void FDuplex(void *);

unsigned long FDStack[50];
unsigned char _RBuff[128];
unsigned char _TBuff[128];
volatile int _Head, _Tail;
volatile int _Head2, _Tail2;
volatile int _FDTXv;
unsigned int _FDBaud;


void FD_Init(int baud)
{
    _FDBaud = baud;
    cogstart(FDuplex, NULL, FDStack, 50);
    _waitms(500);
    FD_PutStr("\r\n");
}

unsigned char FD_Getch(void)
{
    unsigned char ch = 0;

    while (_Head == _Tail)
        _waitus(50);

    ch = _RBuff[_Tail++];
    _Tail = _Tail & 127;

    return ch;
}

int FD_Check(void)
{
    if (_Head != _Tail)
        return 1;
    return 0;
}

void FD_Putch(unsigned char character)
{
    _TBuff[_Head2++] = character;
    _Head2 = _Head2 & 127;
}

void FD_PutStr(unsigned char *string)
{
    int l = strlen(string);
    int p = 0;

    while (l > 127)
    {
        while (_Head2 != _Tail2)
            _waitus(50);
        for (int i=0;i<127;i++)
            FD_Putch(string[p++]);
        l = l - 127;
    }

    for (int i=0;i<l;i++)
        FD_Putch(string[p++]);
}

int FD_Count(void)
{
    if (_Head > _Tail)
        return _Head - _Tail;
    else
        return (_Head + 128) - _Tail;
}


/**
 * Full Duplex background process
 * 
 */

void FDuplex(void *par)
{
    int ch;
    _Head = 0;
    _Tail = 0;
    _Head2 = 0;
    _Tail2 = 0;
    _setbaud(_FDBaud);

    while (1)
    {
        ch = _rxraw(2);
        if (ch >=0)
        {
            _RBuff[_Head++] = ch;
            _Head = _Head & 127;
        }

        if (_Head2 != _Tail2)
        {
            _txraw(_TBuff[_Tail2++]);
            _Tail2 = _Tail2 & 127;
        }
    }
}
