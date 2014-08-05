#include <Servo.h> 
#include "Motors.h"
#include "Switch.h"
#include "Sensors.h"


#define DIGITAL_OUT_POWER 49



Motors motors;
Servo leftWheel;
Servo rightWheel;
Servo frontSensor;

Switch powerSwitch(3);

Sensors infaFront(4);

unsigned long tick = 0;

int currentState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);
  
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)
  frontSensor.attach(10);
}



void loop() {
  powerSwitch.updateSwitch();
  infaFront.updateSensor();
  
  if (powerSwitch.switchState == SWITCH_ON) {
    currentState = 1;
    }
  if (powerSwitch.switchState == SWITCH_OFF || (infaFront.filteredRead < 200)) {
    currentState = 0;
  }
  
  if (currentState == 1) {
    frontSensor.write(160);
    motors.turn(50, CLOCKWISE);
    }
  if (currentState == 0) {
    frontSensor.write(105);
    motors.fullStop();
  }
  
  
  leftWheel.write(motors.leftValue);
  rightWheel.write(motors.rightValue);
 
}
