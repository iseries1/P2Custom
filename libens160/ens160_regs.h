/**
 * @brief Register Addresses for ENS160 device
 * 
 */

#define ENS160_PARTID     0x00

#define ENS160_OP_MODE    0x10

#define ENS160_CONFIG     0x11

#define ENS160_COMMAND	  0x12
// All commands must be issued when device is idle. 

#define ENS160_TEMP_IN     0x13
#define ENS160_RH_IN       0x15
#define ENS160_DEVICE_STATUS 0x20

#define ENS160_DATA_AQI    0x21

#define ENS160_DATA_TVOC   0x22
// TVOC Data - shares register with ethanol data

#define ENS160_DATA_ETOH   0x22
// Ethanol Data - shares register with TVOC data

#define ENS160_DATA_ECO2   0x24
// CO2 Data

#define ENS160_DATA_T      0x30

#define ENS160_DATA_RH     0x32

#define ENS160_DATA_MISR   0x38

// General Purpose Write registers
#define ENS160_GPR_WRITE   0x40

// General Purpose Read registers
#define ENS160_GPR_READ    0x48

