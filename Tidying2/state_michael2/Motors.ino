

static int motorSpeed;
static int motorDir;
static int turnSpeed;
static int turnDir;



void initMotors (void) {
  motorSpeed = 0;
  motorDir = MOTOR_FORWARDS;
  turnSpeed = 0;
  turnDir = MOTOR_CW;
}



// Updates a single sensor using a MAF

void fullStop (void) {
  leftValue = MOTOR_ZERO_VALUE;
  rightValue = MOTOR_ZERO_VALUE;
  currentError.error = 0;
}



// Drives the robot straight - with PID
void straight () {
  
  leftValue = MOTOR_ZERO_VALUE + motorDir*(motorSpeed + followState.returnState()*currentError.scaleError(5));
  rightValue = MOTOR_ZERO_VALUE + motorDir*(motorSpeed - followState.returnState()*currentError.scaleError(5));
  
}




// Turns the robot
void turn (void) {
 
  leftValue = MOTOR_ZERO_VALUE + turnDir*turnSpeed;
  rightValue = MOTOR_ZERO_VALUE - turnDir*turnSpeed;
  
}




void driveRobot () {
  if (driveState.returnState() == STATE_STRAIGHT) {
    straight();
  }
  if (driveState.returnState() == STATE_TURNING) {      
    turn();
  } 
  if (driveState.returnState() == STATE_STOPPED) {
    fullStop();
  }
  
  checkClipping();
  leftWheel.write(leftValue);
  rightWheel.write(rightValue);
}





// Setting various parameters

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
  
  
  
  
  // Ensures the value being read to the motor is not greater than the maximum
void checkClipping(void) {
  if (leftValue > (MOTOR_ZERO_VALUE + MOTOR_FULL_SPEED)) {
    leftValue = MOTOR_ZERO_VALUE + MOTOR_FULL_SPEED;
  }
  if (leftValue < (MOTOR_ZERO_VALUE - MOTOR_FULL_SPEED)) {
    leftValue = MOTOR_ZERO_VALUE - MOTOR_FULL_SPEED;
  }
  if (rightValue > (MOTOR_ZERO_VALUE + MOTOR_FULL_SPEED)) {
    rightValue = MOTOR_ZERO_VALUE + MOTOR_FULL_SPEED;
  }
  if (rightValue < (MOTOR_ZERO_VALUE - MOTOR_FULL_SPEED)) {
    rightValue = MOTOR_ZERO_VALUE - MOTOR_FULL_SPEED;
  }
}

