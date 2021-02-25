/**
 * @brief Interface New Haven EVE2 Display 800x480
 * @author Michael Burmeister
 * @date July 30, 2018
 * @version 1.2
 * 
*/

#include <stdio.h>
#include <propeller.h>
#include "newhaven.h"

void CLR(void);
void doMenu(void);
void doText(void);
void doClock(void);
void doGauge(void);
void doProgress(void);
void doScrollBar(void);
void doSlider(void);
void doToggle(void);
void doDial(void);
void doTouch(void);
void doSpinner(void);
void doDump(void);
void doFixed(unsigned int);


#define MOSI 5
#define MISO 6
#define SCLK 7
#define CS 4
#define POWER 3

int i, j;
unsigned int x;


int main()
{

  i = openNewHaven(CS, MOSI, MISO, SCLK, POWER);
  
  if (i != 0x7c)
  {
    printf("Display Panel not found!\n");
    while (1)
    {
      _waitms(500);
    }
  }
  
  setDisplay(800, 480);
  
  i = readMemory(CHIP_ID + 1);
  printf("FT8%x\n", i);
  
  j = _read32(REG_CMD_WRITE);
  
  setBrightness(64);
  setRotation(1); // my display was upside down

  CLR();
  DoList();
  cmd(CMD_LOGO);
  
  Wait();
  
  _waitms(2000);
  
  printf("\nCalibrate\n");
  
  CLR();
  DoList();
  Wait();
  cmd(CMD_DLSTART);
  
  cmd(CLEAR_COLOR_RGB(0,255,0));
  cmd(CLEAR(1,1,1));
  cmd(CMD_CALIBRATE);
  cmd(CMD_STOP);
  Wait();

  printf("\n");
  x = _read32(REG_TOUCH_TRANSFORM_A);
  doFixed(x);
  x = _read32(REG_TOUCH_TRANSFORM_B);
  doFixed(x);
  x = _read32(REG_TOUCH_TRANSFORM_C);
  doFixed(x);
  x = _read32(REG_TOUCH_TRANSFORM_D);
  doFixed(x);
  x = _read32(REG_TOUCH_TRANSFORM_E);
  doFixed(x);
  x = _read32(REG_TOUCH_TRANSFORM_F);
  doFixed(x);

  printf("\nCalibration done.\n");

  _waitms(1000);

  doMenu();
  
  while(1)
  {
    i = TouchTag();
    switch (i)
    {
      case 1: doText();
              break;
      case 2: doClock();
              break;
      case 3: doGauge();
              break;
      case 4: doProgress();
              break;
      case 5: doScrollBar();
              break;
      case 6: doSlider();
              break;
      case 7: doToggle();
              break;
      case 8: doDial();
              break;
      case 9: doTouch();
              break;
      case 10: doSpinner();
              break;
      case 11: doDump();
              break;
    }
    
    if (i != 0)
      doMenu();
    _waitms(1000);
  }
}

void CLR()
{
  cmd(CMD_DLSTART);
  cmd(CLEAR_COLOR_RGB(0, 0, 0));
  cmd(CLEAR(1, 1, 1));
}

void doMenu()
{
  CLR();

  cmd(TAG(1));
  CMD_BUTTON(80, 80, 175, 50, 31, 0, "Text");
  cmd(TAG(2));
  CMD_BUTTON(80, 140, 175, 50, 31, 0, "Clock");
  cmd(TAG(3));
  CMD_BUTTON(80, 200, 175, 50, 31, 0, "Gauge");
  cmd(TAG(4));
  CMD_BUTTON(80, 260, 175, 50, 31, 0, "Progress");
  cmd(TAG(5));
  CMD_BUTTON(300, 80, 175, 50, 31, 0, "Scroll");
  cmd(TAG(6));
  CMD_BUTTON(300, 140, 175, 50, 31, 0, "Slider");
  cmd(TAG(7));
  CMD_BUTTON(300, 200, 175, 50, 31, 0, "Toggle");
  cmd(TAG(8));
  CMD_BUTTON(300, 260, 175, 50, 31, 0, "Dial");
  cmd(TAG(9));
  CMD_BUTTON(520, 80, 175, 50, 31, 0, "Touch");
  cmd(TAG(10));
  CMD_BUTTON(520, 140, 175, 50, 31, 0, "Spinner");
  cmd(TAG(11));
  CMD_BUTTON(520, 260, 175, 50, 31, 0, "Dump");
  DoList();
}
  
void doText()
{
  CLR();
  cmd(TAG(15));
  CMD_TEXT(400, 240, 31, OPT_CENTER, "The quick red fox jumps over the lazy bro");
  DoList();
  while(1)
  {
    i = TouchTag();
    if (i == 15)
      return;
    _waitms(250);
  }
}

void doClock()
{
  int h, m, s;
  h = 5;
  m = 45;
  s = 0;
  while(1)
  {
    CLR();
    cmd(TAG(15));
    CMD_CLOCK(400, 240, 200, 0, h, m, s, 0);
    DoList();
    _waitms(998);
    i = TouchTag();
    if (i == 15)
      return;
    if (s++ > 59)
    {
      s = 1;
      if (m++ > 59)
      {
        m = 1;
        if (h++ > 11)
          h = 1;
      }
    }
  }          
}

