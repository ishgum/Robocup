

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
    
    if (changeState == STATE_ON) {
        initRobot();
    }
    
    else if (changeState == STATE_OFF) {
        leftArm.setDesiredAngle(0);
        rightArm.setDesiredAngle(0);
        gateArm.setDesiredAngle(110);
        rightWing.setDesiredAngle(0);
        leftWing.setDesiredAngle(0);
    }
    
    else if (changeState == STATE_STOPPED) {
    
    }
    
    else if (changeState == STATE_STRAIGHT) {
        frontSensor.write(SENSOR_MIDDLE);
    }
    
    else if (changeState == STATE_TURNING) {
      if (navigationState.returnState() == STATE_SEARCHING) {
          currentSensor = determineWallFollow(); 
      }
        
        sensorTurnAngle = SENSOR_MIDDLE - followState.returnState()*SENSOR_ANGLE;
        frontSensor.write(sensorTurnAngle);
    }
    
    else if (changeState == STATE_WALL_FOLLOW) {
        
    }
    
    else if (changeState == STATE_SEARCHING) {
        leftError.error = 0;
        rightError.error = 0;
        currentError.error = 0;
    }
    
    else if (changeState == STATE_EVACUATE) {
        driveState.updateState(STATE_STOPPED);
        evacuateStep = 0;
    }
}
