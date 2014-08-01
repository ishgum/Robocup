
#include "Arduino.h"
#include "PID.h"

PID::PID(void)
{
  float desiredValue = 0;
  float error = 0;
}


// Updates a single sensor using a MAF

float PID::findError (float currentValue) {
  error = desiredValue - currentValue;
}
