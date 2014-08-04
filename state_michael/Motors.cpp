
#include "Motors.h"

Motors::Motors(void)
{
  leftValue = 0;
  rightValue = 0;
  
  _zero = 90;
  _fullSpeed = 90;
}


// Updates a single sensor using a MAF

void Motors::fullStop (void) {
  leftValue = _zero;
  rightValue = _zero;
}


void Motors::drive (signed int error, signed int speedPercent, signed int dir) {
  unsigned int speedMotors = (_fullSpeed*speedPercent)/100;
  if (speedMotors > _fullSpeed) {
    speedMotors = _fullSpeed;
  }
  int desiredDir = dir;
  
  leftValue = (_zero + dir*(speedMotors + error));
  rightValue = (_zero + dir*(speedMotors - error));
}


void Motors::turn (unsigned int speedPercent, signed int dir) {
  unsigned int speedMotors = (_fullSpeed*speedPercent)/100;
  if (speedMotors > _fullSpeed) {
    speedMotors = _fullSpeed;
  }
  leftValue = (_zero - dir*speedMotors);
  rightValue = (_zero + dir*speedMotors);
}
