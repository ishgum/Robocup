#include "Gate.h"

Gate::Gate(void){
	angle = 0;
}


bool Gate::lowerGate(void){
  if(angle > ANGLE_MIN){
    gateServo.write(angle);
    angle -= 1;
    gate_down = false;
  }else{
    gate_down = true;
  }
  return gate_down;
}


bool Gate::raiseGate(void){
  if(angle < ANGLE_MAX){
    gateServo.write(angle);
    angle += 1;
    gate_down = true;
  }else{
    gate_down = false;
  }
  return gate_down;
}
