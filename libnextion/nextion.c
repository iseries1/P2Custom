/**
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.2
 * 
*/

//#define DEBUG

#define IBUFF 512
#define OBUFF 512

#include <stdio.h>
#include <propeller.h>
#include "simpletools.h"
#include "nextion.h"
#include "serial.h"

void Nextion_connect(void);
void Nextion_return(void);
void Nextion_value(void);
void Nextion_button(void);
void Nextion_sendme(void);
void Nextion_touche(void);
void Nextion_sleep(void);
void Nextion_wake(void);
void Nextion_text(void);
void Nextion_numeric(void);
void DoSendRecv(void *);
void Nextion_send(unsigned char);
void Nextion_debug(void);

FILE *nxn;
unsigned char _DataT[OBUFF];
unsigned char _DataR[IBUFF];
#ifdef DEBUG
unsigned char Buffer[2048];
int pointer = 0;
#endif
struct tm *tt;
int _Head;
int _Tail;
char _Rx, _Tx;
int _Baud;
int _Index;
int _Error;
int  _Reserved;
char _Model[20];
int _Firmware = 0;
int _MCUSize = 0;
char _SerialNumber[20];
int _Flash = 0;
int _Page = 0;
int _Button = 0;
int _Event = 0;
int _XPosition = 0;
int _YPosition = 0;
int _Touch;
int _Sleep = 0;
short _REN = 0;
char _Text[50];
int _Value = 0;


int *cog;


int Nextion_open(int rx, int tx, int baud)
{
  int i;
  
  _Rx = rx;
  _Tx = tx;
  _Baud = baud;
  _Reserved = 0;
  _SerialNumber[0]=0;
  
  _Error = -1;
  
  cog = cog_run(&DoSendRecv, 50);
  
  _waitms(1000);
  
  Nextion_cmd("code_c");

  _waitms(1000);
  
  Nextion_cmd("connect");
  
  _waitms(1000);
  
  i = _Reserved;
  
  return i;
}

void Nextion_close()
{
  _Baud = 0;
  while (nxn != NULL)
    _waitms(1);
}
  
void Nextion_cmd(char *c)
{
  for (int i=0;i<strlen(c);i++)
    Nextion_send(c[i]);

  Nextion_send(0xff);
  Nextion_send(0xff);
  Nextion_send(0xff);
}

void Nextion_setProperty(char *obj, char *prop, char *val)
{
  sprintf(_DataT, "%s.%s=\"%s\"", obj, prop, val);
  Nextion_cmd(_DataT);
}

void Nextion_return()
{
  
  if (_Index < 1)
  {
    return;
  }

  for (int i=0;i<_Index;i++)
  {
    if (_DataT[i] == 0xff)
      if (_DataT[i+1] == 0xff)
        if (_DataT[i+2] == 0xff)
          Nextion_value();
  }
}

void Nextion_value()
{
  char v;
  
  v = _DataT[0];

  switch (v)
  {
    case 0x00: _Error = 0; //Invalid instruction
      break;
    case 0x01: _Error = 1; //Success
      break;
    case 0x02: _Error = 2; //Component ID invalid
      break;
    case 0x03: _Error = 3; //Page ID invalid
      break;
    case 0x04: _Error = 4; //Picture ID invalid
      break;
    case 0x05: _Error = 5; //Font ID invalid
      break;
    case 0x11: _Error = 17; //Baud rate settings invalid
      break;
    case 0x12: _Error = 18; //Curve control ID number or channel number is invalid
      break;
    case 0x1a: _Error = 26; //Variable name invalid
      break;
    case 0x1b: _Error = 27; //Variable operation invalid
      break;
    case 0x1c: _Error = 28; //Failed to assign
      break;
    case 0x1d: _Error = 29; //Operate EEPROM failed
      break;
    case 0x1e: _Error = 30; //Parameter quantity invalid
      break;
    case 0x1f: _Error = 31; //IO operation failed
      break;
    case 0x20: _Error = 32; //Undefined escape characters
      break;
    case 0x23: _Error = 35; //Too long variable name
      break;
    case 0x24: // serial buffer overflow
      break;
    case 0x63: Nextion_connect(); // process connect command
      _REN = 19;
      break;
    case 0x65: Nextion_button(); // process object touch
      _REN = 21;
      break;
    case 0x66: Nextion_sendme(); // process sendme command
      _REN = 22;
      break;
    case 0x67: Nextion_touche(); // process touch event
      _REN = 23;
      break;
    case 0x68: Nextion_touche(); // process sleep event
      _REN = 24;
      break;
    case 0x70: Nextion_text(); // process text value
      _REN = 25;
      break;
    case 0x71: Nextion_numeric(); // process number value
      _REN = 26;
      break;
    case 0x86: Nextion_sleep(); // process panel sleep
      _REN = 27;
      break;
    case 0x87: Nextion_wake(); // process panel wake
      _REN = 28;
      break;
    case 0x88: // process panel power on
    case 0x89: // process sd card load
    case 0xfd: // transparent mode ending
    case 0xfe: // transparent mode starting
      break;
    default: _Error = 0;
  }

  _Index = 0;
}

