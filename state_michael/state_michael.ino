
#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"

#include "Sensors.h"
#include "Motors.h"
#include "Navigation.h"
#include "State.h"
#include "PID.h"
#include "Magno.h"
#include "Switch.h"
#include "ColourSense.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49


#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30

// Peripherals

  Motors motors;
  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);

  //Magno compass;
  State state;
  PID angularError;
  PID wallError;
  Switch powerSwitch(3);
  
  ColourSense colourView;

// State things


  
// RTOS

unsigned long tick = 0;
  
  
 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);
  
  //Magnometer
  
  //compass.init();
  
  
  //compass.desiredValue = compass.currentAngle;

  frontSensor.attach(10);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)

  wallError.setDesiredValue(400);
  
  colourView.init();
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == SWITCH_ON) {
    state.updatePowerState(ON);
    state.updateDriveState(STRAIGHT);
    determineWallFollow();
    //compass.findAngle();
    //angularError.desiredValue = compass.currentAngle;
  }
  if (powerSwitch.switchState == SWITCH_OFF) {
     state.updateDriveState(STOPPED);
    state.updatePowerState(OFF);
    frontSensor.write(SENSOR_MIDDLE);
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
  //angularError.findError(compass.currentAngle);
  if (state.followState == RIGHT_WALL) {
    wallError.findError(infaRight.filteredRead);
  }
  if (state.followState == LEFT_WALL) {
    wallError.findError(infaLeft.filteredRead);
  }
}



// Facilitates transitions between states





void determineWallFollow(void) {
  updateSensors();
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    state.followState = LEFT_WALL;
  }
  else {
    state.followState = RIGHT_WALL;
  }
}




void driveRobot (void) {
  if (state.driveState == STRAIGHT) {
    float straightError = -state.followState * wallError.error/13;
    motors.drive(straightError, 70, FORWARDS);
  }
  
  if (state.driveState == TURNING) {      
    motors.turn(70, state.followState);
  } 
}





void followWallState (void) {
   if (state.driveState == STRAIGHT && infaFront.findWall(500)) {
      motors.fullStop();
      state.updateDriveState(TURNING);
      int sensorTurnAngle = SENSOR_MIDDLE + state.followState*SENSOR_ANGLE;
      frontSensor.write(sensorTurnAngle);
    }
  else if (state.driveState == TURNING && !infaFront.findWall(300)) {
    
    frontSensor.write(SENSOR_MIDDLE);
    state.updateDriveState(STRAIGHT);
  }
  
}

 



void randomSearchMode (void) {
  if (state.driveState == STRAIGHT) {
//    if (tick % 100) { 
//      if (angularError.sweepDirection == 0) {
//      }
//      if (angularError.sweepDirection == 1) {
//        angularError.desiredSweep -= 1;
//      }
//  }
//  if (angularError.desiredSweep >= 45) {
//    angularError.sweepDirection = 1;
//  }
//  if (angularError.desiredSweep <= -45) {
//    angularError.sweepDirection = 0;
//  }
  //servosSweep();
  followWallState();
    
}
}
    
    





void loop() {
  
  checkPowerSwitch();
  
  if (state.powerState == ON) {
    
    //motors.drive(0, 70, FORWARDS);
    
  updateSensors();
  updateErrors();
    
    if (tick % 50 == 0) {
//      compass.findAngle();
        colourView.findColour();
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



