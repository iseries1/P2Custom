/**
 * @brief Library for EM7180 sensor fusion
 * @author Michael Burmeister
 * @date January 25, 2019
 * @version 1.0
 * 
*/

#define _DEBUG

#include <propeller.h>
#include "simpletools.h"
#include "em7180reg.h"
#include "em7180.h"

void _writeByte(unsigned char , unsigned char , unsigned char );
unsigned char _readByte(unsigned char , unsigned char);
void _readBytes(unsigned char , unsigned char , unsigned char , unsigned char *);


i2c *_em7180;

union {
    long i;
    float f;
  } u;
char _buffer[32];


int Em7180_open(int clk, int sda)
{
  int i;
  _em7180 = i2c_open(_em7180, clk, sda, 1); 
  i = _readByte(EM7180_ADDRESS, EM7180_ROMVersion1);
  i = i << 8 | _readByte(EM7180_ADDRESS, EM7180_ROMVersion2);
  return i;
}

short Em7180_version()
{
  int i;
  i = _readByte(EM7180_ADDRESS, EM7180_RAMVersion1);
  i = i << 8 | _readByte(EM7180_ADDRESS, EM7180_RAMVersion2);
  return i;
}


int Em7180_status()
{
  int i;
  i = _readByte(EM7180_ADDRESS, EM7180_EventStatus);
  i = i | _readByte(EM7180_ADDRESS, EM7180_AlgorithmStatus) << 8;
  i = i | _readByte(EM7180_ADDRESS, EM7180_PassThruStatus) << 16;
  i = i | _readByte(EM7180_ADDRESS, EM7180_RunStatus) << 24;
  return i;
}

short Em7180_productID()
{
  short i;
  i = _readByte(EM7180_ADDRESS, EM7180_ProductID);
  i = i << 8 | _readByte(EM7180_ADDRESS, EM7180_RevisionID);
  return i;
}

char Em7180_sensors()
{
  char i;
  
  i = _readByte(EM7180_ADDRESS, EM7180_FeatureFlags);
  return i;
}    

char Em7180_error()
{
  
  return _readByte(EM7180_ADDRESS, EM7180_ErrorRegister);
}

void Em7180_reset(char t)
{
  _writeByte(EM7180_ADDRESS, EM7180_ResetRequest, t);
  pause(500);
}

void Em7180_loadfw()
{
  int i;
  
  i = Em7180_sensors();

#ifdef _DEBUG
  if (i & 0x01)
    __builtin_printf("Barometer installed\n");
  if (i & 0x02)
    __builtin_printf("Humidity installed\n");
  if (i & 0x04)
    __builtin_printf("Temperature installed\n");
  if (i & 0x08)
    __builtin_printf("Custom Sensor\n");
  if (i & 0x10)
    __builtin_printf("Second Custom Sensor\n");
  if (i & 0x20)
    __builtin_printf("Third Custom Sensor\n");
  _waitms(1000);

  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if ((i & 0x01) != 0)
    __builtin_printf("EEPROM detected on the sensor bus\n");
  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if ((i & 0x02) != 0)
    __builtin_printf("EEPROM uploaded config file\n");
  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if ((i & 0x04) != 0)
    __builtin_printf("EEPROM CRC incorrect\n");
  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if ((i & 0x08) != 0)
    __builtin_printf("EM7180 in initialized state\n");
  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if ((i & 0x10) != 0)
    __builtin_printf("No EEPROM detected\n");
#endif
    
  int count = 0;
  while ((i & 0x01) == 0)
  {
    _writeByte(EM7180_ADDRESS, EM7180_ResetRequest, 0x01);
    _waitms(500);
#ifdef _DEBUG
    i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
    if ((i & 0x01) != 0)
      __builtin_printf("EEPROM detected on the sensor bus\n");
    i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
    if ((i & 0x02) != 0)
      __builtin_printf("EEPROM uploaded config file\n");
    i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
    if ((i & 0x04) != 0)
      __builtin_printf("EEPROM CRC incorrect\n");
    i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
    if ((i & 0x08) != 0)
      __builtin_printf("EM7180 in initialized state\n");
#endif
    i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
    if ((i & 0x10) != 0)
      __builtin_printf("No EEPROM detected\n");
    if (count > 9)
      break;
  }      
  
  i = _readByte(EM7180_ADDRESS, EM7180_SentralStatus);
  if((i & 0x04) == 0x00)
    __builtin_printf("EEPROM upload successful\n");
}