void Nextion_connect()
{
  int i, j, k;
  
 _Reserved = 0;
 _Model[0] = 0;
 _Firmware = 0;
 _MCUSize = 0;
 _SerialNumber[0] = 0;
 _Flash = 0;
 
 i = 0;
 for (k=0;k<_Index;k++)
 {
   if (_DataT[k] == ',')
   {
     j = 0;
     i++;
     k++;
   }     
   switch (i)
   {
     case 0 :
      break;
     case 1 : _Reserved = _Reserved * 10 + _DataT[k] - '0';
      break;
     case 2 : _Model[j++] = _DataT[k];
              _Model[j] = 0;
      break;
     case 3 : _Firmware = _Firmware * 10 + _DataT[k] - '0';
      break;
     case 4 : _MCUSize = _MCUSize * 10 + _DataT[k] - '0';
      break;
     case 5 : _SerialNumber[j++] = _DataT[k];
              _SerialNumber[j] = 0;
      break;
     case 6 : _Flash = _Flash * 10 + _DataT[k] - '0';
      break;
    }
  }
}

int Nextion_error()
{
  int i;

  i = _Error;
  _Error = -1;
  return i;
}

void DoSendRecv(void *par)
{
  
  nxn = serial_open(_Rx, _Tx, _Baud);
  
  _Head = 0;
  _Tail = 0;

  while (_Baud != 0)
  {
    while (serial_rxReady(nxn) > 0)
    {
      _DataT[_Index] = serial_rxChar(nxn);
#ifdef DEBUG
      Buffer[pointer++] = _DataT[_Index];
      Buffer[pointer] = 0;
#endif
      if (_Index++ > IBUFF - 10)
        _Index = IBUFF - 10;
      _DataT[_Index] = 0;
    }
    Nextion_return();

    while (_Head != _Tail)
    {
#ifdef DEBUG
      Buffer[pointer++] = _DataR[_Tail];
#endif
      serial_txChar(nxn, _DataR[_Tail++]);
      _Tail = _Tail & (OBUFF - 1);
    }
  }
  
  serial_close(nxn);
  nxn = NULL;
  _cogstop(_cogid());
}

void Nextion_send(unsigned char s)
{
  while (((_Head + 1) & (OBUFF - 1)) == _Tail)
  {
    low(20);
    _waitms(500);
    high(20);
  }    
  _DataR[_Head++] = s;
  _Head = _Head & (OBUFF - 1);
}

short Nextion_event()
{
  short i;
  
  i = _REN;
  _REN = 0;
  
  return i;
}
  
void Nextion_button()
{
  _Page = _DataT[1];
  _Button = _DataT[2];
  _Touch = _DataT[3];
}

void Nextion_sendme()
{
  _Page = _DataT[1];
}

void Nextion_touche()
{
  _XPosition = _DataT[1];
  _XPosition = _XPosition << 8 | _DataT[2];
  _YPosition = _DataT[3];
  _YPosition = _YPosition << 8 | _DataT[4];
  _Touch = _DataT[5];
}

void Nextion_sleep()
{
  _Sleep = 1;
}

void Nextion_wake()
{
  _Sleep = 0;
}

void Nextion_text()
{
  int i, j;
  
  j = 0;
  for (i=1;i<50;i++)
  {
    if (_DataT[i] == 0xff)
      break;
    _Text[j++] = _DataT[i];
  }
  _Text[j] = 0;
}

void Nextion_numeric()
{
  _Value = _DataT[4];
  _Value = _Value << 8 | _DataT[3];
  _Value = _Value << 8 | _DataT[2];
  _Value = _Value << 8 | _DataT[1];
}

