/**
 * @brief Blueio Notecard Driver
 * @author Michael Burmeister
 * @date February 8, 2023
 * @version 1.0
 */

#define DEBUG

#include <stdio.h>
#include <string.h>
#include <propeller.h>
#include "blueio.h"
#include "serial.h"
#include "json.h"


void Blueio_IO(void *);

const char crlf[] = "\r\n";
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
    _waitms(100);

    if (i < 1)
        return -1;
    
    i = Blueio_Version();

    return i;
}

int Blueio_Request(char *request)
{
    json_init(_XCmd);
    json_putStr("req", request);
    strcat(_XCmd, crlf);

    _trans = strlen(_XCmd);

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

int Blueio_Ready(void)
{
    return _Ready;
}

void Blueio_Sync(void)
{
    int s;

    Blueio_Request("hub.sync");
    for (int i=0;i<10;i++)
    {
        s = Blueio_Ready();
        if (s != 0)
        {
            s = Blueio_Receive(_XCmd);
            return;
        }
        _waitms(1000);
    }
}

int Blueio_Status(void)
{
    int s;

    Blueio_Request("hub.sync.status");
    for (int i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            s = Blueio_Receive(_XCmd);
#ifdef DEBUG
            printf("status:%s\n", _XCmd);
#endif
            return 0;
        }
        _waitms(1000);
    }

}

int Blueio_Version(void)
{
    int status;
    int version;

    version = 0;
    Blueio_Request("card.version");
    for (int i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            status = Blueio_Receive(_XCmd);
            json_init(_XCmd);
            version = atoi(json_find("body.ver_major"));
            version = version * 10 + atoi(json_find("body.ver_minor"));
            version = version * 10 + atoi(json_find("body.ver_patch"));
            return version;
        }
        _waitms(1000);
    }

    return version;
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
    for (i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            i = Blueio_Receive(_XCmd);
            json_init(_XCmd);
            x = json_find("total");
            if (x == NULL)
                return 0;
            else
                return atoi(x);
        }
        _waitms(1000);
    }
    return -1;
}

int Blueio_Check(void)
{
    char *x;

    json_init(_XCmd);
    json_putStr("req", "file.changes");
    json_putArray("files");
    json_putItem("data.qi");
    json_putItem(NULL);
    strcat(_XCmd, crlf);
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Check:%s\n", _XCmd);
#endif
    for (int i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            i = Blueio_Receive(_XCmd);
            json_init(_XCmd);
            x = json_find("total");
            if (x == NULL)
                return 0;
            else
                return atoi(x);
        }
        _waitms(1000);
    }

}

int Blueio_Get(char *data, int remove)
{
    int i;

    json_init(_XCmd);
    json_putStr("req", "note.get");
    json_putStr("file", "data.qi");
    if (remove != 0)
        json_putBool("delete", 1);
    strcat(_XCmd, crlf);
    _trans = strlen(_XCmd);
#ifdef DEBUG
    printf("Get:%s\n", _XCmd);
#endif
    for (i=0;i<10;i++)
    {
        if (Blueio_Ready() != 0)
        {
            i = Blueio_Receive(data);
            return i;
        }
        _waitms(1000);
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
            _trans = 0;
        }
        usleep(50);
    }
}
