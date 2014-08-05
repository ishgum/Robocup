
#include "Motors.h"

Motors::Motors(void)
{
  leftValue = 0;
  rightValue = 0;
}


// Updates a single sensor using a MAF

void Motors::fullStop (void) {
  leftValue = ZERO_VALUE;
  rightValue = ZERO_VALUE;
}


void Motors::drive (signed int error, signed int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  int desiredDir = dir;
  
  leftValue = (ZERO_VALUE + dir*(speedMotors + error));
  rightValue = (ZERO_VALUE + dir*(speedMotors - error));
}


void Motors::turn (unsigned int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  leftValue = (ZERO_VALUE + dir*speedMotors);
  rightValue = (ZERO_VALUE - dir*speedMotors);
}
