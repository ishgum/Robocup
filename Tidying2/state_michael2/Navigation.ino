
#include "State.h"


#define FOLLOW_DISTANCE 250
#define STOP_DISTANCE_FRONT 400
#define STOP_DISTANCE_SIDES 400

#define GO_DISTANCE_FRONT 200
#define GO_DISTANCE_SIDES 150


// Updates errors for the left and right sensors, allowing PID control to be implemented
void updateErrors (void) {
    rightError.findError(infaRight.filteredRead, FOLLOW_DISTANCE);
    leftError.findError(infaLeft.filteredRead, FOLLOW_DISTANCE);
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
  if (!sensor.findWall(distance) && sensor.ignore == false) {
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
      fullStop();
      //state.updateNavigationState(ALIGNING); 
    break;
  
    case STATE_COLLECTING:
      changeToSearchingState(); 
    break;
  }
  driveRobot(driveState, leftError.error/3);
}

