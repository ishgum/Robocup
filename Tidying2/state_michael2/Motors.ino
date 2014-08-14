

int motorSpeed;
int motorDir;
int turnSpeed;
int turnDir;

void initMotors (void) {
  motorSpeed = 0;
  motorDir = MOTOR_FORWARDS;
  turnSpeed = 0;
  turnDir = MOTOR_CW;
}


// Updates a single sensor using a MAF

void fullStop (void) {
  leftWheel.write(MOTOR_ZERO_VALUE);
  rightWheel.write(MOTOR_ZERO_VALUE);
  motorSpeed = 0;
}




void straight (signed int error) {
  
  leftWheel.write(MOTOR_ZERO_VALUE + motorDir*(motorSpeed + error));
  rightWheel.write(MOTOR_ZERO_VALUE + motorDir*(motorSpeed - error));
}


void turn (void) {
 
  leftWheel.write(MOTOR_ZERO_VALUE + turnDir*turnSpeed);
  rightWheel.write(MOTOR_ZERO_VALUE - turnDir*turnSpeed);
  
}


void setMotorSpeed (int newSpeed) {
  if (newSpeed > 0 && newSpeed < 100) {
    motorSpeed = (newSpeed * MOTOR_FULL_SPEED)/100;
  }
}


void setMotorDir (int newDir) {
  if (newDir == MOTOR_FORWARDS) {
    motorDir = MOTOR_FORWARDS;
  }
  if (newDir == MOTOR_BACKWARDS) {
    motorDir = MOTOR_BACKWARDS;
  }
}


void setTurnSpeed (int newSpeed) {
  if (newSpeed > 0 && newSpeed < 100) {
    turnSpeed = (newSpeed * MOTOR_FULL_SPEED)/100;
  }
}


void setTurnDir (int newDir) {
  if (newDir == MOTOR_CW) {
    turnDir = MOTOR_CW;
  }
  if (newDir == MOTOR_CCW) {
    turnDir = MOTOR_CCW;
  }
}




void driveRobot (State state, int straightError) {
  if (driveState.returnState() == STATE_STRAIGHT) {
    straight(straightError);
  }
  
  if (driveState.returnState() == STATE_TURNING) {      
    turn();
  } 
}
  
