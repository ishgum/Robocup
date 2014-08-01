#include <Servo.h> 

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

#include "Sensors.h"
#include "Motors.h"
#include "Navigation.h"
#include "State.h"
#include "PID.h"
#include "Compass.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49

// Peripherals

Motors motors;
Servo sweep;


Sensors infaFront(4);
Sensors infaLeft(0);
Sensors infaRight(1);

int ana_onoff = 3; // analogue input pin


// State things

int turning_dir = CLOCKWISE;

int state_on = 0;
int state_off = 0;
int following_wall = 0;


  
// RTOS

unsigned long tick = 0;
  
  
Compass compass;
State state;
PID angularError; 

 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
 

  compass.desiredValue = compass.findAngle();
  

}


  
// Turning on and off
void check_on (void) {
  if (analogRead(ana_onoff) != 0 && state.powerState == OFF) {
   state_off = 0;
   state_on += 1;
  }
  if (analogRead(ana_onoff) == 0 && state.powerState == ON) {
   state_on = 0;
   state_off += 1;
  }
  
  if (state_on == 10) {
    state.powerState = ON;
  }
  if (state_off == 10) {
    state.powerState = OFF;
  }
}



void navigateCorner (void) {
  if (infaFront.found == true) {
    motors.fullStop();
    state.updateDriveState(TURNING);
    if (infaLeft.found == true) {
      turning_dir = CLOCKWISE;
      angularError.desiredValue += 90;
    }
    else if (infaRight.filteredRead > 300) {
    turning_dir = ANTI_CLOCKWISE;
    angularError.desiredValue -= 90;
    }
  }
}
      

void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
}



void determine_follow_wall(void) {
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    following_wall = infaLeft.filteredRead;
  }
  else {
    following_wall = infaRight.filteredRead;
  }
}


void follow_wall_mode (void) {
  infaFront.findWall(500);
  determine_follow_wall();
  if (state.driveState == STRAIGHT) {
    int straight_error = angularError.error + (following_wall - 400)/20;
    motors.drive(angularError.error, 50, FORWARDS);
  }
  if (state.driveState == TURNING) {      
    motors.turn(50, turning_dir);
    
    if (abs(angularError.error) < 10) {
        state.driveState = STRAIGHT;
    }
  } 
}
  



//void random_search_mode (void) {
  





void loop() {
  
  check_on();
  
  if (tick % 10 == 0) {
  updateSensors();
  }
  
  if (state.powerState == OFF) {
    motors.fullStop();
  }
  
  if (state.powerState == ON) {
      angularError.findError(compass.findAngle());
      
      if (state.navigationState == WALL_FOLLOW) {
        follow_wall_mode();
      }
  }
  tick++;
}

