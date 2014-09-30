

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"
#include "state_michael2.h"

bool collect_trigger = false;
bool weightCollect = false;

int weightDetect = 0;
int motorsGoing = true;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

  frontSensor.attach(12);
  leftWheel.attach(6);  // S11 (on port S6)
  rightWheel.attach(7); // S12 (on port S6)
  
  leftWingServo.attach(8);
  rightWingServo.attach(11);
  leftArmServo.attach(10);
  rightArmServo.attach(9);
  gateServo.attach(13);
  
  initColourView();
  
  //WHISKER STUFF
    cli();
  attachInterrupt(4, WISR, FALLING); //enable interrupt0 (pin2)
  pinMode(19, INPUT);
  TCCR1A = 0x00; //normal operation mode
  TCCR1B = 0x03; //64x prescale for 250kHz clock
  TCNT1=0x0000; //16bit counter register initialised to 0
  sei(); 
  
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
  changeToWallFollowState();
  
  initColourView();
  for (int i = 0; i < 8; i++) {
    updateSensors();
  }
  
  currentSensor = determineWallFollow();
  setHomeColour();
  frontSensor.write(SENSOR_MIDDLE);
  motorsGoing = true;
  collect_trigger = false;
  
  rightWing.setDesiredAngle(160);
  
  rightArm.setDesiredAngle(110);
  leftArm.setDesiredAngle(110);
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkSwitches() {
  powerSwitch.updateSwitch();
  limitRamp.updateSwitch();
  limitHiFive.updateSwitch();
  limitFront.updateSwitch();
  
  //Serial.println(limitFront.switchState);
  
  if (limitFront.switchState == SWITCH_ON) {
        navigationState.updateState(STATE_EVACUATE);
  }
  
  if (limitRamp.switchState == SWITCH_OFF) {
       collect_trigger = true;
  }
  
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
  infaBelly.updateSensor();
  
  currentSensor.updateSensor();
}

void sweepAll (void) {
  leftArm.sweep(leftArmServo);
  rightArm.sweep(rightArmServo);
  gateArm.sweep(gateServo);
  
  rightWing.sweep(rightWingServo);
}

int startTime = 0;
bool millisDelay (int DelayTime){
   bool goTime = false;
   if(startTime == 0){
      startTime = millis(); 
   }
   if ((millis() - startTime) % DelayTime == 0){
      goTime = true;
     startTime = 0;
   } 
   return goTime;
}

void loop() {
  checkSwitches();
  sweepAll();
  //Serial.println(powerState.returnState());
  switch (powerState.returnState()) {
    case STATE_ON:
    updateSensors();
    findWeights();
    if (tick % 100 == 0) {
      checkColour();
    }
    if (tick % 4 == 0) {
      navigateRobot();
    }
    
    if (collect_trigger) {
      fullStop();
      rightWing.setDesiredAngle(90);
      if (limitHiFive.switchState == SWITCH_ON) {
        rightWing.setDesiredAngle(160);
        collect_trigger = false;
        weightCollect = true;
      }
    }
  break;
  
  case STATE_OFF:
    fullStop();
    leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle( 0);
     gateArm.setDesiredAngle(120);
     rightWing.setDesiredAngle(160);
  break;
  }
  tick++;
}


