

#include <Servo.h> 
#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#include "Adafruit_TCS34725.h"
#include "state_michael2.h"

bool collect_trigger = false;
bool weightCollect = false;

  
void setup() {
  Serial.begin(9600);
  Serial.println("Got here");
  
  pinMode(DIGITAL_OUT_POWER, OUTPUT); 
  digitalWrite(DIGITAL_OUT_POWER, 1);

  frontSensor.attach(12);
  leftWheel.attach(6);  // S11 (on port S6)
  rightWheel.attach(7); // S12 (on port S6)
  
  leftWingServo.attach(11);
  rightWingServo.attach(8);
  leftArmServo.attach(10);
  rightArmServo.attach(9);
  gateServo.attach(13);
  
  initColourView();
  
  //WHISKER STUFF
    cli();
  attachInterrupt(5, WISR, FALLING); //enable interrupt0 (pin2)
  pinMode(2, INPUT);
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
  initColourView();
  updateSensors();
  currentSensor = determineWallFollow();
  setHomeColour();
  frontSensor.write(SENSOR_MIDDLE);
  
}


// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkSwitches() {
  powerSwitch.updateSwitch();
  limitRamp.updateSwitch();
  
  switch (limitRamp.switchState) {
    case SWITCH_ON:
        collect_trigger = true;
    break;
    
    case SWITCH_OFF:
        if (collect_trigger) {
            weightCollect = true;
            collect_trigger = false;
        }
    break;
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



int startTime = 0;
bool millisDelay (int DelayTime){
   bool goTime = false;
   if(startTime == 0){
      startTime = millis(); 
   }
   if ((millis() - startTime) >= DelayTime){
      goTime = true;
      startTime = 0;
   } 
   return goTime;
}


// Updates the front, left and right infa-red sensors
void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
  infaBottom.updateSensor();
  
  currentSensor.updateSensor();
}

void sweepAll (void) {
  leftArm.sweep(leftArmServo);
  rightArm.sweep(rightArmServo);
  gateArm.sweep(gateServo);
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
  break;
  
  case STATE_OFF:
    fullStop();
   navigationState.updateState(STATE_SEARCHING);
  break;
  }
  tick++;
}


