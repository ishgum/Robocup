
#include "PID.h"

PID::PID(int desired)
{
  desiredValue = desired;
  sweepDirection = 0;
  error = 0;
  scaledError = 0;
  ignore = false;
}


// Updates a single sensor using a MAF

float PID::findError (float currentValue) {
  if (ignore == false) {
    error = desiredValue - currentValue;
  }
}


void PID::setDesiredValue(float newValue) {
  //Serial.println(desiredValue);
  desiredValue = newValue;
  //Serial.println(desiredValue);
}


float PID::currentDesiredValue(void) {
  return desiredValue;
}


void PID::scaleError (signed int scale) {
  scaledError = error*scale;
}

