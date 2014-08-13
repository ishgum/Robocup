
#include "State.h"




void findTurn (Sensors sensor, int distance) {
  sensor.ignore = true;
  if (sensor.findWall(distance)) {
    initTurnState();
    state.updateDriveState(STATE_TURNING);
    sensor.ignore = false;
  }
}


void findStraight (Sensors sensor, int distance) {
  if (!sensor.findWall(distance) && sensor.ignore == false) {
    initStraightState();
    state.updateDriveState(STATE_STRAIGHT);
  }
}




void navigateCorner (void) {
   if (state.driveState == STATE_STRAIGHT) {
      findTurn(infaFront, 400);
    }
  else if (state.driveState == STATE_TURNING) {
      findStraight(infaFront, 200);  

  }
  
}



void avoidWall (void) {
    if (state.driveState == STATE_STRAIGHT) {
      findTurn(infaFront, 400);
      findTurn(infaLeft, 400);
      findTurn(infaRight, 400);
    }
    else if (state.driveState == STATE_TURNING) {
      findStraight(infaFront, 200); 
      findStraight(infaLeft, 150); 
      findStraight(infaRight, 150); 
    }
}



void initStraightState (void) {
  frontSensor.write(SENSOR_MIDDLE);
}


void initTurnState (void) {
  int sensorTurnAngle = SENSOR_MIDDLE + state.followState*SENSOR_ANGLE;
  frontSensor.write(sensorTurnAngle);
}
