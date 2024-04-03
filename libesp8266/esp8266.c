/**
 * @brief ESP8266 command driver library
 * @author Michael Burmeister
 * @version 1.2
 * @date November 29, 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <propeller.h>
#include "serial.h"
#include "esp8266.h"

void DoESP8266(void *);
int Count();
unsigned char GetChar(void);
void PutChar(unsigned char);
void PutStr(unsigned char *);
int DoRecv(void);
int DoWait(void);


#define JOIN    0xEF
#define CONNECT 0xE4
#define CLOSE   0xE8
#define LISTEN  0xE7
#define REPLY   0xE5
#define POLL    0xEC
#define RECV    0xE9
#define SEND    0xEA
#define CHECK   0xEE
#define SET     0xED
#define PATH    0xEB
#define ARG     0xE6
#define CMD     0xFE
#define UDP     0xDE
#define SLEEP   0xF1

int ESPStack[100];
char _RBuff[128];
char _TBuff[128];
char _Buffer[1050];
char _URL[128];
unsigned char _Status;
int _SValue;
char *_Header = NULL;
int _RXpin;
int _TXpin;
int _Baud;
volatile int _Head, _Tail, _Head2, _Tail2;


void esp8266_Open(int rx, int tx, int baud)
{
    _RXpin = rx;
    _TXpin = tx;
    _Baud = baud;

    cogstart(DoESP8266, NULL, ESPStack, 50);
    _waitms(500);
}

int esp8266_Connect(char *url, short port)
{
    int i;

    strcpy(_URL, url);
    i = DoRecv();
    sprintf(_Buffer, "%c%c%s,%d\r", CMD, CONNECT, url, port);
    PutStr(_Buffer);

    i = DoWait();

    if (i < 0)
        return -1;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;

}

int esp8266_Send(char handle, char *request)
{
    int i;

    i = strlen(request);
    return esp8266_SendBin(handle, request, i);
}

int esp8266_Http(char handle, char *request, short opt)
{
    int i;

    strcpy(_Buffer, request);
    strcat(_Buffer, " HTTP/1.1\r\nHost: ");
    strcat(_Buffer, _URL);
    strcat(_Buffer, "\r\nConnection: ");
    if (opt == 0)
        strcat(_Buffer, "close");
    else
        strcat(_Buffer, "keep-alive");
    if (_Header != NULL)
    {
        strcat(_Buffer, "\r\n");
        strcat(_Buffer, _Header);
    }
    strcat(_Buffer, "\r\nAccept: */\*\r\n\r\n");

    i = strlen(_Buffer);

    return esp8266_SendBin(handle, _Buffer, i);
}

void esp8266_setHeader(char *header)
{
    _Header = header;
}

int esp8266_SendBin(char handle, char *data, int size)
{
    int i, j;

    sprintf(_URL, "%c%c%d,%d\r", CMD, SEND, handle, size);
    PutStr(_URL);

    for (j=0;j<size;j+=32)
    {
        i = size - j;
        if (i > 32)
            i = 32;
        
        for (int k=0;k<i;k++)
            PutChar(data[j+k]);
        _waitms(1);
    }

    i = DoWait();

    if (i <= 0)
        return i;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;
}

int esp8266_Recv(char handle, char *data, int size)
{
    int i, s;
    char *r;

    if (size > 1024)
        size = 1024;

    sprintf(_URL, "%c%c%d,%d\r", CMD, RECV, handle, size);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return i;
    
    r = memchr(_Buffer, '\r', 15);
    if (r == NULL)
        return -1;
    
    s = i - (r - _Buffer);
    memcpy(data, &r[1], s);
    data[s] = 0;

    i = DoRecv();
    if (i > 0)
        strcat(data, _Buffer);
    
    return _SValue;
}

int esp8266_UDP(char *url, short port)
{
    int i;

    i = DoRecv();
    sprintf(_URL, "%c%c%s,%d\r", CMD, UDP, url, port);
    PutStr(_URL);

    i = DoWait();

    if (i < 0)
        return i;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;
}

void esp8266_Close(char handle)
{
    sprintf(_URL, "%c%c%d\r", CMD, CLOSE, handle);
    PutStr(_URL);
    DoWait();
}

int esp8266_Join(char *sid, char pwd)
{
    int i;

    sprintf(_URL, "%c%c%s,%s\r", CMD, JOIN, sid, pwd);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return i;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;
}

int esp8266_Set(char *env, char *value)
{
    int i;

    sprintf(_URL, "%c%c%s,%s\r", CMD, SET, env, value);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return i;
    
    if (_Status == 'S')
        return _Status;
    
    return -_Status;
}

