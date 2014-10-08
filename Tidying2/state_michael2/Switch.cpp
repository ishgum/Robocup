
#include "Switch.h"

Switch::Switch(int port, int inputPulse, int inputMode)
{
  _port = port;
  _onCount = 0;
  _offCount = 0;
  switchState = SWITCH_OFF;
  pulse = inputPulse;
  _mode = inputMode;
}


// Updates a single sensor using a MAF

void Switch::updateSwitch () {
  if (_mode == ANALOG) {
    currentRead = analogRead(_port);
  }
  if (_mode == DIGITAL) {
    currentRead = !digitalRead(_port);
  }
  
   if (currentRead > 0) {
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
  else if (pulse == PULSE_ON) {
    switchState = SWITCH_WAITING;
  }
}


