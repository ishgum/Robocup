
#include "Motors.h"

Motors::Motors(void)
{
  leftValue = 0;
  rightValue = 0;
  _motorSpeed = 0;
  _motorDir = FORWARDS;
  _turnSpeed = 0;
  _turnDir = MOTOR_CW;
}


// Updates a single sensor using a MAF

void Motors::fullStop (void) {
  leftValue = ZERO_VALUE;
  rightValue = ZERO_VALUE;
  _motorSpeed = 0;
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



void Motors::straight (signed int error) {
  
  leftValue = (ZERO_VALUE + _motorDir*(_motorSpeed + error));
  rightValue = (ZERO_VALUE + _motorDir*(_motorSpeed - error));

  checkClipping();
}


void Motors::turn (void) {
 
  leftValue = (ZERO_VALUE + _turnDir*_turnSpeed);
  rightValue = (ZERO_VALUE - _turnDir*_turnSpeed);
  
  checkClipping();
}


void Motors::setMotorSpeed (int newSpeed) {
  if (newSpeed > 0 && newSpeed < 100) {
    _motorSpeed = (newSpeed * FULL_SPEED)/100;
  }
}


void Motors::setMotorDir (int newDir) {
  if (newDir == FORWARDS) {
    _motorDir = FORWARDS;
  }
  if (newDir == BACKWARDS) {
    _motorDir = BACKWARDS;
  }
}

void Motors::setTurnSpeed (int newSpeed) {
  if (newSpeed > 0 && newSpeed < 100) {
    _turnSpeed = (newSpeed * FULL_SPEED)/100;
  }
}


void Motors::setTurnDir (int newDir) {
  if (newDir == MOTOR_CW) {
    _turnDir = MOTOR_CW;
  }
  if (newDir == MOTOR_CCW) {
    _turnDir = MOTOR_CCW;
  }
}




void Motors::driveRobot (State state, int straightError) {
  if (state.driveState == STRAIGHT) {
    straight(straightError);
  }
  
  if (state.driveState == TURNING) {      
    turn();
  } 
}
  
