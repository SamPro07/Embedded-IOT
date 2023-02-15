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


// Handshaking lines
#define HAL_GRANTED   D2
#define HAL_DEMAND    D1

// I2C lines
#define HAL_SDA       D6
#define HAL_SCL       D7

// Using the built-in LED on the ESP8266.
#define HAL_LED       D4   
#define HAL_ledOn()   digitalWrite(HAL_LED, LOW);
#define HAL_ledOff()  digitalWrite(HAL_LED, HIGH);


//==============================================================
// HAL_isGranted()
//
// This function checks the status of the GRANTED line.
// If this line is low, it means the resource has been
// granted and the function returns true.
// Otherwise, the resource has not been granted and the
// function returns false.
//==============================================================
bool HAL_isGranted();


//==============================================================
// HAL_demandHigh()
//
// This function implements a safe method of asserting a 
// logic 1 on the DEMAND line
//==============================================================
void HAL_demandHigh();


//==============================================================
// HAL_demandLow()
//
// This function implements a safe method of asserting a 
// logic 0 on the DEMAND line
//==============================================================
void HAL_demandLow();


//==============================================================
// HAL_gpioInit()
//
// This function initializes the GPIO lines. 
//==============================================================
void HAL_gpioInit();


#endif
