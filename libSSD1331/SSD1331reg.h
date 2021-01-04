/**
 * @file ssd1331reg.h
 * @brief Oled display register values
 * @author Michael Burmeister
 * @date December 11, 2018
 * @version 1.0
 * 
*/


#define TFTWIDTH  96
#define TFTHEIGHT 64


// SSD1331 Commands
#define SSD1331_DRAWLINE        0x21
#define SSD1331_DRAWRECT        0x22
#define SSD1331_COPY            0x23
#define SSD1331_CLEAR           0x25
#define SSD1331_FILL            0x26
#define SSD1331_SCROLLSETUP     0x27
#define SSD1331_SCROLLSTOP      0x2E
#define SSD1331_SCROLLSTART     0x2F
#define SSD1331_SETCOLUMN       0x15
#define SSD1331_SETROW          0x75
#define SSD1331_CONTRASTA       0x81
#define SSD1331_CONTRASTB       0x82
#define SSD1331_CONTRASTC       0x83
#define SSD1331_MASTERCURRENT   0x87
#define SSD1331_SETREMAP        0xA0
#define SSD1331_STARTLINE       0xA1
#define SSD1331_DISPLAYOFFSET   0xA2
#define SSD1331_NORMALDISPLAY   0xA4
#define SSD1331_DISPLAYALLON    0xA5
#define SSD1331_DISPLAYALLOFF   0xA6
#define SSD1331_INVERTDISPLAY   0xA7
#define SSD1331_SETMULTIPLEX    0xA8
#define SSD1331_DIMCONTRAST     0xAB
#define SSD1331_SETMASTER       0xAD
#define SSD1331_DISPLAYDIM      0xAC
#define SSD1331_DISPLAYOFF      0xAE
#define SSD1331_DISPLAYON       0xAF
#define SSD1331_POWERMODE       0xB0
#define SSD1331_PRECHARGE       0xB1
#define SSD1331_CLOCKDIV        0xB3
#define SSD1331_PRECHARGEA      0x8A
#define SSD1331_PRECHARGEB      0x8B
#define SSD1331_PRECHARGEC      0x8C
#define SSD1331_PRECHARGELEVEL  0xBB
#define SSD1331_VCOMH           0xBE
