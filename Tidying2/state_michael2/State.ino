

#include "State.h"

State::State(int defaultState)
{
  _default = defaultState;
  init = false;
  _currentState = defaultState;
}


void State::setToDefault(void) {
  _currentState = _default;
}

void State::updateState (int changeState) {
   initStates(changeState);
  _currentState = changeState;
}

int State::returnState (void) {
  return _currentState;
}




void initStates (int changeState) {
  switch (changeState) {
    
    case STATE_ON:
        initRobot();
    break;
    
    case STATE_OFF:
        driveState.updateState(STATE_STOPPED);
        leftArm.setDesiredAngle(0);
        rightArm.setDesiredAngle(0);
        gateArm.setDesiredAngle(120);
        rightWing.setDesiredAngle(90);
        leftWing.setDesiredAngle(90);
    break;
    
    case STATE_STOPPED:
    
    break;
    
    case STATE_STRAIGHT:
        frontSensor.write(SENSOR_MIDDLE);
    break;
    
    case STATE_TURNING:
        sensorTurnAngle = SENSOR_MIDDLE + followState.returnState()*SENSOR_ANGLE;
        frontSensor.write(sensorTurnAngle);
    break;
    
    case STATE_WALL_FOLLOW:
        
    break;
    
    case STATE_SEARCHING:
        leftError.error = 0;
        rightError.error = 0;
        currentError.error = 0;
    break;
    
    case STATE_EVACUATE:
        driveState.updateState(STATE_STOPPED);
        rightWing.setDesiredAngle(40);
        leftWing.setDesiredAngle(40);
        evacuateStep = 0;
    break;
  }
}
