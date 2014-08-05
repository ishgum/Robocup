#include <Servo.h> 
#include "Motors.h"
#include "Switch.h"
#include "Sensors.h"
#include "State.h"
#include "PID.h"


#define DIGITAL_OUT_POWER 49

State state;

Motors motors;
Servo leftWheel;
Servo rightWheel;
Servo frontSensor;

Switch powerSwitch(3);

Sensors infaFront(4);
Sensors infaLeft (0);
Sensors infaRight (1);

PID wallError;

unsigned long tick = 0;

int currentState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);
  
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)
  frontSensor.attach(10);
  
  wallError.setDesiredValue(400);
}



void loop() {
  powerSwitch.updateSwitch();
  infaFront.updateSensor();
  infaRight.updateSensor();
  
  wallError.findError(infaRight.filteredRead);
  Serial.println(state.powerState);
  
  if (powerSwitch.switchState == SWITCH_ON) {
    state.powerState = ON;
    state.driveState = STRAIGHT;
    }
  if (powerSwitch.switchState == SWITCH_OFF) {
    state.powerState = OFF;
  }
  
  if (state.powerState == ON) {
    if (state.driveState == STRAIGHT) {
      frontSensor.write(105);
      int currentError = wallError.error/10;
      motors.drive(currentError, 50, FORWARDS);
      if (infaFront.filteredRead > 500) {
        state.updateDriveState(TURNING);
      }
    }
    if (state.driveState == TURNING) {
      frontSensor.write(60);
      motors.turn(50, ANTI_CLOCKWISE);
      if (infaFront.filteredRead < 250) {
        state.updateDriveState(STRAIGHT);
      }
    }
  }
  
  if (state.powerState == OFF) {
    frontSensor.write(105);
    motors.fullStop();
  }
  
  
  leftWheel.write(motors.leftValue);
  rightWheel.write(motors.rightValue);
 
}
