

#ifndef stateM_h
#define stateM_h

#include "Sensors.h"
#include "State.h"
#include "PID.h"
#include "Switch.h"
#include "Whisker.h"
#include "Arm.h"
#include "Motors.h"
#include "schedule.h"

/**** SET UP ****/


#define DIGITAL_OUT_POWER 49

#define SENSOR_MIDDLE 105
#define SENSOR_ANGLE 30

#define WALL_FOLLOW_DISTANCE 350

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
  
  Sensors currentSensor(10);


  State powerState(STATE_OFF);
  State navigationState(STATE_SEARCHING);
  State driveState(STATE_STRAIGHT);
  State followState(STATE_LEFT_WALL);

  PID leftError(WALL_FOLLOW_DISTANCE);
  PID rightError(WALL_FOLLOW_DISTANCE);
  PID currentError(WALL_FOLLOW_DISTANCE);
  
  Switch powerSwitch(3, 0, PULSE_ON);
  Switch limitRamp(10, 400, PULSE_OFF);
    
  Arm leftArm(LEFT_SIDE, 0);
  Arm rightArm (RIGHT_SIDE, 180);
  Arm gateArm(RIGHT_SIDE, 90);

// State things  
  
 int leftValue = MOTOR_ZERO_VALUE;
int rightValue = MOTOR_ZERO_VALUE;

// RTOS
  
unsigned long long tick;  
 /**** Program ****/

#endif

