
#include "Motors.h"

Motors::Motors(void)
{
  leftValue = 0;
  rightValue = 0;
  motorSpeed = 50;
}


// Updates a single sensor using a MAF

void Motors::fullStop (void) {
  leftValue = ZERO_VALUE;
  rightValue = ZERO_VALUE;
  motorSpeed = 0;
}

void Motors::checkClipping(void) {
  if (leftValue > (ZERO_VALUE + FULL_SPEED)) {
    leftValue = ZERO_VALUE + FULL_SPEED;
  }
  if (leftValue < (ZERO_VALUE - FULL_SPEED)) {
    leftValue = ZERO_VALUE - FULL_SPEED;
  }
  if (rightValue > (ZERO_VALUE + FULL_SPEED)) {
    rightValue = ZERO_VALUE + FULL_SPEED;
  }
  if (rightValue < (ZERO_VALUE - FULL_SPEED)) {
    rightValue = ZERO_VALUE - FULL_SPEED;
  }
}



void Motors::drive (signed int error, signed int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;
  
  leftValue = (ZERO_VALUE + dir*(speedMotors + error));
  rightValue = (ZERO_VALUE + dir*(speedMotors - error));
  //Serial.println(leftValue);
  checkClipping();
}


void Motors::turn (unsigned int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;

  leftValue = (ZERO_VALUE + dir*speedMotors);
  rightValue = (ZERO_VALUE - dir*speedMotors);
  
  checkClipping();
}


void Motors::setMotorSpeed (int newSpeed) {
  if (newSpeed > 0 && newSpeed < 100) {
    motorSpeed = newSpeed;
  }
}
  
