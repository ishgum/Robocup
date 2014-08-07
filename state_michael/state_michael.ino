
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
#include "WaveArm.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49


#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30

#define TOO_CLOSE 0
#define FAR_AWAY 1

#define FRONT 0
#define SIDE 1

// Peripherals

  Motors motors;
  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  Servo detectorArm;
  
  
  Whisker whisker;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);

  //Magno compass;
  State state;
  PID angularError;
  PID wallError;
  Switch powerSwitch(3);
  
  ColourSense colourView;
  
  WaveArm detector;

// State things

int setOff = FRONT;
bool waving = true; //won't lose it here//////////////////////////////
bool centred = false;
  
// RTOS

unsigned long tick = 0;
  
  
 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

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
  
  //Magnometer
  //compass.init();
  //compass.desiredValue = compass.currentAngle;
  
}

void WISR(void)
{
    whisker.count++;
}



void resetRobot(void) {
  state.updateDriveState(STRAIGHT);
  updateSensors();
  determineWallFollow();
  colourView.setHome();
  frontSensor.write(SENSOR_MIDDLE);
  waving = true;
  state.navigationState = WALL_FOLLOW;
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  
  switch (powerSwitch.switchState) {
    case SWITCH_ON:
    state.updatePowerState(ON);
    resetRobot();
    
    //compass.findAngle();
    //angularError.desiredValue = compass.currentAngle;
    
    break;
  case SWITCH_OFF:
    state.updateDriveState(STOPPED);
    state.updatePowerState(OFF);
    break;
  }
}



void checkColour(void) {
  colourView.detectBase();
  if (colourView.area == ENEMY) {
    state.updateNavigationState(EVACUATE);
  }
  if (colourView.area == ARENA) {
    motors.setMotorSpeed(70);
  }
  if (colourView.area == HOME) {
    motors.setMotorSpeed(50);
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
  
  if (state.followState == RIGHT_WALL) {
    wallError.findError(infaRight.filteredRead);
  }
  if (state.followState == LEFT_WALL) {
    wallError.findError(infaLeft.filteredRead);
  }
}



void determineWallFollow (void) {
  //angularError.findError(compass.currentAngle);
  
  if (infaLeft.filteredRead <= infaRight.filteredRead) {
    state.followState = RIGHT_WALL;
  }
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    state.followState = LEFT_WALL;
  }
}





void driveRobot (int driveDirection) {
  if (state.driveState == STRAIGHT) {
    float straightError = -driveDirection * state.followState * wallError.error/10;
    motors.drive(straightError, motors.motorSpeed, driveDirection);
  }
  
  if (state.driveState == TURNING) {      
    motors.turn(70, state.followState);
  } 
}




void navigateCorner (void) {
   if (state.driveState == STRAIGHT && infaFront.findWall(400)) {
      motors.fullStop();
      state.updateDriveState(TURNING);
      int sensorTurnAngle = SENSOR_MIDDLE + state.followState*SENSOR_ANGLE;
      frontSensor.write(sensorTurnAngle);
      setOff = FRONT;
      determineWallFollow();
    }
  else if (state.driveState == TURNING && !infaFront.findWall(300) && setOff == FRONT) {
    
    frontSensor.write(SENSOR_MIDDLE);
    state.updateDriveState(STRAIGHT);
  }
  
}

 



void avoidWallState (void) {
    navigateCorner ();
    if (state.driveState == STRAIGHT && (infaLeft.findWall(400) || infaRight.findWall(400))) {
      motors.fullStop();
      state.updateDriveState(TURNING);
      setOff = SIDE;
      determineWallFollow();
    }
    else if (state.driveState == TURNING && !(infaLeft.findWall(150) || infaRight.findWall(150)) && setOff == SIDE) {
        state.updateDriveState(STRAIGHT);
      }
    wallError.error = 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void loop() {
   checkPowerSwitch();
  
    switch (state.powerState) {
      case ON:
      updateSensors();
      checkColour();
      
      if (tick % 40 == 0) {
      //      compass.findAngle();
            colourView.findColour();
        }
      
      updateWallError();
      
      switch (state.navigationState) {
      
        case EVACUATE:
          state.updateNavigationState(SEARCHING);
          motors.fullStop();
          leftWheel.write(motors.leftValue);
          rightWheel.write(motors.rightValue);
          delay(50);
          //leaveEnemyBase();
        break;
      
        case WALL_FOLLOW: 
          wallError.setDesiredValue(350);
          navigateCorner();
        break;
      
        case SEARCHING: 
          wallError.setDesiredValue(300);
          avoidWallState();
          if(whisker.detect(SLOW)){
            waving = false;
            motors.fullStop();
            //state.updateNavigationState(ALIGNING); 
          }
          detector.waveArm(waving, detectorArm, tick);
        break;
      
  //     case ALIGNING:
  //       Serial.println(centred);
  //         if(!centred){
  //           motors.fullStop();
  //           centred = detector.align(detectorArm);
  //         }
  //         else if(centred){
  //           if(whisker.detect(QUICK)){
  //            motors.fullStop(); 
  //            state.updateNavigationState(COLLECTING); 
  //           }
  //           else {
  //             motors.turn(25, 1); //turn until find the weight again
  //           }
  //         }
  
         //break; 
      
        case COLLECTING:
          state.updateNavigationState(SEARCHING); 
        break;
      }
        driveRobot(FORWARDS);
    break;
  
  case OFF:
    motors.fullStop();
  break;
  }
    
    
    leftWheel.write(motors.leftValue);
    rightWheel.write(motors.rightValue);
    tick++;
}




