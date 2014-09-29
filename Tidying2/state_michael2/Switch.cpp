
#include "Switch.h"

Switch::Switch(int port, int inputDefaultOff)
{
  _port = port;
  _onCount = 0;
  _offCount = 0;
  switchState = SWITCH_OFF;
  defaultOff = inputDefaultOff;
}


// Updates a single sensor using a MAF

void Switch::updateSwitch () {
   if (analogRead(_port) > defaultOff) {
     _offCount = 0;
     _onCount += 1;
  }
  else {
     _onCount = 0;
     _offCount += 1;
  }
  
  if (_onCount == ON_BUFFER) {
    switchState = SWITCH_ON;
  }
  else if (_offCount == OFF_BUFFER) {
    switchState = SWITCH_OFF;
  }
  else {
    switchState = SWITCH_WAITING;
  }
}


