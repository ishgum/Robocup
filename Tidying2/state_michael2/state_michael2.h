

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
  Sensors infaBottom(2);


  State powerState(STATE_OFF);
  State navigationState(STATE_WALL_FOLLOW);
  State driveState(STATE_STRAIGHT);
  State followState(STATE_LEFT_WALL);

  PID leftError;
  PID rightError;
  Switch powerSwitch(3);
  
  Arm leftArm(LEFT_SIDE, 0);
  Arm rightArm (RIGHT_SIDE, 180);
  Arm gateArm(RIGHT_SIDE, 90);

// State things

bool waving = true; //won't lose it here//////////////////////////////
bool centred = false;
  
  
 int leftValue = MOTOR_ZERO_VALUE;
int rightValue = MOTOR_ZERO_VALUE;

// RTOS
  
unsigned long long tick;  
 /**** Program ****/

#endif

