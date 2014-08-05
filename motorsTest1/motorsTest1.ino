#include <Servo.h> 
#include "Motors.h"
#include "Switch.h"

#define DIGITAL_OUT_POWER 49



Motors motors;
Servo leftWheel;
Servo rightWheel;

Switch powerSwitch(3);

unsigned long tick = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);
  
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)

}



void loop() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == SWITCH_ON) {
    motors.turn(100, ANTI_CLOCKWISE);
    }
  if (powerSwitch.switchState == SWITCH_OFF) {
    motors.fullStop();
  }
  
  Serial.println(motors.leftValue);
  
  leftWheel.write(motors.leftValue);
  rightWheel.write(motors.rightValue);
 
}
