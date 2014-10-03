
#include "PID.h"

PID::PID(int desired)
{
  desiredValue = desired;
  error = 0;
  scaledError = 0;
}


// Updates a single sensor using a MAF

float PID::findError (float currentValue) {
  error = desiredValue - currentValue;
}


void PID::setDesiredValue(float newValue) {
  desiredValue = newValue;
}



signed int PID::scaleError (signed int scale) {
  scaledError = error/scale;
  return scaledError;
}

