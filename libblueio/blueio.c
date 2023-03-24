/**
 * @brief Blueio Notecard Driver
 * @author Michael Burmeister
 * @date February 8, 2023
 * @version 1.0
 */

//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <propeller.h>
#include "blueio.h"
#include "serial.h"
#include "json.h"


void Blueio_IO(void *);
int Blueio_Return(void);


FILE *bsr;
int brecv;
int btrans;
int *_px;
volatile int _head;
volatile int _tail;
int bstack[50];
char _XBuffer[4096];
char _XCmd[4096];
volatile int _trans;
volatile int _Ready;


int Blueio_Init(int receive, int transmit)
{
    int i;

    brecv = receive;
    btrans = transmit;

    i = cogstart(Blueio_IO, NULL, bstack, 50);
    _waitms(1000);

    if (i < 1)
        return -1;
    
    i = Blueio_Version();

    return i;
}

int Blueio_Request(char *request)
{
    json_init(_XCmd);
    json_putStr("req", request);

    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("request: %s\n", _XCmd);
#endif
    return _trans;
}

int Blueio_Receive(char *buffer)
{
    int i;

    i = 0;
    while (_head != _tail)
    {
        buffer[i++] = _XBuffer[_tail++];
        buffer[i] = 0;
        _tail = _tail & 4095;
    }
    _Ready = 0;
    return i;
}

void Blueio_Sync(void)
{
    int s;

    Blueio_Request("hub.sync");

    Blueio_Return();
}

int Blueio_Status(void)
{
    int s;
    char *x;

    Blueio_Request("hub.sync.status");

    s = Blueio_Return();
    if (s > 0)
    {
#ifdef DEBUG
        printf("status:%s\n", _XCmd);
#endif
        json_init(_XCmd);
        x = json_find("completed");
        return atoi(x);
    }
    return -1;
}

int Blueio_Version(void)
{
    int status;
    int version;

    version = 0;
    Blueio_Request("card.version");

    status = Blueio_Return();
    if (status > 0)
    {
        json_init(_XCmd);
        version = atoi(json_find("body.ver_major"));
        version = version * 10 + atoi(json_find("body.ver_minor"));
        version = version * 10 + atoi(json_find("body.ver_patch"));
        return version;
    }
    return 0;
}

int Blueio_Add(char *note)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "note.add");
    json_putObject("body");
    i = strlen(_XCmd);
    _XCmd[i-1] = 0;
    strcat(_XCmd, note);
    strcat(_XCmd, "}\r\n");

    _trans = strlen(_XCmd);

#ifdef DEBUG
    printf("Add:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
        json_init(_XCmd);
        x = json_find("total");
        if (x == NULL)
            return 0;
        else
            return atoi(x);
    }
    return -1;
}

int Blueio_Check(void)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "file.changes");
    json_putArray("files");
    json_putItem("data.qi");
    json_putItem(NULL);
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Check:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
        json_init(_XCmd);
        x = json_find("total");
        if (x == NULL)
            return 0;
        else
            return atoi(x);
    }
    return i;
}

int Blueio_GetData(char *data, int remove)
{
    int i;

    json_init(_XCmd);
    json_putStr("req", "note.get");
    json_putStr("file", "data.qi");
    if (remove != 0)
        json_putBool("delete", 1);
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Get:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    return i;
}

void Blueio_SetAttn(int mode, int time)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "card.attn");
    if (mode == 1)
        json_put("mode", "arm");
    if (mode == 2)
        json_putStr("mode", "sleep");
    if (mode == 3)
        json_putStr("mode", "disarm");
    json_putDec("seconds", itoa(time));
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Attn:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
        json_init(_XCmd);
    }
}

float Blueio_GetVoltage(void)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "card.voltage");
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Voltage:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
        json_init(_XCmd);
        x = json_find("value");
        return atof(x);
    }
    return 0;
}

float Blueio_GetTemperature(void)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "card.temp");
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Temp:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
        json_init(_XCmd);
        x = json_find("value");
        return atof(x);
    }
    return 0;
}

int Blueio_GetTime(void)
{
    int i;
    char *x;

    json_init(_XCmd);
    json_putStr("req", "card.time");
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Time:%s\n", _XCmd);
#endif

    i = Blueio_Return();
    if (i > 0)
    {
#ifdef DEBUG
        printf("T:%s\n", _XCmd);
#endif
        json_init(_XCmd);
        x = json_find("time");
        return atoi(x);
    }
    return 0;
}


/* Background send receive code */
void Blueio_IO(void *par)
{
    int i;

    bsr = serial_open(brecv, btrans, 9600);
    _head = 0;
    _tail = 0;
    _trans = 0;
    _Ready = 0;

    while (1)
    {
        if (serial_rxReady(bsr) != 0)
        {
            _XBuffer[_head++] = serial_rxChar(bsr);
            if (_XBuffer[_head-1] == '\n')
                _Ready = 1;

            _head = _head & 4095;
        }

        if (_trans > 0)
        {
            i = 0;
            while (_trans > 250)
            {
                serial_write(bsr, &_XCmd[i], 250);
                i += 250;
                _trans -= 250;
                _waitms(300);
            }
            i = serial_write(bsr, &_XCmd[i], _trans);
            serial_txChar(bsr, '\r');
            serial_txChar(bsr, '\n');
            _trans = 0;
        }
        usleep(50);
    }
}

/* wait 30 seconds for return data */
int Blueio_Return()
{
    int i;

    for (i=0;i<30;i++)
    {
        if (_Ready != 0)
        {
            i = Blueio_Receive(_XCmd);
            return i;
        }
        _waitms(1000);
    }
    return 0;
}

