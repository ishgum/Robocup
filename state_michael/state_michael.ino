

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

#include "Sensors.h"
#include "Motors.h"
#include "Navigation.h"
#include "State.h"
#include "PID.h"
#include "Magno.h"
#include "Switch.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49

// Peripherals

  Motors motors;
  Servo sweep;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);

  Magno compass;
  State state;
  PID angularError;
  PID wallError;
  Switch powerSwitch(3);

// State things

int turning_dir = CLOCKWISE;

int following_wall = 0;


  
// RTOS

unsigned long tick = 0;
  
  
 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
  compass.desiredValue = compass.findAngle();

  wallError.desiredValue = 400;
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == true) {
    state.updatePowerState(ON);
  }
  if (powerSwitch.switchState == false) {
    state.updatePowerState(OFF);
  }
}



// Updates the front, left and right infa-red sensors

void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
}


// Updates the error for the angle as well as for the wall following

void updateErrors (void) {
  angularError.findError(compass.findAngle());
  if (state.followState == RIGHT_WALL) {
    wallError.findError(infaRight.filteredRead);
  }
  if (state.followState == LEFT_WALL) {
    wallError.findError(infaLeft.filteredRead);
  }
}



// Facilitates transitions between states

void updateState(void) {
  if (state.navigationState == WALL_FOLLOW) {
    if (state.driveState == STRAIGHT && infaFront.findWall(500)) {
      motors.fullStop();
      state.updateDriveState(TURNING);
      
      if (state.followState == RIGHT_WALL) {
        angularError.desiredValue -= 90;
      }
      if (state.followState == LEFT_WALL) {
        angularError.desiredValue += 90;
      }
    }
    else if (state.driveState == TURNING && abs(angularError.error) < 5) {
      state.updateDriveState(STRAIGHT);
    }
  }
}




void determine_follow_wall(void) {
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    following_wall = infaLeft.filteredRead;
  }
  else {
    following_wall = infaRight.filteredRead;
  }
}





void followWallState (void) {
   
  if (state.driveState == STRAIGHT) {
    float straightError = angularError.error + wallError.error/20;
    motors.drive(straightError, 50, FORWARDS);
  }
  
  if (state.driveState == TURNING) {      
    motors.turn(50, turning_dir);
  } 
}
  



//void random_search_mode (void) {
  





void loop() {
  
  checkPowerSwitch();
  
  if (state.powerState == ON) {
    
    if (tick % 10 == 0) {
    updateSensors();
    updateErrors();
    }
    
    if (tick % 1000 == 0) {
      updateState();
      
      if (state.navigationState == WALL_FOLLOW) {
        followWallState();
      }
    }
  }
  
  if (state.powerState == OFF) {
    motors.fullStop();
  }
  tick++;
}

