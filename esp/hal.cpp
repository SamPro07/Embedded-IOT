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
  pinMode(HAL_GRANTED, INPUT_PULLUP);
  pinMode(HAL_DEMAND, INPUT_PULLUP);
}


//==============================================================
// HAL_isGranted()
//
// This function checks the status of the GRANTED line.
// If this line is low, it means the resource has been
// granted and the function returns true.
// Otherwise, the resource has not been granted and the
// function returns false.
//==============================================================
bool HAL_isGranted()
{
  return (!digitalRead(HAL_GRANTED));
}

//==============================================================
// HAL_demandHigh()
//
// This function implements a safe method of asserting a 
// logic 1 on the DEMAND line
//==============================================================
void HAL_demandHigh()
{
  pinMode(HAL_DEMAND, INPUT_PULLUP);
}

//==============================================================
// HAL_demandLow()
//
// This function implements a safe method of asserting a 
// logic 0 on the DEMAND line
//==============================================================
void HAL_demandLow() 
{
  digitalWrite(HAL_DEMAND, LOW);
  pinMode(HAL_DEMAND, OUTPUT);
}
