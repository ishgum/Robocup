
#include "State.h"

#define STOP_DISTANCE_FRONT 400
#define STOP_DISTANCE_SIDES 350

#define GO_DISTANCE_FRONT 150
#define GO_DISTANCE_SIDES 150

#define MAX_OBJ_DIST 300

int evacuateStep = 0;

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

void findWeight (void) {
   if(!infaFront.findWall(MAX_OBJ_DIST) && infaBottom.findWall(MAX_OBJ_DIST)){
      navigationState.updateState(STATE_HONING);
   } 
}

// High level function which moves the robot around the arena
void navigateRobot (void) {
  //Serial.println(navigationState.returnState());
  switch (navigationState.returnState()) {
      
    case STATE_EVACUATE:
      if (evacuateStep == 0) {
        fullStop();
        //delay(1000);
        if (tick % 1000 == 0) {
          evacuateStep = 1;
        }
      }
      
      else if (evacuateStep == 1) {
        changeToStraightState();
        setMotorDir(MOTOR_BACKWARDS);
        if (tick % 500 == 0) {
          evacuateStep = 2;
          setMotorDir(MOTOR_FORWARDS);
          determineWallFollow();
        }
      }
      
      else if (evacuateStep == 2) {
        changeToTurnState();
        if (tick % 500 == 0) {
          changeToSearchingState();
          infaLeft.ignore = false;
          infaRight.ignore = false;
          infaFront.ignore = false;
        }
      }
    break;
  
    case STATE_WALL_FOLLOW:
      updateErrors();
      navigateCorner();
    break;
  
    case STATE_SEARCHING:
      if (driveState.returnState() == STATE_STRAIGHT) {
        currentSensor = determineWallFollow(); 
      }
      avoidWall();
      
      //findWeight();
    break;
  
    case STATE_COLLECTING:
      changeToSearchingState(); 
    break;
    
    case STATE_HONING:
      fullStop();
    break;
  }
  driveRobot(driveState, currentError.error/5);
}