char *esp8266_Check(char *env)
{
    int i;

    i = DoRecv();

    sprintf(_URL, "%c%c%s\r", CMD, CHECK, env);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return NULL;

    if (_Status == 'S')
        return &_Buffer[4];
    
    return NULL;
}

int esp8266_Poll(int mask)
{
    int i;

    if (mask == 0)
        mask = -1;
    sprintf(_URL, "%c%c%d\r", CMD, POLL, mask);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return i;
    
    return _Status;
}

int esp8266_Listen(char *protocol, char *uri)
{
    int i;

    sprintf(_URL, "%c%c%c%s\r", CMD, LISTEN, protocol, uri);
    PutStr(_URL);
    i = DoWait();
    if (i <= 0)
        return i;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;
}

int esp8266_Reply(char handle, char *data)
{
    int i, j;
    int size;

    size = strlen(data);
    sprintf(_URL, "%c%c%d,200,%d\r", CMD, REPLY, handle, size);
    PutStr(_URL);
    
    for (j=0;j<size;j+=32)
    {
        i = size - j;
        if (i > 32)
            i = 32;
        
        for (int k=0;k<i;k++)
            PutChar(data[j+k]);
        _waitms(1);
    }

    i = DoWait();
    if (i <= 0)
        return i;
    
    if (_Status == 'S')
        return _SValue;
    
    return -_SValue;
}

int esp8266_Wait(char *type)
{
    while (DoWait() <= 0);
    *type = _Status;
    return _SValue;
}

char *esp8266_Path(char handle)
{
    int i;

    sprintf(_URL, "%c%c%d\r", CMD, PATH, handle);
    PutStr(_URL);

    i = DoWait();
    if (i <= 0)
        return NULL;
    
    if (_SValue == 'S')
        return &_Buffer[4];
    
    return NULL;
}

char *esp8266_arg(char handle, char *name)
{
    sprintf(_URL, "%c%c%d,%s\r", CMD, ARG, handle, name);
    PutStr(_URL);
    if (DoWait() <= 0)
        return NULL;
    
    if (_Status == 'S')
        return &_Buffer[4];
    
    return NULL;
}

void esp8266_Print(char *data, int size)
{
    for (int n=0;n < size;n++)
    {
        if ((data[n] <= 128) && (data[n] != ' '))
            PutChar(data[n]);
        else if (data[n] == 0)
        {
            printf("[0]");
            break;
        }
        else if (data[n] == '\n')
            PutChar('\n');
        else
            printf("[%x]", data[n]);

    }
}


/* Process Requests */
int DoRecv()
{
    int i, j;
    int t, c;

    c = _getms() + 500;
    t = 0;
    i = 0;

    while (t < c)
    {
        if (Count() > 0)
        {
            j = Count();
            if ((j + i) >= 1023)
                j = 1023 - i;
            
            for (int k = 0;k < j;k++)
                _Buffer[i++] = GetChar();
            
            _Buffer[i] = 0;
            if (i > 1023)
                return i;
        }
        _waitms(1);

        t = _getms();
    }

    return i;
}

void DoESP8266(void *par)
{
    FILE *esp;

    _pinl(_TXpin);
    _waitms(5);
    _pinh(_TXpin);

    esp = serial_open(_RXpin, _TXpin, _Baud);
    int ch;
    _Head = 0;
    _Tail = 0;
    _Head2 = 0;
    _Tail2 = 0;

    while (_Baud != 0)
    {
        ch = serial_rxReady(esp);
        if (ch != 0)
        {
            ch = serial_rxChar(esp);
            _RBuff[_Head++] = ch;
            _Head = _Head & 127;
        }

        if (_Head2 != _Tail2)
        {
            serial_txChar(esp, _TBuff[_Tail2++]);
            _Tail2 = _Tail2 & 127;
        }
    }
}

int Count()
{
    int t;

    if (_Tail > _Head)
        t = _Head - _Tail + 128;
    else
        t = _Head - _Tail;
    
    return t;
}

unsigned char GetChar()
{
    char c;

    if (_Head != _Tail)
        c = _RBuff[_Tail++];
    _Tail = _Tail & 127;

    return c;
}

void PutChar(unsigned char c)
{
    _TBuff[_Head2++] = c;
    _Head2 = _Head2 & 127;
}

int DoWait()
{
    int i, t;

    t = 0;
    i = 0;

    while (i == 0)
    {
        if (t++ > 30)
            return -1;
        
        i = DoRecv();
    }

    _Status = ' ';
    _SValue = 0;

    if (_Buffer[0] != CMD)
        return -1;
    
    _Status = _Buffer[2];
    _SValue = atoi(&_Buffer[4]);

    return i;
}

void PutStr(unsigned char *str)
{
    for (int i=0;i<strlen(str);i++)
        PutChar(str[i]);
}

