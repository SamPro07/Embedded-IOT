/************************************************************/
/* hal.cpp                                                  */
/*                                                          */
/* Hardware Abstraction Layer (HAL) implementation          */
/* Name / P-number / Date                                   */
/************************************************************/

#include "hal.h"


//==============================================================
// HAL_gpioInit()
//
// This function initializes the GPIO lines. 
//==============================================================
void HAL_gpioInit()
{
  pinMode(HAL_LED, OUTPUT);
  pinMode(HAL_GRANTED, OUTPUT);
}

//==============================================================
// HAL_demandRequest()
//
// This function measures the voltage on analogue pin A6
// If this exceeds 1.25V the line is considered to be a 
// logic 1, there is no demand, and the function returns false. 
// Otherwise the line is considered a logic '0', there is
// demand and the function returns true.
//==============================================================
bool HAL_demandRequest()
{
  return (!(analogRead(HAL_DEMAND_INPUT) >> 8));
}

//==============================================================
// HAL_grantedHigh()
//
// This function implements a safe method of asserting a 
// logic 1 on the GRANTED line
//==============================================================
void HAL_grantedHigh()
{
  pinMode(HAL_GRANTED, INPUT);
}

//==============================================================
// HAL_grantedLow()
//
// This function implements a safe method of asserting a 
// logic 0 on the GRANTED line
//==============================================================
void HAL_grantedLow() 
{
  digitalWrite(HAL_GRANTED, LOW);
  pinMode(HAL_GRANTED, OUTPUT);
}

//==============================================================
// HAL_mpu6050Init()
//
// This function contains the initialization code to turn on
// the MPU6050. 
//==============================================================
void HAL_mpu6050Init()
{
  // TO-DO
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr);
  Wire.write(PWR_Mangement_1); // registers all the setting for all the registers
  Wire.write(0); // wakes up the mpu 6050 module
  Wire.endTransmission(true);
}

//==============================================================
// HAL_readAccelerometer()
//
// This function reads the X, Y, Z acceleration data from the
// MPU6050 and returns the values via pointers to accx, accy
// and accz respectively. 
//==============================================================
void HAL_readAccelerometer(int *accX, int *accY, int *accZ)
{
  // TO-DO
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // accX adress 
  Wire.endTransmission(true);
  Wire.requestFrom(MPU_addr,6,true);
  
  if(Wire.available() >= 6) 
  {
    *accX = Wire.read() << 8|Wire.read(); // sets the pointer variable to accX to read the registers 0x3B and 0x3C
    *accY = Wire.read() << 8|Wire.read(); // sets the pointer variable to accY to read the registers 0x3D and 0x3E
    *accZ = Wire.read() << 8|Wire.read(); // sets the pointer variable to accZ to read the registers 0x3F and 0x40
  }
   
}

//==============================================================
// HAL_determineOrientation()
//
// This function uses the X, Y and Z components of acceleration
// via parameters: accX, accY and accZ respectively and 
// determines the orientation.
// This function also takes another parameter: prevOrientation
// containing the previous orientation value. If an orientation
// value cannot be determined, the previous value will be used.
// This function returns a single character representing the
// orientation: 'F' (flat), 'b' (base-up), 'l' (left-portrait)
// 'r' (right portrait), 'L' (Landscape), 'U' (upside-down
// landscape).  
//==============================================================
char HAL_determineOrientation(char prevOrientation, int accX, int accY, int accZ)
{
  char orientation;
  // TO-DO: Initialize orientation

  // TO-DO: Calculate orientation
  if (abs(accX) < 300 && abs(accY) > -300 && abs(accZ) < 14000)
  {
   orientation = 'F';
  }
  else if (abs(accX) < 4000 && abs(accY) < 14000 && abs(accZ) > -14000 ) 
  {
    orientation = 'l';
  }
  else if (abs(accX) < 4000 && abs(accY) > -18000 && abs(accZ) < 3000)
  {
   orientation = 'r'; 
  }
  else if (abs(accX) > -16000 && abs(accY) > -700 && abs(accZ) > -3500)
  {
   orientation = 'L'; 
  }
  else if (abs(accX) < 18000 && abs(accY) > -700 && abs(accZ) > -7000)
  {
   orientation = 'U'; 
  }
  else if (abs(accX) < 2600 && 100 > abs(accY) > -200 && abs(accZ) > -20000)
  {
    orientation = 'b';
  }
  
  return orientation;
}
