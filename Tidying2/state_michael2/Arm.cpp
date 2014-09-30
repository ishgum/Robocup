

#include "Arm.h"

/* Functions to move the sweeper arms */


Arm::Arm(bool input_loc, int defaultAngle)
{
        loc = input_loc;
        bool moving = false;
        desiredAngle = defaultAngle;
}


void Arm::setDesiredAngle (int newAngle) {
  if (moving == false) {
  desiredAngle = newAngle;
  }
}


void Arm::sweep (Servo armServo) {
  if (desiredAngle > currentAngle) {
    currentAngle += 1;
  }
  else if (desiredAngle < currentAngle) {
    currentAngle -= 1;
  }
  
  if (loc == LEFT_SIDE) {      
      armServo.write(currentAngle);
  }
  else {
      armServo.write(180-currentAngle);
  }
}


bool Arm::checkMoving(void){
  if (desiredAngle == currentAngle) {
    moving = false;
  }
  else {
    moving = true;
  }
  return moving;
}

