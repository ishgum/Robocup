#include <Servo.h> 

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>
#define DIGITAL_OUT_POWER 49


// State defines

#define ON 1
#define OFF 0
#define STRAIGHT 0
#define TURNING 1

#define CLOCKWISE 1
#define ANTI_CLOCKWISE -1


// Peripherals

Servo leftWheel;  // create servo object to control a servo 
Servo rightWheel;                 // a maximum of eight servo objects can be created 
Servo sweep;

int ana_frontDistance = 4; // analogue input pin
int ana_leftDistance = 1;
int ana_rightDistance = 0;
int ana_onoff = 3;

// State things

int turning = CLOCKWISE;

int state_on = 0;
int state_off = 0;
int current_state = OFF;
int action_state = STRAIGHT;


// Measurement variables

int desiredAngle = 0;
int error = 0;

// Magnometer stuff

float angles[3];
FreeSixIMU sixDOF = FreeSixIMU();
HMC5883L compass;

  
  
  
  
void setup() {
  Serial.begin(9600);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13);  // S12 (on port S6)
  sweep.attach(11); //S10 (on port S5)
  sweep.write(0);
  
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  compass = HMC5883L(); // init HMC5883
  
  compass.SetMeasurementMode(Measurement_Continuous);
  
  sixDOF.getEuler(angles);
  float desiredAngle = angles[0];
}




// State check with debouncing
void check_state (void) {
  if (analogRead(ana_onoff) == 0) {
   state_off = 0;
   state_on += 1;
  }
  if (analogRead(ana_onoff) != 0) {
   state_on = 0;
   state_off += 1;
  }
  
  if (state_on == 100) {
    current_state = ON;
    desiredAngle = angles[0];
  }
  if (state_off == 100) {
    current_state = OFF;
  }
  
  
  if (analogRead(ana_frontDistance) > 500 && current_state == ON) {
     action_state = TURNING;
     leftWheel.write(90);
     rightWheel.write(90);
     find_direction(); 
     }
}





void find_direction (void) {
  sweep.write(100);
  delay (500);
  if (analogRead(ana_frontDistance) > 500) {
    turning = CLOCKWISE;
    desiredAngle += 90;
  }
  else {
    turning = ANTI_CLOCKWISE;
    desiredAngle -= 90;
  }
    sweep.write(0);
}





void loop() {
  
  check_state();
  sixDOF.getEuler(angles);
  error = desiredAngle - angles[0];
  Serial.println(analogRead(ana_frontDistance));
  
  if (current_state == OFF) {
    leftWheel.write(90);
    rightWheel.write(90);
  }
  
  if (current_state == ON) {
    if (action_state == STRAIGHT) {
      leftWheel.write(120 + error);
      rightWheel.write(120 - error);
    }
    
    if (action_state == TURNING) {      
      leftWheel.write((90 + turning*30));
      rightWheel.write((90 - turning*30));
      
      if (abs(error) < 10) {
          action_state = STRAIGHT;
      }
    }
  }
}