void Em7180_setupdefault()
{
  Em7180_setup(0x03, 0x03, 0x08, 0x7d0, 0x3e8, 1, 0x64, 0x14, 0x14, 0x32);
}

void Em7180_setup(char accBW, char gyroBW, short accFS, short gyroFS, short magFS, char QRtDiv, char magRT, char accRT, char gyroRT, char baroRT)
{
  unsigned short EM7180_mag_fs, EM7180_acc_fs, EM7180_gyro_fs; // EM7180 sensor full scale ranges
  char param[4];
  int i;
  
  // Enter EM7180 initialized state
  _writeByte(EM7180_ADDRESS, EM7180_HostControl, 0x00); // set SENtral in initialized state to configure registers
  _writeByte(EM7180_ADDRESS, EM7180_PassThruControl, 0x00); // make sure pass through mode is off
  _writeByte(EM7180_ADDRESS, EM7180_HostControl, 0x01); // Force initialize
  _writeByte(EM7180_ADDRESS, EM7180_HostControl, 0x00); // set SENtral in initialized state to configure registers
  
  //Setup LPF bandwidth (BEFORE setting ODR's)
  _writeByte(EM7180_ADDRESS, EM7180_ACC_LPF_BW, accBW);   // accBW = 3 = 41Hz
  _writeByte(EM7180_ADDRESS, EM7180_GYRO_LPF_BW, gyroBW); // gyroBW = 3 = 41Hz
  
  // Set accel/gyro/mag desired ODR rates
  _writeByte(EM7180_ADDRESS, EM7180_QRateDivisor, QRtDiv); // quat rate = gyroRt/(1 QRTDiv)
  _writeByte(EM7180_ADDRESS, EM7180_MagRate, magRT); // 0x64 = 100 Hz
  _writeByte(EM7180_ADDRESS, EM7180_AccelRate, accRT); // 200/10 Hz, 0x14 = 200 Hz
  _writeByte(EM7180_ADDRESS, EM7180_GyroRate, gyroRT); // 200/10 Hz, 0x14 = 200 Hz
  _writeByte(EM7180_ADDRESS, EM7180_BaroRate, 0x80 | baroRT);  // set enable bit and set Baro rate to 25 Hz, rate = baroRt/2, 0x32 = 25 Hz
  
  // Configure operating mode
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // read scale sensor data
  // Enable interrupt to host upon certain events
  // choose host interrupts when any sensor updated (0x40), new gyro data (0x20), new accel data (0x10),
  // new mag data (0x08), quaternions updated (0x04), an error occurs (0x02), or the SENtral needs to be reset(0x01)
  _writeByte(EM7180_ADDRESS, EM7180_EnableEvents, 0x07);
  // Enable EM7180 run mode
  _writeByte(EM7180_ADDRESS, EM7180_HostControl, 0x01); // set SENtral in normal run mode
  _waitms(100);
  
 // EM7180 parameter adjustments
  __builtin_printf("Beginning Parameter Adjustments\n");
  
  // Read sensor default FS values from parameter space
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x4A); // Request to read parameter 74
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); // Request parameter transfer process
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  while(i!=0x4A)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  param[0] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte0);
  param[1] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte1);
  param[2] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte2);
  param[3] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte3);
  
  EM7180_mag_fs = ((short)(param[1]<<8) | param[0]);
  EM7180_acc_fs = ((short)(param[3]<<8) | param[2]);
  __builtin_printf("Magnetometer Default Full Scale Range: +/-%duT\n", EM7180_mag_fs);
  __builtin_printf("Accelerometer Default Full Scale Range: +/-%dg\n", EM7180_acc_fs);
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x4B); // Request to read  parameter 75
  
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  while(i!=0x4B)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  param[0] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte0);
  param[1] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte1);
  param[2] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte2);
  param[3] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte3);
  
  EM7180_gyro_fs = ((short)(param[1]<<8) | param[0]);
  __builtin_printf("Gyroscope Default Full Scale Range: +/-%ddps\n", EM7180_gyro_fs);
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //End parameter transfer
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // re-enable algorithm
  
  //Disable stillness mode for balancing robot application
  Em7180_setintparam(0x49, 0x00);
  
  //Write desired sensor full scale ranges to the EM7180
  Em7180_setmagaccfs(magFS, accFS); // 1000 uT == 0x3E8, 8 g == 0x08
  Em7180_setgyrofs(gyroFS); // 2000 dps == 0x7D0
  
  // Read sensor new FS values from parameter space
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x4A); // Request to read  parameter 74
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); // Request parameter transfer process
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  while(i!=0x4A)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  param[0] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte0);
  param[1] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte1);
  param[2] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte2);
  param[3] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte3);
  
  EM7180_mag_fs = ((short)(param[1]<<8) | param[0]);
  EM7180_acc_fs = ((short)(param[3]<<8) | param[2]);
  __builtin_printf("Magnetometer New Full Scale Range: +/-%duT\n", EM7180_mag_fs);
  __builtin_printf("Accelerometer New Full Scale Range: +/-%dg\n", EM7180_acc_fs);
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x4B); // Request to read  parameter 75
  
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  while (i != 0x4B)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  param[0] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte0);
  param[1] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte1);
  param[2] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte2);
  param[3] = _readByte(EM7180_ADDRESS, EM7180_SavedParamByte3);
  
  EM7180_gyro_fs = ((short)(param[1]<<8) | param[0]);
  __builtin_printf("Gyroscope New Full Scale Range: +/-%ddps\n", EM7180_gyro_fs);
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //End parameter transfer
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // re-enable algorithm

  
  // Read EM7180 status
  i = _readByte(EM7180_ADDRESS, EM7180_RunStatus);
  if ((i & 0x01) == 0x01)
    __builtin_printf(" EM7180 run status = normal mode\n");
  i = _readByte(EM7180_ADDRESS, EM7180_AlgorithmStatus);
  if ((i & 0x01) == 0x01)
    __builtin_printf(" EM7180 standby status\n");
  if ((i & 0x02) == 0x02)
    __builtin_printf(" EM7180 algorithm slow\n");
  if ((i & 0x04) == 0x04)
    __builtin_printf(" EM7180 in stillness mode\n");
  if ((i & 0x08) == 0x08)
    __builtin_printf(" EM7180 mag calibration completed\n");
  if ((i & 0x10) == 0x10)
    __builtin_printf(" EM7180 magnetic anomaly detected\n");
  if ((i & 0x20) == 0x20)
    __builtin_printf(" EM7180 unreliable sensor data\n");
  
  i = _readByte(EM7180_ADDRESS, EM7180_PassThruStatus);
  if ((i & 0x01) == 0x01)
    __builtin_printf(" EM7180 in passthru mode!\n");
  
  i = _readByte(EM7180_ADDRESS, EM7180_EventStatus);
  if ((i & 0x01) == 0x01)
    __builtin_printf(" EM7180 CPU reset\n");
  if ((i & 0x02) == 0x02)
    __builtin_printf(" EM7180 Error\n");
  if ((i & 0x04) == 0x04)
    __builtin_printf(" EM7180 new quaternion result\n");
  if ((i & 0x08) == 0x08)
    __builtin_printf(" EM7180 new mag result\n");
  if ((i & 0x10) == 0x10)
    __builtin_printf(" EM7180 new accel result\n");
  if ((i & 0x20) == 0x20)
    __builtin_printf(" EM7180 new gyro result\n"); 
  
  _waitms(1000); // give some time to read the screen
  
  // Check sensor status
  i = _readByte(EM7180_ADDRESS, EM7180_SensorStatus);
  __builtin_printf(" EM7180 sensor status = %x\n", i);
  if ((i & 0x01) == 0x01)
    __builtin_printf("Magnetometer not acknowledging!\n");
  if ((i & 0x02) == 0x02)
    __builtin_printf("Accelerometer not acknowledging!\n");
  if ((i & 0x04) == 0x04)
    __builtin_printf("Gyro not acknowledging!\n");
  if ((i & 0x10) == 0x10)
    __builtin_printf("Magnetometer ID not recognized!\n");
  if ((i & 0x20) == 0x20)
    __builtin_printf("Accelerometer ID not recognized!\n");
  if ((i & 0x40) == 0x40)
    __builtin_printf("Gyro ID not recognized!\n");
  
  i = _readByte(EM7180_ADDRESS, EM7180_ActualMagRate);
  __builtin_printf("Actual MagRate = %d Hz\n", i);
  
  i = 10 * _readByte(EM7180_ADDRESS, EM7180_ActualAccelRate);
  __builtin_printf("Actual AccelRate = %d Hz\n", i);
  
  i = 10 * _readByte(EM7180_ADDRESS, EM7180_ActualGyroRate);
  __builtin_printf("Actual GyroRate = %d Hz\n", i);
  
  i = _readByte(EM7180_ADDRESS, EM7180_ActualBaroRate);
  __builtin_printf("Actual BaroRate = %d Hz\n", i);
}