char *Nextion_serialno()
{
  return _SerialNumber;
}

int Nextion_color(short blue, short green, short red)
{
  int color;
  
  color = blue | (green << 5) | (red << 11);
  
  return color;
}

int Nextion_page(void)
{
  return _Page;
}

void Nextion_setpage(int page)
{
  sprintf(_DataT, "page %d", page);
  Nextion_cmd(_DataT);
}

void Nextion_cls(int color)
{
  sprintf(_DataT, "cls %d", color);
  Nextion_cmd(_DataT);
  _waitms(3000);
}

int Nextion_getnumeric()
{
  return _Value;
}

char *Nextion_gettext()
{
  return _Text;
}

int Nextion_gettouch(short *page, short *id)
{
  *page = _Page;
  *id = _Button;
  return _Touch;
}

int Nextion_touchxy(short *x, short *y)
{
  *x = _XPosition;
  *y = _YPosition;
  return _Touch;
}

void Nextion_settext(char *var, char *val)
{
  sprintf(_DataT, "%s.txt=\"%s\"", var, val);
  Nextion_cmd(_DataT);
}
  
void Nextion_setnumeric(char *var, int val)
{
  sprintf(_DataT, "%s.val=%d", var, val);
  Nextion_cmd(_DataT);
}

void Nextion_setbaud(int baud)
{
  sprintf(_DataT, "baud=%d", baud);
  Nextion_cmd(_DataT);
}

void Nextion_setsleep(int t)
{
  sprintf(_DataT, "thsp=%d", t);
  Nextion_cmd(_DataT);
  if (t == 0)
    Nextion_cmd("thup=0");
  else
    Nextion_cmd("thup=1");
}

void Nextion_touch(int events)
{
  sprintf(_DataT, "sendxy=%d", events);
  Nextion_cmd(_DataT);
}

void Nextion_setbrightness(int b)
{
  sprintf(_DataT, "dim=%d", b);
  Nextion_cmd(_DataT);
}
  
void Nextion_xstr(short x, short y, short w, short h, char f, int pco, int bco, char xcen, char ycen, char sta, char *text)
{
  sprintf(_DataT, "xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\"", x, y, w, h, f,
          pco, bco, xcen, ycen, sta, text);
  Nextion_cmd(_DataT);
}

void Nextion_fill(short x, short y, short width, short height, int color)
{
  sprintf(_DataT, "fill %d,%d,%d,%d,%d", x, y, width, height, color);
  Nextion_cmd(_DataT);
}

void Nextion_line(short x, short y, short x1, short y1, int color)
{
  sprintf(_DataT, "line %d,%d,%d,%d,%d", x, y, x1, y1, color);
  Nextion_cmd(_DataT);
}

void Nextion_circle(short x, short y, short radius, int color)
{
  sprintf(_DataT, "cir %d,%d,%d,%d", x, y, radius, color);
  Nextion_cmd(_DataT);
}

void Nextion_fillcircle(short x, short y, short radius, int color)
{
  sprintf(_DataT, "cirs %d,%d,%d,%d", x, y, radius, color);
  Nextion_cmd(_DataT);
}

void Nextion_click(char *item, char value)
{
  sprintf(_DataT, "click %s,%d", item, value);
  Nextion_cmd(_DataT);
}

void Nextion_settime(long i)
{
  tt = localtime(&i);
  i = tt->tm_year+1900;
  sprintf(_DataT, "rtc0=%d", i);
  Nextion_cmd(_DataT);
  i = tt->tm_mon;
  sprintf(_DataT, "rtc1=%d", i);
  Nextion_cmd(_DataT);
  i = tt->tm_mday;
  sprintf(_DataT, "rtc2=%d", i);
  Nextion_cmd(_DataT);
  i = tt->tm_hour;
  sprintf(_DataT, "rtc3=%d", i);
  Nextion_cmd(_DataT);
  i = tt->tm_min;
  sprintf(_DataT, "rtc4=%d", i);
  Nextion_cmd(_DataT);
  i = tt->tm_sec;
  sprintf(_DataT, "rtc5=%d", i);
  Nextion_cmd(_DataT);
}

void Nextion_debug(void)
{
#ifdef DEBUG
  for (int i=0;i<strlen(Buffer);i++)
  {
    if (Buffer[i] == 0xff)
    {
      putChar('\n');
      i += 2;
    }      
    else
      putChar(Buffer[i]);
  }
#endif
  printf("\n");
}
