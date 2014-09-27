
#include "Switch.h"

Switch::Switch(int inputPort)
{
  port = inputPort;
  onCount = 0;
  offCount = 0;
  switchState = SWITCH_OFF;
}


void Switch::Init (void){
  pinMode(port, INPUT); 
}

// Updates a single sensor using a MAF

bool Switch::updateSwitch (void) {
  if (analogRead(port) != 0) {
     offCount = 0;
     onCount += 1;
  }
  if (analogRead(port) == 0) {
     onCount = 0;
     offCount += 1;
  }
  
  if (onCount >= ON_BUFFER) {
    switchState = SWITCH_ON;
  }
  if (offCount >= OFF_BUFFER) {
    switchState = SWITCH_OFF;
  }
  return switchState;
}
