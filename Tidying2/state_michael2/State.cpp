
#include "State.h"

State::State(void)
{
  powerState = STATE_OFF;
  navigationState = STATE_SEARCHING;
  driveState = STATE_STOPPED;
  followState = STATE_RIGHT_WALL;
  init = false;
}



void State::updatePowerState (int changeState) {
  if (changeState == STATE_ON) {
    powerState = STATE_ON;
  }
  if (changeState == STATE_OFF) {
    powerState = STATE_OFF;
  }
}



void State::updateNavigationState (int changeState) {
  if (powerState == STATE_ON) {
    if (changeState == STATE_WALL_FOLLOW) {
     navigationState = STATE_WALL_FOLLOW;
    }
    if (changeState == STATE_SEARCHING) {
      navigationState = STATE_SEARCHING;
    }
    if (changeState == STATE_EVACUATE) {
      navigationState = STATE_EVACUATE;
    }
  }
}



void State::updateDriveState (int changeState) {
  if (powerState == STATE_ON) {
    if (changeState == STATE_STOPPED) {
     driveState = STATE_STOPPED;
    }
    if (changeState == STATE_STRAIGHT) {
      driveState = STATE_STRAIGHT;
    }
    if (changeState == STATE_TURNING) {
      driveState = STATE_TURNING;
    }
  }
  if (changeState == STATE_OFF) {
    driveState = STATE_STOPPED;
  }
}



void State::updateFollowState (int changeState) {
  if (changeState == STATE_RIGHT_WALL) {
   followState = STATE_RIGHT_WALL;
  }
  if (changeState == STATE_LEFT_WALL) {
    followState = STATE_LEFT_WALL;
  }
}