void Em7180_setgyrofs(short fs)
{
  int i;
  
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte0, fs & 0xff); //Gyro LSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte1, (fs >> 8)); //Gyro MSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte2, 0); //Unused
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte3, 0); //Unused
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0xCB); //Parameter 75; 0xCB is 75 decimal with the MSB set high to indicate a paramter write processs
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); //Request parameter transfer procedure

  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge); //Check the parameter acknowledge register and loop until the result matches parameter request byte
  while (i != 0xcb)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //Parameter request = 0 to end parameter transfer process
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // Re-start algorithm
}

void Em7180_setmagaccfs(short mag, short acc)
{
  int i;
  
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte0, (mag & 0xff)); //Mag LSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte1, (mag >> 8)); //Mag MSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte2, (acc & 0xff)); //Acc LSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte3, (acc >> 8)); //Acc MSB
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0xCA); //Parameter 74; 0xCA is 74 decimal with the MSB set high to indicate a paramter write processs
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); //Request parameter transfer procedure
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge); //Check the parameter acknowledge register and loop until the result matches parameter request byte
  while (i != 0xCA)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //Parameter request = 0 to end parameter transfer process
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // Re-start algorithm
}

void Em7180_setintparam(char p, int v)
{
  int i;
  
  p = p | 0x80; //Parameter is the decimal value with the MSB set high to indicate a paramter write processs
  
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte0, v); //Param LSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte1, (v >> 8));
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte2, (v >> 16));
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte3, (v >> 24)); //Param MSB
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, p);
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); //Request parameter transfer procedure
  
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge); //Check the parameter acknowledge register and loop until the result matches parameter request byte
  while (i != p)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //Parameter request = 0 to end parameter transfer process
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // Re-start algorithm

}  

