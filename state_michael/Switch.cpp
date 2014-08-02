
#include "Switch.h"

Switch::Switch(int port)
{
  int _port = port;
  int _onCount = 0;
  int _offCount = 0;
  int switchState = false;
}


// Updates a single sensor using a MAF

void Switch::updateSwitch () {
   if (analogRead(_port) != LOW) {
     _offCount = 0;
     _onCount += 1;
  }
  if (analogRead(_port) == LOW) {
     _onCount = 0;
     _offCount += 1;
  }
  
  if (_onCount == ON_BUFFER) {
    switchState = true;
  }
  if (_offCount == OFF_BUFFER) {
    switchState = false;
  }
}
