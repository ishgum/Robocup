
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
  Servo servoLeft;
  Servo servoRight;
  Servo leftWheel;
  Servo rightWheel;
  
  
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
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);
  
  //Magnometer
  
  compass.init();
  
  
  compass.desiredValue = compass.currentAngle;

  servoLeft.attach(0);
  servoRight.attach(1);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)

  wallError.desiredValue = 400;
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == SWITCH_ON) {
    state.updatePowerState(ON);
    compass.findAngle();
    angularError.desiredValue = compass.currentAngle;
  }
  if (powerSwitch.switchState == SWITCH_OFF) {
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
  angularError.findError(compass.currentAngle);
  if (state.followState == RIGHT_WALL) {
    wallError.findError(infaRight.filteredRead);
  }
  if (state.followState == LEFT_WALL) {
    wallError.findError(infaLeft.filteredRead);
  }
}



// Facilitates transitions between states

void updateState(void) {
  if (state.powerState == OFF) {
    state.driveState = STOPPED;
  }
  
  if (state.driveState == STOPPED && state.powerState == ON) {
      state.driveState = STRAIGHT;
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




void driveRobot (void) {
  if (state.driveState == STRAIGHT) {
    float straightError = angularError.error + wallError.error/10;
    motors.drive(straightError, 50, FORWARDS);
  }
  
  if (state.driveState == TURNING) {      
    motors.turn(40, turning_dir);
  } 
}





void followWallState (void) {
   if (state.driveState == STRAIGHT && infaFront.findWall(450)) {
      motors.fullStop();
      state.updateDriveState(TURNING);
      
      if (state.followState == RIGHT_WALL) {
        angularError.changeDesired(-90);
      }
      if (state.followState == LEFT_WALL) {
        angularError.changeDesired(90);
      }
    }
  else if (state.driveState == TURNING && abs(angularError.error) < 5) {
    state.updateDriveState(STRAIGHT);
  }
  
}

 



void randomSearchMode (void) {
  if (state.driveState == STRAIGHT) {
    if (tick % 100) { 
      if (angularError.sweepDirection == 0) {
        angularError.desiredSweep += 1;
        servoLeft.write(angularError.desiredSweep * 2);
        servoRight.write(angularError.desiredSweep * 2);
      }
      if (angularError.sweepDirection == 1) {
        angularError.desiredSweep -= 1;
      }
  }
  if (angularError.desiredSweep >= 45) {
    angularError.sweepDirection = 1;
  }
  if (angularError.desiredSweep <= -45) {
    angularError.sweepDirection = 0;
  }
  //servosSweep();
  followWallState();
    
}
}
    
    





void loop() {
  
  checkPowerSwitch();
 
 
  updateState();
  
  if (state.powerState == ON) {
    
    //motors.drive(0, 70, FORWARDS);
    
  updateSensors();
  updateErrors();
    
    if (tick % 50 == 0) {
      compass.findAngle();
      //Serial.println(angularError.error);
    }
    
    if (tick % 10 == 0) {      
      if (state.navigationState == WALL_FOLLOW) {
        followWallState();
      }
      if (state.navigationState == SEARCHING) {
        randomSearchMode();
      }
      driveRobot();
    }
  }
  
  if (state.powerState == OFF) {
    motors.fullStop();
  }
  
  leftWheel.write(motors.leftValue);
  rightWheel.write(motors.rightValue);
  tick++;
}