void Em7180_floatparam(char p, float v)
{
  long i;
  
  i = Em7180_long(v);
  p = p | 0x80; //Parameter is the decimal value with the MSB set high to indicate a paramter write processs
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte0, i); //Param LSB
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte1, i >> 8);
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte2, i >> 16);
  _writeByte(EM7180_ADDRESS, EM7180_LoadParamByte3, i >> 24); //Param MSB
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, p);
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x80); //Request parameter transfer procedure
  
  i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge); //Check the parameter acknowledge register and loop until the result matches parameter request byte
  while (i != p)
  {
    i = _readByte(EM7180_ADDRESS, EM7180_ParamAcknowledge);
  }
  _writeByte(EM7180_ADDRESS, EM7180_ParamRequest, 0x00); //Parameter request = 0 to end parameter transfer process
  _writeByte(EM7180_ADDRESS, EM7180_AlgorithmControl, 0x00); // Re-start algorithm
}
  
float Em7180_float(long value)
{
  u.i = value;
  return u.f;    
}

long Em7180_long(float value)
{
  u.f = value;
  return u.i;
}

void Em7180_readquaternions(float *Qs)
{
  long i;
  
  _readBytes(EM7180_ADDRESS, EM7180_QX, 16, _buffer); // Read the sixteen raw data registers into data array
for (i=0;i<24;i++)
	__builtin_printf("%x ", _buffer[i]);

  i = _buffer[12] | _buffer[13] << 8 | _buffer[14] << 16 | _buffer[15] << 24;
  Qs[0] = Em7180_float(i);
  i = _buffer[0] | _buffer[1] << 8 | _buffer[2] << 16 | _buffer[3] << 24;
  Qs[1] = Em7180_float(i);
  i = _buffer[4] | _buffer[5] << 8 | _buffer[6] << 16 | _buffer[7] << 24;
  Qs[2] = Em7180_float(i);
  i = _buffer[8] | _buffer[9] << 8 | _buffer[10] << 16 | _buffer[11] << 24;
  Qs[3] = Em7180_float(i);
}

