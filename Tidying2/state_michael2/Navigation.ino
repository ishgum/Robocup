
#include "State.h"

#define STOP_DISTANCE_FRONT 450
#define STOP_DISTANCE_SIDES 400

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



// If the sensor reads a wall within a certain distance it will change the state to turning
Sensors findTurn (Sensors sensor, int distance) {
  sensor.ignore = true;
  if (sensor.findWall(distance)) {
    driveState.updateState(STATE_TURNING);
    sensor.ignore = false;
  }
  return sensor;
}




// If the robot is turning, and the sensor reads that the wall is no longer within a certain distance, the robot will begin moving straight
void findStraight (Sensors sensor, int distance) {
  if (!sensor.findWall(distance) && sensor.ignore == false) {
    driveState.updateState(STATE_STRAIGHT);
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


void evacuateArea(void) {
  int randomTime = 0;
    if (evacuateStep == 0) {      // Drive straight backwards
            driveState.updateState(STATE_STRAIGHT);
            setMotorDir(MOTOR_BACKWARDS);
            randomTime = random(100, 500);
            evacuateStep = 1;
          }
          
    else if (evacuateStep == 1 && wait(1, randomTime)) {    // Turn
      setMotorDir(MOTOR_FORWARDS);
      determineWallFollow();
      driveState.updateState(STATE_TURNING);
      evacuateStep = 2;
      
    }
    
    else if (evacuateStep == 2 && wait(1, 500)) {    // Change back to searching state
        navigationState.updateState(STATE_SEARCHING);
        infaLeft.ignore = false;
        infaRight.ignore = false;
        infaFront.ignore = false;
    }
}





void infraredLocate (void) {
  float linearTop = 30431 * pow(infaFront.filteredRead, -1.169);
  float linearBottom = 30431 * pow(infaBottom.filteredRead, -1.169);
   if((linearTop - linearBottom + 30.0) > 50.0 && driveState.returnState() == STATE_STRAIGHT){
      powerState.updateState(STATE_OFF);
   } 
}



int wiggle = 0;
// High level function which moves the robot around the arena
void navigateRobot (void) {
  //Serial.println(navigationState.returnState());
  switch (navigationState.returnState()) {
      
    case STATE_EVACUATE:
      evacuateArea();
    break;
  
  
    case STATE_WALL_FOLLOW:
      currentError.findError(currentSensor.filteredRead);
      navigateCorner();
      
    break;
  
    case STATE_SEARCHING:      
      if (driveState.returnState() == STATE_STRAIGHT) {
        if (followState.returnState() == STATE_RIGHT_WALL && wait(5, 2000)) {
          followState.updateState(STATE_LEFT_WALL);
          Serial.println("wiggle1");
        }
      
        else if (followState.returnState() == STATE_LEFT_WALL && wait(5, 2000)) {
          followState.updateState(STATE_RIGHT_WALL);
          Serial.println("wiggle2");
          }
      }
      
      avoidWall();
    break;
  
  
    case STATE_COLLECTING:
      navigationState.updateState(STATE_SEARCHING);
    break;
    
    
    case STATE_HONING:
      fullStop();
    break;
  }
  
  
  if (limitFront.switchState == SWITCH_ON && navigationState.returnState() != STATE_EVACUATE) {
        navigationState.updateState(STATE_EVACUATE);
  }
}

