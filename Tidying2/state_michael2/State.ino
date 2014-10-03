

#include "State.h"

State::State(int defaultState)
{
  _default = defaultState;
  init = false;
  _currentState = defaultState;
}


void State::setToDefault(void) {
  _currentState = _default;
}

void State::updateState (int changeState) {
  _currentState = changeState;
}

int State::returnState (void) {
  return _currentState;
}




void changeToStraightState (void) {
  frontSensor.write(SENSOR_MIDDLE);
  driveState.updateState(STATE_STRAIGHT);
}


void changeToTurnState (void) {
  int sensorTurnAngle = SENSOR_MIDDLE + followState.returnState()*SENSOR_ANGLE;
  frontSensor.write(sensorTurnAngle);
  driveState.updateState(STATE_TURNING);
}


