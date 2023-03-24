/**
 * @brief Driver for Wio E5 LoraWan Device
 * @author Michael Burmeister
 * @date February 11, 2023
 * @version 1.0
 * 
*/

//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <propeller.h>
#include "serial.h"

void WIOE5_IO(void *);
void WIOE5_Parse(void);
void WIOE5_Process(int);
int WIOE5_Return(void);
int WIOE5_Receive(char *);
int ConvertHex(char *); 

char _RTN[][5] = {"+AT:", "+VER", "+RES", "+MSG", "+CMS", "+POR", "+ADR", "+DR:",
                  "+CH:", "+POW", "+REP", "+RET", "+RWX", "+KEY", "+FDE", "+DFU",
                  "+MOD", "+JOI", "+BEA", "+CLA", "+DEL", "+LW:", "+WDT", "+LOW",
                  "+VDD", "+TEM", "+RTC", "+EEP", "+UAR", "+TES", "+LOG"};
FILE *_wio;
char _WData[512];
char _WCmd[512];
long _wstack[50];
volatile int _hd;
volatile int _tl;
volatile int _wtx;
volatile int _Rdy;
volatile int Ver;
volatile int Val;
#ifdef DEBUG
volatile int Fun;
#endif
int _Wx;
int _Wr;


int WIOE5_Init(int rx, int tx)
{
    int i;

    _Wx = tx;
    _Wr = rx;

    i = cogstart(WIOE5_IO, NULL, _wstack, 50);
    _waitms(500);

    WIOE5_Request("AT");

    i = WIOE5_GetVer();
    return i;
}

int WIOE5_GetVer(void)
{
    int i, x;

    i = WIOE5_Request("at+ver");

    return Ver;
}

int WIOE5_GetID(void)
{
    int i;
    int v;
    int id;
    int c;

    i = WIOE5_Request("at+id");
    c = 28;
    id = 0;
    for (int i=14;i<25;i++)
    {
        v = _WCmd[i] - '0';
        if (v == 10)
            continue;
        if (v > 10)
            v = v - 7;
        id = id | v << c;
        c -= 4;
    }
    return id;
}

int WIOE5_Request(char *request)
{
    int i;

    strcpy(_WCmd, request);

    _wtx = strlen(_WCmd);

#ifdef DEBUG
    printf("Request: %s\n", _WCmd);
#endif
    i = WIOE5_Return();
#ifdef DEBUG
    printf("Function: %d\n", Fun);
    printf(_WCmd);
#endif
    _Rdy = 0;
    return i;   
}

int WIOE5_Results(char *buffer)
{
    int i;

    i = WIOE5_Return();

    buffer[0] = 0;

    if (i > 0)
        memcpy(buffer, _WCmd, i);
    
    return i;
}

void WIOE5_Reset(void)
{
    int i;

    i = WIOE5_Request("at+reset");
}

int WIOE5_SetMode(int mode)
{
    int i;

    switch (mode)
    {
        case 0: i = WIOE5_Request("at+mode=LWABP");
            break;
        case 1: i = WIOE5_Request("at+mode=LWOTAA");
            break;
        case 2: i = WIOE5_Request("at+mode=TEST");
            break;
        default: return -1;
    }

    return _Rdy;
}

void WIOE5_SetClass(int class)
{
    int i;

    switch (class)
    {
        case 0: i = WIOE5_Request("at+class=A");
            break;
        case 1: i = WIOE5_Request("at+class=B");
            break;
        case 2: i = WIOE5_Request("at+class=C");
            break;
        default:
            break;
    }

}

int WIOE5_Join(void)
{
    int i;

    i = WIOE5_Request("at+join");

    return i;
}

void WIOE5_Send(char *message)
{
    int i;

    strcpy(_WCmd, "at+msg=\"");
    strcat(_WCmd, message);
    strcat(_WCmd, "\"");

    i = WIOE5_Request(_WCmd);
}

int WIOE5_SendConfirmed(char *message)
{
    int i;

    strcpy(_WCmd, "at+cmsg=\"");
    strcat(_WCmd, message);
    strcat(_WCmd, "\"");
    i = WIOE5_Request(_WCmd);

    return i;
}

int WIOE5_SendHex(char *message)
{
    int i;

    strcpy(_WCmd, "at+msghex=\"");
    strcat(_WCmd, message);
    strcat(_WCmd, "\"");
    i = WIOE5_Request(_WCmd);
    return i;
}

int WIOE5_SendConfirmedHex(char *message)
{
    int i;

    strcpy(_WCmd, "at+cmsghex=\"");
    strcat(_WCmd, message);
    strcat(_WCmd, "\"");

    i = WIOE5_Request(_WCmd);
    if (i > 40)
        return 0;

    return i;
}

void WIOE5_SetPort(int port)
{
    int i;

    sprintf(_WCmd, "at+port=\"%d\"", port);
    i = WIOE5_Request(_WCmd);
}

void WIOE5_SetDataRate(int rate)
{
    int i;

    sprintf(_WCmd, "at+dr=\"%d\"", rate);

    i = WIOE5_Request(_WCmd);
}

void WIOE5_SetLora(int mode, int freq, int sf)
{
    int i;

    WIOE5_SetMode(2);
    sprintf(_WCmd, "at+test=rfcfg,%d,sf%d,125,8,8,14,on,off,on", freq, sf);
    if (mode == 0)
    {
        i = WIOE5_Request(_WCmd);
    }
}

