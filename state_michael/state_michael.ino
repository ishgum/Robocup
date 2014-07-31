#include <Servo.h> 

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

#include "Sensors.h"
#include "Motors.h"
#include "Navigation.h"


/**** SET UP ****/


#define DIGITAL_OUT_POWER 49

// State defines

#define ON 1
#define OFF 0
#define STRAIGHT 0
#define TURNING 1

#define WALL_FOLLOW 0

// Peripherals

Motors motors;
Servo sweep;


Sensors infaFront(4);
Sensors infaLeft(0);
Sensors infaRight(1);

int ana_onoff = 3; // analogue input pin


// State things

int turning_dir = CLOCKWISE;

int state_on = 0;
int state_off = 0;
int on_state = OFF;
int current_state = WALL_FOLLOW;
int action_state = STRAIGHT;
int following_wall = 0;


// Measurement variables

int desiredAngle = 0;
int error = 0;

// Magnometer stuff

float angles[3];
FreeSixIMU sixDOF = FreeSixIMU();
HMC5883L compass;
  
// RTOS

unsigned long tick = 0;
  
void setup() {
  Serial.begin(9600);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13);  // S12 (on port S6)
  //sweep.attach(11); //S10 (on port S5)
  //sweep.write(0);
  
  
  
 /**** Program ****/
  
  
  
void setup() {
  Serial.begin(9600);
 
  //Initialising magnet sensor
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  compass = HMC5883L(); // init HMC5883
  compass.SetMeasurementMode(Measurement_Continuous);
  sixDOF.getEuler(angles);
 
  float desiredAngle = angles[0];
  

}


void updateOnState (int stateChange) {
  if (stateChange == ON) {
    currentState = ON;
  if (stateChange == OFF) {
    currentState = OFF;
  }
  
void updateActionState (int stateChange) {
  if (currentState == ON) {
    if (stateChange == STRAIGHT) {
      actionState



// Turning on and off
void check_on (void) {
  if (analogRead(ana_onoff) != 0 && on_state == OFF) {
   state_off = 0;
   state_on += 1;
  }
  if (analogRead(ana_onoff) == 0 && on_state == ON) {
   state_on = 0;
   state_off += 1;
  }
  
  if (state_on == 10) {
    on_state = ON;
  }
  if (state_off == 10) {
    on_state = OFF;
  }
}


// Finds the error between the current angle and the desired

void find_error (void) {
  sixDOF.getEuler(angles);
  error = desiredAngle - angles[0]; 
}



void navigateCorner (void) {
  if (infaFront.found == true) {
    motors.fullStop();
    updateState(TURNING);
    if (infaLeft.found == true) {
      turning_dir = CLOCKWISE;
      desiredAngle += 90;
    }
    else if (infaRight.filteredRead > 300) {
    turning_dir = ANTI_CLOCKWISE;
    desiredAngle -= 90;
    }
  }
}
      

void updateSensors (void) {
  infaFront.updateSensor();
  infaLeft.updateSensor();
  infaRight.updateSensor();
}



void determine_follow_wall(void) {
  if (infaLeft.filteredRead > infaRight.filteredRead) {
    following_wall = infaLeft.filteredRead;
  }
  else {
    following_wall = infaRight.filteredRead;
  }
}


void follow_wall_mode (void) {
  find_Wall();
  determine_follow_wall();
  if (action_state == STRAIGHT) {
    int straight_error = error + (following_wall - 400)/20;
    motors.drive(error, 50, FORWARDS);
  }
  if (action_state == TURNING) {      
    motors.turn(50, turning_dir);
    
    if (abs(error) < 10) {
        action_state = STRAIGHT;
    }
  } 
}
  



//void random_search_mode (void) {
  



void loop() {
  
  check_on();
  
  if (tick % 10 == 0) {
  updateSensors();
  }
  
  if (on_state == OFF) {
    motors.fullStop();
  }
  
  if (on_state == ON) {
      find_error();
      
      if (current_state == WALL_FOLLOW) {
        follow_wall_mode();
      }
  }
  tick++;
}

