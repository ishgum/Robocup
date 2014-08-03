
#include "Switch.h"

Switch::Switch(int port)
{
  _port = port;
  _onCount = 0;
  _offCount = 0;
  switchState = SWITCH_OFF;
}


// Updates a single sensor using a MAF

void Switch::updateSwitch () {
   if (analogRead(_port) != 0) {
     _offCount = 0;
     _onCount += 1;
  }
  if (analogRead(_port) == 0) {
     _onCount = 0;
     _offCount += 1;
  }
  
  if (_onCount == ON_BUFFER) {
    switchState = SWITCH_ON;
  }
  if (_offCount == OFF_BUFFER) {
    switchState = SWITCH_OFF;
  }
}
