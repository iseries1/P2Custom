/**
 * @brief Driver for e-Paper display
 * @author Michael Burmeister
 * @date July 7, 2019
 * @version 1.0
 * 
*/

// commands
#define EPAPER_DRVOUT 0x01
#define EPAPER_BSTSFT 0x0C
#define EPAPER_DEPSLP 0x10
#define EPAPER_DATA   0x11
#define EPAPER_SWREST 0x12
#define EPAPER_TEMPER 0x1A
#define EPAPER_MASTER 0x20
#define EPAPER_UPDATE 0x21
#define EPAPER_UPDAT2 0x22
#define EPAPER_WRAM   0x24
#define EPAPER_WVCOM  0x2C
#define EPAPER_WLUT   0x32
#define EPAPER_DUMMY  0x3A
#define EPAPER_GATE   0x3B
#define EPAPER_BORDER 0x3C
#define EPAPER_SRAMX  0x44
#define EPAPER_SRAMY  0x45
#define EPAPER_SRAMXC 0x4E
#define EPAPER_SRAMYC 0x4F
#define EPAPER_NOP    0xFF
