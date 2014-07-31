
#include "Arduino.h"
#include "State.h"

State::State(void)
{
  int powerState = OFF;
  int navigationState = WALL_FOLLOW;
  int driveState = STOPPED;
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