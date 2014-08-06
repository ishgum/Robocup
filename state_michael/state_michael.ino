
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
#include "Whisker.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49


#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30

#define TOO_CLOSE 0
#define FAR_AWAY 1

// Peripherals

  Motors motors;
  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  Servo detectorArm;
  
  
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

int motorSpeed = 50;
int pos = 0;
int waveDirection = 1;
int wall = FAR_AWAY;
  
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
  detectorArm.attach(11);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)

  
  
  colourView.init();
  colourView.setHome();
  
  //WHISKER STUFF
  attachInterrupt(0, WISR, FALLING); //enable interrupt0 (pin2)
  pinMode(2, INPUT);
  TCCR1A = 0x00; //normal operation mode
  TCCR1B = 0x03; //64x prescale for 250kHz clock
  TCNT1=0x0000; //16bit counter register initialised to 0
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  if (powerSwitch.switchState == SWITCH_ON) {
    state.updatePowerState(ON);
    state.updateDriveState(STRAIGHT);
    updateSensors();
    determineWallFollow();
    
    
    colourView.setHome();
    //compass.findAngle();
    //angularError.desiredValue = compass.currentAngle;
  }
  if (powerSwitch.switchState == SWITCH_OFF) {
     state.updateDriveState(STOPPED);
    state.updatePowerState(OFF);
    frontSensor.write(SENSOR_MIDDLE);
  }
}



void checkColour(void) {
  colourView.detectBase();
  if (colourView.area == ENEMY) {
    state.updateNavigationState(EVACUATE);
  }
  if (colourView.area == ARENA) {
    motorSpeed = 60;
  }
  if (colourView.area == HOME) {
    motorSpeed = 50;
    state.updateNavigationState(WALL_FOLLOW);
  }
}






// Updates the front, left and right infa-red sensors

void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
}


// Updates the error for the angle as well as for the wall following

void updateWallError (void) {
  //angularError.findError(compass.currentAngle);
  determineWallFollow();
  
  if (state.followState == RIGHT_WALL) {
    wallError.findError(infaRight.filteredRead);
  }
  if (state.followState == LEFT_WALL) {
    wallError.findError(infaLeft.filteredRead);
  }
}



// Facilitates transitions between states





void determineWallFollow(void) {
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    state.followState = LEFT_WALL;
  }
  else {
    state.followState = RIGHT_WALL;
  }
}




void driveRobotBackwards (void) {
  if (state.driveState == STRAIGHT) {
    float straightError = state.followState * wallError.error/13;
    motors.drive(straightError, motorSpeed, BACKWARDS);
  }
  
  if (state.driveState == TURNING) {      
    motors.turn(70, state.followState);
  } 
}


void driveRobotForwards (void) {
  if (state.driveState == STRAIGHT) {
    float straightError = -state.followState * wallError.error/13;
    motors.drive(straightError, motorSpeed, FORWARDS);
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

 



void avoidWallState (void) {
      followWallState ();
      if (wallError.error < 400) {
        wallError.error = wallError.error;
      }
      if (wallError.error > 400) {
        wallError.error = 0;
      }
      //if (wall == TOO_CLOSE) {
      //  wallError.error = wallError.error;
      //}
      //if (wall == FAR_AWAY) {
      //  wallError.error = 0;
      //}
}


void leaveEnemyBase (void) {
  if (infaFront.findWall(200)) {
    float straightError = state.followState * wallError.error/10;
    motors.drive(straightError, motorSpeed, BACKWARDS);
  }
  else {
    switch (state.followState) {
      case RIGHT_WALL:
        state.followState = LEFT_WALL;
        break;
      
      case LEFT_WALL:   
       state.followState = RIGHT_WALL;
    } 
    state.navigationState = WALL_FOLLOW;
  }
    
}
    
    
    
void waveArm(void){
  detectorArm.write(pos);
  if (tick % 2 == 0) {
    pos = pos + waveDirection;
  }
  if (pos >= 140) {
    waveDirection = -1;
  }
  if (pos <= 40) {
    waveDirection = 1;
  }
}
    





void loop() {
  
  checkPowerSwitch();
  
  switch (state.powerState) {
    case ON:
      updateSensors();
      checkColour();
        
      if (tick % 200 == 0) {
  //      compass.findAngle();
          colourView.findColour();
      }
      
      switch (state.navigationState) {
        case WALL_FOLLOW: 
          wallError.setDesiredValue(350);
          updateWallError();
          followWallState();
          driveRobotForwards();
          break;

        case SEARCHING: 
          wallError.setDesiredValue(300);
          updateWallError();
          avoidWallState();
          Serial.println(wallError.error);
          waveArm();
          driveRobotForwards();
          
        case EVACUATE:
          state.updateNavigationState(SEARCHING);
          //motors.fullStop();
          //leaveEnemyBase();
          break;
        }
        break;
  
  case OFF:
    motors.fullStop();
    break;
  }
  
  leftWheel.write(motors.leftValue);
  rightWheel.write(motors.rightValue);
  tick++;
}



