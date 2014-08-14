
#include <Servo.h> 
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
#include "Motors.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49


#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30



// Peripherals

  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  Servo detectorArm;
  
  
  Whisker whisker;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);


  State powerState(STATE_OFF);
  State navigationState(STATE_WALL_FOLLOW);
  State driveState(STATE_STRAIGHT);
  State followState(STATE_LEFT_WALL);

  PID leftError;
  PID rightError;
  Switch powerSwitch(3);
  
  
  WaveArm detector;

// State things

bool waving = true; //won't lose it here//////////////////////////////
bool centred = false;
  
// RTOS
  
unsigned long long tick;  
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
  
  tick = 0;
  
}

void WISR(void)
{
    whisker.count++;
}



void initRobot(void) {
  driveState.setToDefault();
  navigationState.setToDefault();
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
    powerState.updateState(STATE_ON);
    initRobot();
    
    break;
  case SWITCH_OFF:
    powerState.updateState(STATE_OFF);
    driveState.updateState(STATE_STOPPED);
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
    followState.updateState(STATE_RIGHT_WALL);
    setTurnDir(MOTOR_CCW);
  }
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    followState.updateState(STATE_LEFT_WALL);
    setTurnDir(MOTOR_CW);
  }
}






void loop() {
  
  checkPowerSwitch();
  
  switch (powerState.returnState()) {
    case STATE_ON:
    if (tick % 50) {
      updateSensors();
      checkColour();
    }
    if (tick % 100) {
      navigateRobot();
    }
  break;
  
  case STATE_OFF:
    fullStop();
  break;
  }
  tick++;
}