void WIOE5_SendLora(char *data)
{
    int i;

    strcpy(_WCmd, "at+test=txlrpkt,\"");
    strcat(_WCmd, data);
    strcat(_WCmd, "\"");

    i = WIOE5_Request(_WCmd);
}

int WIOE5_GetLora(char *buf)
{
    int i;

    i = WIOE5_Request("at+test=rxlrpkt");
    while (WIOE5_Return() < 0);

    i = ConvertHex(_WCmd);
    memcpy(buf, _WCmd, i);
    return i;
}

void WIOE5_SetLowPower(int mode)
{
    int i;

    if (mode == 0)
    {
        i = WIOE5_Request("at+lowpower");
        return;
    }
    
    if (mode == 1)
    {
        i = WIOE5_Request("at+lowpower=autoon");
        return;
    }

    if (mode == 2)
    {
        i = WIOE5_Request("at+lowpower=autooff");
        return;
    }

    if (mode == 3)
    {
        WIOE5_Request("AT");
        return;
    }

    if (mode < 100)
        return;

    sprintf(_WCmd, "at+lowpower=%d", mode);
    i = WIOE5_Request(_WCmd);
    while (WIOE5_Return() < 0);
}

void WIOE5_SetMemory(char address, char value)
{
    int i;

    sprintf(_WCmd, "at+eeprom=%x, %x", address, value);
    i = WIOE5_Request(_WCmd);
}

char WIOE5_GetMemory(char address)
{
    int i;

    sprintf(_WCmd, "at+eeprom=%x", address);
    i = WIOE5_Request(_WCmd);
    return Val;
}


/**
 * Background serial interface tasks
 * 
 */
void WIOE5_IO(void *par)
{
    int i;

    _wio = serial_open(_Wr, _Wx, 9600);

    _hd = 0;
    _tl = 0;
    _wtx = 0;
    _Rdy = 0;

    while (1)
    {
        if (serial_rxReady(_wio) != 0)
        {
            _WData[_hd] = serial_rxChar(_wio);
            if (_WData[_hd++] == '\n')
                WIOE5_Parse();

            _hd = _hd & 511;
        }

        if (_wtx > 0)
        {
            i = serial_write(_wio, _WCmd, _wtx);
            serial_txChar(_wio, '\r');
            serial_txChar(_wio, '\n');
            _wtx = 0;
        }
        usleep(50);
    }
}

void WIOE5_Parse()
{
    int i, x;

    i = WIOE5_Receive(_WCmd);
    for (int z=0;z<31;z++)
    {
        if (memcmp(_WCmd, _RTN[z], 4) == 0)
        {
            WIOE5_Process(z);
            return;
        }
    }
}

void WIOE5_Process(int i)
{
    int x;

#ifdef DEBUG
    Fun = i;
#endif
    switch (i)
    {
    case 1: x = 0;
            i = strlen(_WCmd);
            for (int j=6;j<i;j++)
                if (_WCmd[j] != '.')
                    _WCmd[x++] = _WCmd[j];
            _WCmd[x] = 0;
            Ver = atoi(_WCmd);
            _Rdy = 1;
        break;
    case 3:
    case 4:
    case 5: if (_WCmd[7] == 'D')
                _Rdy = 1;
            if (_WCmd[7] == 'P')
                _Rdy = -1;
            if (_WCmd[7] == 'N')
                _Rdy = -1;
        break;
    case 8: if ((_WCmd[7] == 'U') || (_WCmd[7] == 'E'))
                _Rdy = 1;
        break;
    case 17: if (_WCmd[7] == 'D')
                _Rdy = 1;
             if (memcmp(&_WCmd[7], "Join ", 5) == 0)
                _Rdy = -1;
             if (memcmp(&_WCmd[7], "Joine", 5) == 0)
                _Rdy = 1;
             if (_WCmd[7] == 'L')
                _Rdy = -1;
             if (memcmp(&_WCmd[7], "Not", 3) == 0)
                _Rdy = -1;
        break;
    case 27: _WCmd[12] = '\"';
             ConvertHex(_WCmd);
             Val = _WCmd[0];
             _Rdy = 1;
        break;
    case 29: if (_WCmd[7] != 'L')
                _Rdy = 1;
        break;
    default: _Rdy = 1;
        break;
    }

}

int WIOE5_Return()
{
    int i;

    while (_wtx > 0)
        _waitms(50);

    _WCmd[0] = 0;
    for (i=0;i<30;i++)
    {
        if (_Rdy != 0)
            return _Rdy;
        _waitms(500);
    }
    return -1;
}

int WIOE5_Receive(char *buffer)
{
    int i;

    i = 0;
    while (_hd != _tl)
    {
        buffer[i++] = _WData[_tl++];
        _tl = _tl & 511;
        buffer[i] = 0;
    }
    _Rdy = 0;
    return i;
}

int ConvertHex(char *data)
{
    int i, j, h, l;

    j = 0;
    i = 0;
    while (data[i++] != '\"');

    while ((data[i] != '\"') && (data[i] != '\r'))
    {
        h = data[i] - '0';
        l = data[i+1] - '0';
        if (h > 9)
            h = h - 7;
        if (l > 9)
            l = l - 7;
        data[j++] = h << 4 | l;
        i += 2;
    }
    return j;
}

