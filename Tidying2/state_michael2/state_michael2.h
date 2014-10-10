

#ifndef stateM_h
#define stateM_h

#include "Sensors.h"
#include "State.h"
#include "PID.h"
#include "Switch.h"
#include "Whisker.h"
#include "Arm.h"
#include "Motors.h"

/**** SET UP ****/


#define DIGITAL_OUT_POWER 49

#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30

#define WALL_FOLLOW_DISTANCE 300

// Peripherals

  Servo frontSensor;
  Servo leftWheel;
  Servo rightWheel;
  
  Servo leftWingServo;
  Servo rightWingServo;
  Servo leftArmServo;
  Servo rightArmServo;
  
  Servo gateServo;
  
  
  Whisker whisker;
  
  
  Sensors infaFront(4);
  Sensors infaLeft(0);
  Sensors infaRight(1);
  Sensors infaBottom(11);
  Sensors infaBelly(10);
  
  Sensors currentSensor(10);


  State powerState(STATE_OFF);
  State navigationState(STATE_SEARCHING);
  State driveState(STATE_STRAIGHT);
  State followState(STATE_LEFT_WALL);

  PID leftError(WALL_FOLLOW_DISTANCE);
  PID rightError(WALL_FOLLOW_DISTANCE);
  PID currentError(WALL_FOLLOW_DISTANCE);
  
  Switch powerSwitch(3, PULSE_ON, ANALOG);
  Switch limitFront(44, PULSE_OFF, DIGITAL);
  Switch limitRamp(45, PULSE_OFF, DIGITAL);
  Switch limitLeftWing(42, PULSE_OFF, DIGITAL);
  Switch limitRightWing(43, PULSE_OFF, DIGITAL);
  Switch limitWeight(41, PULSE_OFF, DIGITAL);
    
  Arm leftArm(LEFT_SIDE, 0);
  Arm rightArm (RIGHT_SIDE, 180);
  
  Arm rightWing(RIGHT_SIDE, 180);
  Arm leftWing(LEFT_SIDE, 180);
  Arm gateArm(RIGHT_SIDE, 90);

// State things  
  
 int leftValue = MOTOR_ZERO_VALUE;
int rightValue = MOTOR_ZERO_VALUE;

// RTOS
  
unsigned long long tick;  
 /**** Program ****/

#endif

