

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

#include "Sensors.h"
//#include "Motors.h"
#include "Navigation.h"
#include "State.h"
#include "PID.h"
#include "Magno.h"
#include "Switch.h"


/**** SET UP ****/


#define ZERO_VALUE 90
#define FULL_SPEED 90

#define FORWARDS 1
#define BACKWARDS -1

#define CLOCKWISE 1
#define ANTI_CLOCKWISE -1



#define DIGITAL_OUT_POWER 49

// Peripherals

  //Motors motors;
  Servo sweep;
  
  Servo leftWheel;
  Servo rightWheel;
                
                
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);

  State state;
  PID angularError;
  PID wallError;
  Switch powerSwitch(3);

// State things

int turning_dir = CLOCKWISE;

int following_wall = 0;


  
// RTOS

unsigned long tick = 0;
  
  
  
  
  float angles[3];
  FreeSixIMU sixDOF = FreeSixIMU();
  HMC5883L compass;



 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
  
      //Initialising magnet sensor
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  
  compass = HMC5883L(); // init HMC5883
  compass.SetMeasurementMode(Measurement_Continuous);
  sixDOF.getEuler(angles);
  
  
  angularError.desiredValue = angles[0];

  wallError.desiredValue = 400;
  
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)
  
}









// Updates a single sensor using a MAF

void fullStop (void) {
  leftWheel.write(90);
  rightWheel.write(90); 
}


void drive (signed int error, signed int speedPercent, signed int dir) {
  signed int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  
  leftWheel.write(ZERO_VALUE + dir*(speedMotors + error));
  rightWheel.write(ZERO_VALUE + dir*(speedMotors - error));
}


void turn (unsigned int speedPercent, signed int dir) {
  signed int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  leftWheel.write(ZERO_VALUE + dir*speedMotors);
  rightWheel.write(ZERO_VALUE - dir*speedMotors);
}


















float findAngle(void) {
  Serial.println(angles[0]);
  sixDOF.getEuler(angles);
  return angles[0];
}
  
  
// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == SWITCH_ON) {
    state.updatePowerState(ON);
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
  angularError.findError(findAngle());
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
      fullStop();
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
    drive(straightError, 50, FORWARDS);
  }
  
  if (state.driveState == TURNING) {      
    turn(50, turning_dir);
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
    
    if (tick % 10 == 0) {
      updateState();
      
      if (state.navigationState == WALL_FOLLOW) {
        followWallState();
      }
    }
  }
  
  if (state.powerState == OFF) {
    fullStop();
  }
  tick++;
}

