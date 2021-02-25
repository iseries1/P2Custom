/**
 * @brief HX8357 320x480 display panel
 * @author Michael Burmeister
 * @date March 11, 2019
 * @version 1.0
*/

#include "simpletools.h"
#include "HX8357.h"
#include "libHX8357/HX8357Reg.h"


#define LITE 22
#define RST 21
#define DC 20
#define CS 19
#define MOSI 18
#define MISO 17
#define CLK 16

int i;
unsigned long PCNT;

int main()
{
  pause(1000);
  print("Starting\n");
  i = HX8357_open(CLK, MISO, MOSI, CS, DC, RST, LITE);
  
  print("Power: %x\n", i);

  if ((i & 0x08) == 0)
    HX8357_sleepOn(0);

  // Is display on
  if ((i & 0x04) == 0)
    HX8357_displayOn(1);
  
  i = readCmd(HX8357_RDMADCTL);
  print("Control: %x\n", i);

  HX8357_rotation(1);

  HX8357_cls(HX8357_BLACK);
  
  HX8357_writeSStr(10, 10, "Hello World");
  
  HX8357_writeStr(10, 110, "Hello World");
  
  HX8357_writeXStr(10, 160, "Hello World");
  
  HX8357_drawBox(50, 50, 100, 100, HX8357_color(255,0,0));
  
  HX8357_displayMode(0);
  
  print("Done\n");
  
  while(1)
  {
    pause(1000);
    
  }  
}
