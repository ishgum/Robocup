

#define WINGS_TUCK 1
#define WINGS_OUT 70
#define WINGS_KNOCK 130
#define LEFT_SIDE_ERROR 15

#define WAIT_BUFFER 5

int wingWait = false;
bool weightFound = false;

int tuckWaitRight = 0;
int tuckWaitLeft = 0;

void checkWings(void) {
    weightFound = sideWhisker.detect(DETECT_THRESHOLD_SIDE);
    
    
    if (limitRightWing.switchState == SWITCH_ON) {
      if (!weightFound || (weightFound == -1)) {
          tuckWaitRight++;
      }
      else if (weightFound) {
         rightWing.setDesiredAngle(WINGS_KNOCK);
         wingWait = true;
         tuckWaitRight = 0;
      }
      if (tuckWaitRight >= WAIT_BUFFER) {
        rightWing.setDesiredAngle(WINGS_TUCK);
         wingWait = true;
         tuckWaitRight = 0;
      }
    }
    
    else if (limitLeftWing.switchState == SWITCH_ON) {
       if (!weightFound || (weightFound == -1)) {
           tuckWaitLeft++;
       }
      else if (weightFound) {
       leftWing.setDesiredAngle(WINGS_KNOCK - (LEFT_SIDE_ERROR));
       wingWait = true;
       tuckWaitLeft = 0;
       }
       if (tuckWaitLeft >= WAIT_BUFFER) {
         leftWing.setDesiredAngle(WINGS_TUCK);
         wingWait = true;
         tuckWaitLeft = 0;
       }
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

