
#include "State.h"


#define FOLLOW_DISTANCE 350
#define STOP_DISTANCE_FRONT 400
#define STOP_DISTANCE_SIDES 400

#define GO_DISTANCE_FRONT 200
#define GO_DISTANCE_SIDES 150



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
      if(whisker.detect(SLOW)){
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
}





void findTurn (Sensors sensor, int distance) {
  sensor.ignore = true;
  if (sensor.findWall(distance)) {
    changeToTurnState();
    sensor.ignore = false;
  }
}




void findStraight (Sensors sensor, int distance) {
  if (!sensor.findWall(distance) && sensor.ignore == false) {
    changeToStraightState();
  }
}






void navigateCorner (void) {
   if (driveState.returnState() == STATE_STRAIGHT) {
      findTurn(infaFront, STOP_DISTANCE_FRONT);
    }
  else if (driveState.returnState() == STATE_TURNING) {
      findStraight(infaFront, GO_DISTANCE_FRONT); 
  }
  
}





void avoidWall (void) {
    if (driveState.returnState() == STATE_STRAIGHT) {
      findTurn(infaFront, STOP_DISTANCE_FRONT);
      findTurn(infaLeft, STOP_DISTANCE_SIDES);
      findTurn(infaRight, STOP_DISTANCE_SIDES);
    }
    else if (driveState.returnState() == STATE_TURNING) {
      findStraight(infaFront, GO_DISTANCE_FRONT); 
      findStraight(infaLeft, GO_DISTANCE_SIDES); 
      findStraight(infaRight, GO_DISTANCE_SIDES); 
    }
}


