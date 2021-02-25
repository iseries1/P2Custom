/**
 * @brief Driver for CH559 USB Host device
 * @author Michael Burmeister
 * @date Feburary 11, 2021
 * @version 1.0
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "ch559.h"
#include "serial.h"


int _RXPin;
char _Buffer[1024];
volatile int Head;
volatile int Tail;
int Stack[50];
FILE *s;

void CH559_Open(int rxpin, int txpin)
{
    _RXPin = rxpin;
    Head = 0;
    Tail = 0;
    
    _cogstart(CH559Run, NULL, Stack, 49);
}


void CH559Run(void *par)
{
    int ch;
    
    s = serial_open(_RXPin, 1, 400000);
    
    while (1)
    {
        ch = serial_rxChar(s);
        _Buffer[Head++] = ch;
        Head = Head & 0x3ff;
    }
}

int CH559_Recieve(char *data, int size)
{
    int i;
    
    i = 0;
    while (Head != Tail)
    {
        data[i++] = _Buffer[Tail++];
        Tail = Tail & 0x3ff;
        if (i >= size)
            break;
    }
    
    data[i] = 0;
    return i;
}
