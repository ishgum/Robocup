

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"
#include "state_michael2.h"

  
  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

  frontSensor.attach(12);
  leftWheel.attach(6);  // S11 (on port S6)
  rightWheel.attach(7); // S12 (on port S6)
  
  leftWing.attach(11);
  rightWing.attach(8);
  leftArm.attach(10);
  rightArm.attach(9);
  ramp.attach(13);
  
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
  infaBottom.updateSensor();
}


// Updates the error for the angle as well as for the wall following

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
    updateSensors();
    if (tick % 10) {
      checkColour();
    }
    if (tick % 4) {
      navigateRobot();
      leftArm.write(0);
      rightArm.write(180);
      ramp.write(80);
      leftWheel.write(leftValue);
      rightWheel.write(rightValue);
    }
  break;
  
  case STATE_OFF:
    fullStop();
    ramp.write(160);
    delay(100);
    leftArm.write(130);
     rightArm.write(50);
      
  break;
  }
  tick++;
}