void Em7180_readaccelerometer(short *v)
{
  _readBytes(EM7180_ADDRESS, EM7180_AX, 6, _buffer); // Read the six raw data registers into data array
  v[0] = _buffer[0] | _buffer[1] << 8; // Turn the MSB and LSB into a signed 16-bit value
  v[1] = _buffer[2] | _buffer[3] << 8;
  v[2] = _buffer[4] | _buffer[5] << 8;
}

void Em7180_readgyro(short *v)
{
  _readBytes(EM7180_ADDRESS, EM7180_GX, 6, _buffer); // Read the six raw data registers sequentially into data array
  v[0] = _buffer[0] | _buffer[1] << 8; // Turn the MSB and LSB into a signed 16-bit value
  v[1] = _buffer[2] | _buffer[3] << 8;
  v[2] = _buffer[4] | _buffer[5] << 8;
}

void Em7180_readmagnetometer(short *v)
{
  _readBytes(EM7180_ADDRESS, EM7180_MX, 6, _buffer); // Read the six raw data registers sequentially into data array
  v[0] = _buffer[0] | _buffer[1] << 8; // Turn the MSB and LSB into a signed 16-bit value
  v[1] = _buffer[2] | _buffer[3] << 8;
  v[2] = _buffer[4] | _buffer[5] << 8;
}
  
/* basic read write funcitons
 */

/**
 * @brief I2C read write routines
 * @param address device address to write to
 * @param subAddress device register or location on device
 * @param data to write
*/
void _writeByte(unsigned char address, unsigned char subAddress, unsigned char data)
{
  int i;

  i2c_out(_em7180, address, subAddress, 1, &data, 1);
}

/**
 * @brief I2C read routine
 * @param address address of device
 * @param subAddress device register or location on device
 * @return byte value
*/
uint8_t _readByte(unsigned char address, unsigned char subAddress)
{
  int i;
  uint8_t data;

  i2c_in(_em7180, address, subAddress, 1, &data, 1);
  return data;
}

/**
 * @brief I2C read routine
 * @param address of device
 * @param subAddress device register or location on device
 * @param cnt number of bytes to read
 * @param dest returned byte of data from device
*/
void _readBytes(unsigned char address, unsigned char subAddress, unsigned char cnt, unsigned char *dest)
{
  i2c_in(_em7180, address, subAddress, 1, dest, cnt);
}
