
#include "PID.h"

PID::PID(void)
{
  desiredValue = 0;
  desiredSweep = 0;
  sweepDirection = 0;
  error = 0;
}


// Updates a single sensor using a MAF

float PID::findError (float currentValue) {
  error = (desiredValue + desiredSweep) - currentValue;
}
