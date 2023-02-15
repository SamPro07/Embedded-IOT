////////////////////////////////////////////////////////////////
// Task 1
// NodeMCU (ESP8266) Resource Manager
// Name / Date
////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "Concurrent.h"
#include "hal.h"


#define NoTriggerNotGranted  0   // idle state
//#define TriggerNotGranted    1   // trigger detected, 
#define TriggerIamMaster     1   // we are master after a successful claim
#define NoTriggerGranted     2   // we do not want to be a master any more but
                                 // the GRANTED line is still active

// Global variable for storing the resource manager state
int  rmstate;

// Global variable for storing the trigger value
bool trigger;

Concurrent mainTask; // concurrency object 

//==============================================================
// resourceManager()
//
// This function implements the resource manager FSM based on
//    a) the current state (rmstate)
//    b) the 'trigger' variable
//    c) the state of GRANTED determined using the
//       HAL_isGranted() function
// The LED should be illuminated in the IamMaster state and
// should be extinguished for all other states.
//==============================================================
void resourceManager()
{
  // TO-DO: Implement your optimized FSM
  switch (rmstate)
  {
    case NoTriggerNotGranted:
      HAL_demandHigh();
    if (trigger & !HAL_isGranted())
    {
      rmstate = NoTriggerGranted;
    }
    else if (trigger & HAL_isGranted())
    {
      rmstate = TriggerIamMaster;
    }
    else {
      HAL_demandHigh();
      rmstate = NoTriggerNotGranted;
    }
      break;
    case TriggerIamMaster:
      HAL_demandLow();
     if (trigger & !HAL_isGranted())
     {
         rmstate = NoTriggerGranted;
     }
     else if (trigger & HAL_isGranted())
     {
      
      rmstate = TriggerIamMaster;
     }
     else {
      rmstate = NoTriggerNotGranted;
     }
      break;
    case NoTriggerGranted:
      HAL_demandHigh();
    if (!trigger & !HAL_isGranted())
    {
      rmstate = NoTriggerNotGranted;
    }
    else if (trigger & HAL_isGranted()) 
    {
       rmstate = TriggerIamMaster;
    }
    else
    {
      rmstate = NoTriggerGranted; 
    }
      break;
  }
}


void setup() {
  // Initialize the GPIO
  // TO-DO
  HAL_gpioInit();
  // Initialize rmstate and trigger to sensible values.
  // TO-DO  
  rmstate = NoTriggerNotGranted;
  trigger = false;

  // Begin the serial port for orientation results
  Serial.begin(115200);

  // Initialize the wire library with SDA on D6, and SCL on D7 of NodeMCU
  // TO-DO
   Wire.begin(D6, D7);

  // Start the main task
  // TO-DO
  mainTask.setRunning(true);
  mainTask.setModuleDelay(1);
}


void loop() 
{

  // The Resource Manager has the highest priority and must
  // run every time the loop() function is executed.
  // TO-DO

    resourceManager();

  // The main task requires some form of concurrent code module
  // capable of implementing an FSM containing 4 states.
  // This will require a module delay of 1ms.
  // State 0: Set a delay time of 13 ms, then move immediately to state 1
  // State 1: Stay here until the delay time has elapsed,
  //          activate the trigger, then move to state 2
  // State 2: Stay here until the Resource Manager state (rmstate) reaches 
  //          the IamMaster state. Then move to state 3.
  // State 3: Read the orientation data from the Nano, disable the trigger,
  //          output the data to the serial port, and return back to state 0.
  // TO-DO
  
  if (mainTask.actionTask())
  {
    static int state = 0;
    static unsigned long referencetime;
    referencetime = millis();

    switch (state)
    {
      case 0:
        mainTask.setModuleDelay(13);
        state = 1;
        break;
      case 1:
        if ((millis() - referencetime) >= 13) {
          trigger = true;
          state = 2;
        }
        break;
      case 2:
        if (rmstate == TriggerIamMaster){ state = 3;}
        else { state = 2; }
        break;
      case 3:
        Wire.requestFrom(8, 13);
        while (Wire.available()) {
          char arduinoData = Wire.read();
          Serial.println(arduinoData);
        }
        trigger = false;
        state = 0;
        break;
    }
  }

}
