

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
  
  pinMode(38, INPUT);
  pinMode(39, INPUT);
  pinMode(40, INPUT);
  pinMode(41, INPUT);
  pinMode(42, INPUT);
  pinMode(43, INPUT);
  pinMode(44, INPUT);
  pinMode(45, INPUT);
  
}

void WISR(void)
{
    whisker.count++;
}



void initRobot(void) {
  driveState.setToDefault();
  navigationState.setToDefault();
  setMotorDir(MOTOR_FORWARDS);
  //initColourView();
  
  for (int i = 0; i < 8; i++) {
    updateSensors();
  }
  
  currentSensor = determineWallFollow();

  frontSensor.write(SENSOR_MIDDLE);

  rightArm.setDesiredAngle(120);
  leftArm.setDesiredAngle(40);
  gateArm.setDesiredAngle(0);
  
  setTurnSpeed(DEFAULT_SPEED);
  setMotorSpeed(DEFAULT_SPEED);
}

int setMode = 0;
// Checks the state of the on switch, if the switch is on the power is supplied to the robot

void checkSwitches() {
  powerSwitch.updateSwitch();
  limitRamp.updateSwitch();
  limitLeftWing.updateSwitch();
  limitRightWing.updateSwitch();
  limitFront.updateSwitch();
  limitWeight.updateSwitch();

  
  //Serial.print(limitRightWing.switchState); Serial.print('\t'); Serial.print(limitLeftWing.switchState); Serial.print('\t'); Serial.print(limitFront.switchState); Serial.print('\t'); Serial.print(limitWeight.switchState); Serial.print('\t'); Serial.println(limitRamp.switchState); 
  
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
  infaBottom.updateSensor();
  infaBelly.updateSensor();
  
  
  currentSensor.updateSensor();
}


void sweepAll (void) {
  leftArm.sweep(leftArmServo);
  rightArm.sweep(rightArmServo);
  gateArm.sweep(gateServo);
  
  rightWing.sweep(rightWingServo);
  leftWing.sweep(leftWingServo);
}


void loop() {
  
  
  checkSwitches();
  sweepAll();
  updateSensors();
  driveRobot();

     
  switch (powerState.returnState()) {
    case STATE_ON:    
      findWeights();
      
      if (tick % 100 == 0) {
        //checkColour();
      }
      if (tick % 4 == 0) {
        navigateRobot();
      }
      
      if (tick % 5 == 0) {
        //infraredLocate();
      }
      
      if (tick % 5 == 0) {
        checkWings();
      }
      
  break;
  
  case STATE_OFF:
     driveState.updateState(STATE_STOPPED);
  break;
  }
  tick++;
}


