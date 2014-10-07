

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"
#include "state_michael2.h"

bool collect_trigger = false;
bool weightCollect = false;
bool detected = false;

int weightDetect = 0;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

  frontSensor.attach(9);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)
  
  leftWingServo.attach(6);
  rightWingServo.attach(7);
  leftArmServo.attach(8);
  rightArmServo.attach(11);
  gateServo.attach(10);
  
  
  //WHISKER STUFF
    cli();
  attachInterrupt(4, WISR, FALLING); //enable interrupt0 (pin2)
  pinMode(19, INPUT);
  TCCR1A = 0x00; //normal operation mode
  TCCR1B = 0x03; //64x prescale for 250kHz clock
  TCNT1=0x0000; //16bit counter register initialised to 0
  sei(); 
  
  tick = 0;
  
  initRobot();
}

void WISR(void)
{
    whisker.count++;
}



void initRobot(void) {
  driveState.setToDefault();
  navigationState.setToDefault();
  setMotorDir(MOTOR_FORWARDS);
  navigationState.updateState(STATE_WALL_FOLLOW);  
  initColourView();
  
  for (int i = 0; i < 8; i++) {
    updateSensors();
  }
  Serial.println("init");
  currentSensor = determineWallFollow();
  setHomeColour();
  frontSensor.write(SENSOR_MIDDLE);
  collect_trigger = false;
  
  rightWing.setDesiredAngle(160);
  
  rightArm.setDesiredAngle(110);
  leftArm.setDesiredAngle(110);
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkSwitches() {
  powerSwitch.updateSwitch();
  limitRamp.updateSwitch();
  limitLeftWing.updateSwitch();
  limitRightWing.updateSwitch();
  limitFront.updateSwitch();
  
  //Serial.print(limitRightWing.switchState); Serial.print('\t'); Serial.print(limitLeftWing.switchState); Serial.print('\t'); Serial.print(limitFront.switchState); Serial.print('\t'); Serial.println(limitRamp.switchState); 
  
  if (limitFront.switchState == SWITCH_ON) {
        navigationState.updateState(STATE_EVACUATE);
        //detected = true;
  }
  
  if (limitRamp.switchState == SWITCH_OFF) {
       collect_trigger = true;
  }
  
  if (limitRightWing.switchState == SWITCH_ON) {
       //detected = true;
  }
  
  switch (powerSwitch.switchState) {
    case SWITCH_ON:
      powerState.updateState(STATE_ON);    
    break;
    
  case SWITCH_OFF:
    powerState.updateState(STATE_OFF);
   break;
  }
}





// Updates the front, left and right infa-red sensors

void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
  //infaBottom.updateSensor();
  //infaBelly.updateSensor();
  
  currentSensor.updateSensor();
}


void sweepAll (void) {
  leftArm.sweep(leftArmServo);
  rightArm.sweep(rightArmServo);
  gateArm.sweep(gateServo);
  
  rightWing.sweep(rightWingServo);
  leftWing.sweep(leftWingServo);
}


int stateTest = 1;
void loop() {
  
  
  checkSwitches();
  sweepAll();
  updateSensors();
  driveRobot();
  
  gateArm.setDesiredAngle(50);
     
  switch (powerState.returnState()) {
    case STATE_ON:    
      findWeights();
      
      if (tick % 100 == 0) {
        checkColour();
      }
      if (tick % 4 == 0) {
        navigateRobot();
      }
      
      if (collect_trigger) {
        driveState.updateState(STATE_STOPPED);
        rightWing.setDesiredAngle(90);
        
        if (limitRightWing.switchState == SWITCH_ON) {
          rightWing.setDesiredAngle(160);
          collect_trigger = false;
          weightCollect = true;
        }
      }
  break;
  
  case STATE_OFF:
     
  break;
  }
  tick++;
}


