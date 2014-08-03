
#include "State.h"

State::State(void)
{
  powerState = OFF;
  navigationState = WALL_FOLLOW;
  driveState = STOPPED;
  followState = RIGHT_WALL;
}



void State::updatePowerState (int changeState) {
  if (changeState == ON) {
    powerState = ON;
  }
  if (changeState == OFF) {
    powerState = OFF;
  }
}



void State::updateNavigationState (int changeState) {
  if (powerState == ON) {
    if (changeState == WALL_FOLLOW) {
     navigationState = WALL_FOLLOW;
    }
    if (changeState == SEARCHING) {
      navigationState = SEARCHING;
    }
  }
}



void State::updateDriveState (int changeState) {
  if (powerState == ON) {
    if (changeState == STOPPED) {
     driveState = STOPPED;
    }
    if (changeState == STRAIGHT) {
      driveState = STRAIGHT;
    }
    if (changeState == TURNING) {
      driveState = TURNING;
    }
  }
  if (changeState == OFF) {
    driveState = STOPPED;
  }
}



void State::updateFollowState (int changeState) {
  if (changeState == RIGHT_WALL) {
   navigationState = RIGHT_WALL;
  }
  if (changeState == LEFT_WALL) {
    navigationState = LEFT_WALL;
  }
}
