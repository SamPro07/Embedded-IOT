/************************************************************/
/* hal.h                                                    */
/*                                                          */
/* Hardware Abstraction Layer (HAL) definitions             */
/* Name / P-number / Date                                   */
/************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include <Arduino.h>
#include <Wire.h>


#define MPU_addr 0x68       // I2C address of the MPU-6050
#define PWR_Mangement_1 0x6B //pow module address 


#define HAL_GRANTED         A2
#define HAL_DEMAND_INPUT    A6

// Using the built-in LED on the Arduino Nano.
#define HAL_LED             13
#define HAL_ledOn()         digitalWrite(HAL_LED, HIGH)
#define HAL_ledOff()        digitalWrite(HAL_LED, LOW)   

//==============================================================
// HAL_demandRequest()
//
// This function measures the voltage on analogue pin A6
// If this exceeds 1.25V the line is considered to be a 
// logic 1, there is no demand, and the function returns false. 
// Otherwise the line is considered a logic '0', there is
// demand and the function returns true.
//==============================================================
bool HAL_demandRequest();

//==============================================================
// HAL_grantedHigh()
//
// This function implements a safe method of asserting a 
// logic 1 on the GRANTED line
//==============================================================
void HAL_grantedHigh();

//==============================================================
// HAL_grantedLow()
//
// This function implements a safe method of asserting a 
// logic 0 on the GRANTED line
//==============================================================
void HAL_grantedLow();

//==============================================================
// HAL_gpioInit()
//
// This function initializes the GPIO lines. 
//==============================================================
void HAL_gpioInit();

//==============================================================
// HAL_mpu6050Init()
//
// This function contains the initialization code to turn on
// the MPU6050. 
//==============================================================
void HAL_mpu6050Init();

//==============================================================
// HAL_readAccelerometer()
//
// This function reads the X, Y, Z acceleration data from the
// MPU6050 and returns the values via pointers to accx, accy
// and accz respectively. 
//==============================================================
void HAL_readAccelerometer(int *accX, int *accY, int *accZ);

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
char HAL_determineOrientation(char prevOrientation, int accX, int accY, int accZ);

#endif
