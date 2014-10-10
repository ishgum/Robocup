

#define WINGS_TUCK 1
#define WINGS_OUT 90
#define WINGS_KNOCK 160

int wingWait = false;

void checkWings(void) {
    if (limitRightWing.switchState == SWITCH_ON) {
       rightWing.setDesiredAngle(WINGS_TUCK);
       wingWait = true;
    }
    
    
    else if (limitLeftWing.switchState == SWITCH_ON) {
       leftWing.setDesiredAngle(WINGS_TUCK);
       wingWait = true;
    }
    
    else if (navigationState.returnState() == STATE_WALL_FOLLOW) {
      if (followState.returnState() == STATE_RIGHT_WALL) {
       rightWing.setDesiredAngle(WINGS_TUCK);
       leftWing.setDesiredAngle(WINGS_OUT);
      }
      if (followState.returnState() == STATE_LEFT_WALL) {
        leftWing.setDesiredAngle(WINGS_TUCK);
        rightWing.setDesiredAngle(WINGS_OUT);
    }
    }
    
    else if (navigationState.returnState() == STATE_EVACUATE) {
      rightWing.setDesiredAngle(WINGS_TUCK);
      leftWing.setDesiredAngle(WINGS_TUCK);
      Serial.println("Here");
    }
    
    else if (wingWait == true) {
      if (wait(4, 5000)) {
        wingWait = false;
      }
    }
    
    else {
      rightWing.setDesiredAngle(WINGS_OUT);
      leftWing.setDesiredAngle(WINGS_OUT);
    }
}

