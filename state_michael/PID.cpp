
#include "Arduino.h"
#include "PID.h"

PID::PID(void)
{
  signed int _desiredValue = 0;
  signed int error = 0;
}



void PID::findError (int currentValue) {
  error = desiredValue - currentValue;
}
