
#include <Servo.h> 
#include <Scheduler.h>
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"

#include "Sensors.h"
#include "State.h"
#include "PID.h"
#include "Switch.h"
#include "Whisker.h"
#include "WaveArm.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49


#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30



#define MOTOR_ZERO_VALUE 90
#define MOTOR_FULL_SPEED 65

#define MOTOR_FORWARDS 1
#define MOTOR_BACKWARDS -1

#define MOTOR_CW 1
#define MOTOR_CCW -1

// Peripherals

  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  Servo detectorArm;
  
  
  Whisker whisker;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);


  State state;

  PID leftError;
  PID rightError;
  Switch powerSwitch(3);
  
  
  WaveArm detector;

// State things

bool waving = true; //won't lose it here//////////////////////////////
bool centred = false;
  
// RTOS
  
  
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
  
  initColourView();
 
  
  //WHISKER STUFF
  attachInterrupt(0, WISR, FALLING); //enable interrupt0 (pin2)
  pinMode(2, INPUT);
  TCCR1A = 0x00; //normal operation mode
  TCCR1B = 0x03; //64x prescale for 250kHz clock
  TCNT1=0x0000; //16bit counter register initialised to 0
  
  Scheduler.startLoop(loop2);
  //Scheduler.startLoop(loop3);
  
}

void WISR(void)
{
    whisker.count++;
}



void initRobot(void) {
  state.updateDriveState(STATE_STRAIGHT);
  state.updateNavigationState(STATE_WALL_FOLLOW);
  setMotorDir(MOTOR_FORWARDS);
  
  updateSensors();
  determineWallFollow();
  setHomeColour();
  frontSensor.write(SENSOR_MIDDLE);
  waving = true;
  
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkPowerSwitch() {
  powerSwitch.updateSwitch();
  
  switch (powerSwitch.switchState) {
    case SWITCH_ON:
    state.updatePowerState(STATE_ON);
    initRobot();
    
    break;
  case SWITCH_OFF:
    state.updatePowerState(STATE_OFF);
    state.updateDriveState(STATE_STOPPED);
    break;
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
  
    rightError.findError(infaRight.filteredRead);
    leftError.findError(infaLeft.filteredRead);
}



void determineWallFollow (void) {
    
  if (infaLeft.filteredRead <= infaRight.filteredRead) {
    state.followState = STATE_RIGHT_WALL;
    setTurnDir(MOTOR_CCW);
  }
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    state.followState = STATE_LEFT_WALL;
    setTurnDir(MOTOR_CW);
  }
}






void loop() {
  
  checkPowerSwitch();
  
  switch (state.powerState) {
    case STATE_ON:
    updateSensors();
    checkColour();
    updateErrors();
    delay(50);
  break;
  
  case STATE_OFF:
    fullStop();
  break;
  }
}


void loop2() {
  switch (state.navigationState) {
      
        case STATE_EVACUATE:
          state.updateNavigationState(STATE_SEARCHING);
          fullStop();
          //leaveEnemyBase();
        break;
      
        case STATE_WALL_FOLLOW: 
          leftError.setDesiredValue(350);
          rightError.setDesiredValue(350);
          navigateCorner();
        break;
      
        case STATE_SEARCHING: 
          leftError.setDesiredValue(300);
          rightError.setDesiredValue(300);
          avoidWall();
          if(whisker.detect(SLOW)){
            waving = false;
            fullStop();
            //state.updateNavigationState(ALIGNING); 
          }
          //detector.waveArm(waving, detectorArm, tick);
        break;
      
        case STATE_COLLECTING:
          state.updateNavigationState(STATE_SEARCHING); 
        break;
      }
  
}


