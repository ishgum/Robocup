#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>


#include "Magno.h"
#include "Switch.h"

#define DIGITAL_OUT_POWER 49


Magno compass;

Switch powerSwitch(3);


int currentState = 0;

unsigned long tick = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

  compass.init();
}




void loop() {
  powerSwitch.updateSwitch();
  
   if (powerSwitch.switchState == SWITCH_ON) {
    currentState = 1;
    }
  if (powerSwitch.switchState == SWITCH_OFF) {
    currentState = 0;
  }
  
  
  if (currentState == 1) {
    compass.findAngle();
    Serial.println(compass.currentAngle);
    }
  if (currentState == 0) {
  }
 
 
}