void doGauge()
{
  j = 0;
  
  while(1)
  {
    CLR();
    cmd(TAG(15));
    CMD_GAUGE(400, 240, 200, 0, 5, 10, j, 100);
    DoList();
    _waitms(998);
    i = TouchTag();
    if (i == 15)
      return;
    if (j++ > 99)
      j = 0;
  }    
}

void doProgress()
{
  j = 0;
  
  while(1)
  {
    CLR();
    cmd(TAG(15));
    CMD_PROGRESS(200, 240, 400, 30, 0, j, 100);
    DoList();
    _waitms(998);
    i = TouchTag();
    if (i == 15)
      return;
    if (j++ > 99)
      j = 0;
  }    
}

void doScrollBar()
{
  j = 0;
  
  while(1)
  {
    CLR();
    cmd(TAG(15));
    CMD_SCROLLBAR(200, 240, 400, 35, 0, j, 5, 100);
    DoList();
    _waitms(998);
    i = TouchTag();
    if (i == 15)
      return;
    if (j++ > 99)
      j = 0;
  }    
}

void doSlider()
{
  j = 0;
  CLR();
  CMD_TRACK(200, 240, 400, 1, 15);
  Wait();
  
  while(1)
  {
    CLR();
    cmd(TAG(15));
    CMD_SLIDER(200, 240, 400, 15, 0, j, 100);
    cmd(TAG(1));
    CMD_BUTTON(600, 50, 120, 40, 31, 0, "Done");
    DoList();
    _waitms(250);
    i = TouchTag();
    if (i == 1)
      return;
    i = Tracker();
    if ((i & 0xff) == 15)
    {
      j = (i >> 16) & 0xffff;
      j = j * 100 / 65535;
    }
  }    
}

void doToggle()
{
  j = 0;
  
  CLR();
  cmd(TAG(15));
  CMD_TOGGLE(350, 200, 100, 31, 0, j, "On\xFFOff");
  DoList();

  while(1)
  {
    i = TouchTag();
    if (i == 15)
    {
      j = 65535 - j;
      CLR();
      cmd(TAG(15));
      CMD_TOGGLE(350, 200, 100, 31, 0, j, "On\xFFOff");
      cmd(TAG(1));
      CMD_BUTTON(600, 50, 120, 40, 31, 0, "Done");
      DoList();
    }
    if (i == 1)
      return;
    while(i != 0)
    {
      i = TouchTag();
      _waitms(250);
    }      
  }    
}

void doDial()
{

  CLR();
  CMD_TRACK(400, 240, 1, 1, 33);
  Wait();
  cmd(TAG(33));
  CMD_DIAL(400, 240, 200, 0, 0x8000);
  DoList();
  
  while (1)
  {
    _waitms(250);
    i = TouchTag();
    if (i == 1)
      return;
    i = Tracker();
    if ((i & 0xff) == 33)
    {
      j = (i >> 16) & 0xffff;
      
      CLR();
      cmd(TAG(33));
      CMD_DIAL(400, 240, 200, 0, j);
      j = j * 360 / 65536 + 180;
      j = j % 360;
      CMD_NUMBER(400, 240, 31, OPT_CENTER, j);
      cmd(TAG(1));
      CMD_BUTTON(600, 50, 120, 40, 31, 0, "Done");
      DoList();
    }
  }    
}

void doTouch()
{

  CLR();
  DoList();
    
  while(1)
  {
    i = TouchScreen();
    if (i != 0x80008000)
    {
      j = i >> 16 & 0xffff;
      i = i & 0xffff;
      printf("X: %d, Y: %d \n", j, i);
      CLR();
      cmd(SAVE_CONTEXT());
      cmd(COLOR_RGB(255,0,255));
      CMD_TEXT(300, 240, 31, OPT_CENTER, "Touch less than 30 to exit");
      cmd(RESTORE_CONTEXT());
      cmd(BEGIN(POINTS));
      cmd(POINT_SIZE(64));
      cmd(VERTEX_TRANSLATE_X(j*16));
      cmd(VERTEX_TRANSLATE_Y(i*16));
      cmd(VERTEX2II(1, 1, 0, 0));
      cmd(END());
      DoList();
      if (j < 30)
        return;
    }
    _waitms(250);
  }  
}

void doSpinner()
{
  CLR();
  CMD_SPINNER(400, 240, 0, 1);
  
  _waitms(1000);
  while(1)
  {
    i = TouchScreen();
    if (i != 0x80008000)
      return;
    _waitms(250);
  }    
}

void doDump()
{
  DumpDL();
  return;
}

void doFixed(unsigned int f)
{
  int whole, fraction;

  whole = f >> 16 & 0x7fff;
  if ((f & 0x80000000) != 0)
    whole = -whole;
  fraction = f & 0xffff;
  printf("%8x %d.%2d\n", f, whole, fraction);
}
