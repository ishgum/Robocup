
#include "State.h"

#define STOP_DISTANCE_FRONT 400
#define STOP_DISTANCE_SIDES 400

#define GO_DISTANCE_FRONT 200
#define GO_DISTANCE_SIDES 150


<<<<<<< HEAD
// Updates the error for the angle as well as for the wall following

Sensors determineWallFollow (void) {
    
  if (infaLeft.filteredRead <= infaRight.filteredRead) {
    followState.updateState(STATE_RIGHT_WALL);
    setTurnDir(MOTOR_CCW);
    return infaRight;
  }
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    followState.updateState(STATE_LEFT_WALL);
    setTurnDir(MOTOR_CW);
    return infaLeft;
  }
}


// Updates errors for the left and right sensors, allowing PID control to be implemented
void updateErrors (void) {
    currentError.findError(currentSensor.filteredRead);
=======

void navigateRobot (void) {
  switch (navigationState.returnState()) {
      
    case STATE_EVACUATE:
      changeToSearchingState();
    break;
  
    case STATE_WALL_FOLLOW: 
      updateErrors();
      navigateCorner();
      determineWallFollow();
      if (followState.returnState() == STATE_LEFT_WALL) {
      driveRobot(driveState, leftError.error/5);
      }
      if (followState.returnState() == STATE_RIGHT_WALL) {
      driveRobot(driveState, rightError.error/5);
      }
    break;
  
    case STATE_SEARCHING: 
      avoidWall();
      if(whisker.detect()){
        waving = false;
        fullStop();
        //state.updateNavigationState(ALIGNING); 
      }
      //detector.waveArm(waving, detectorArm, tick);
    break;
  
    case STATE_COLLECTING:
      changeToSearchingState(); 
    break;
  }
>>>>>>> origin/master
}


// If the sensor reads a wall within a certain distance it will change the state to turning
Sensors findTurn (Sensors sensor, int distance) {
  sensor.ignore = true;
  if (sensor.findWall(distance)) {
    changeToTurnState();
    sensor.ignore = false;
  }
  return sensor;
}


// If the robot is turning, and the sensor reads that the wall is no longer within a certain distance, the robot will begin moving straight
void findStraight (Sensors sensor, int distance) {
  if (!sensor.findWall(distance)) {
    changeToStraightState();
  }
}



// Implements the findTurn and findStraight functions 
void navigateCorner (void) {
   if (driveState.returnState() == STATE_STRAIGHT) {
      infaFront = findTurn(infaFront, STOP_DISTANCE_FRONT);
    }
  else if (driveState.returnState() == STATE_TURNING) {
      findStraight(infaFront, GO_DISTANCE_FRONT); 
  }
  
}


// Avoids walls using all three distance sensors
void avoidWall (void) {
    if (driveState.returnState() == STATE_STRAIGHT) {
      infaFront = findTurn(infaFront, STOP_DISTANCE_FRONT);
      infaLeft = findTurn(infaLeft, STOP_DISTANCE_SIDES);
      infaRight = findTurn(infaRight, STOP_DISTANCE_SIDES);
    }
    else if (driveState.returnState() == STATE_TURNING) {
      findStraight(infaFront, GO_DISTANCE_FRONT); 
      findStraight(infaLeft, GO_DISTANCE_SIDES); 
      findStraight(infaRight, GO_DISTANCE_SIDES); 
    }
}


// High level function which moves the robot around the arena
void navigateRobot (void) {
  switch (navigationState.returnState()) {
      
    case STATE_EVACUATE:
      changeToSearchingState();
    break;
  
    case STATE_WALL_FOLLOW:
      updateErrors();
      navigateCorner();
    break;
  
    case STATE_SEARCHING: 
      avoidWall();
    break;
  
    case STATE_COLLECTING:
      changeToSearchingState(); 
    break;
  }
  driveRobot(driveState, currentError.error/5);
}

