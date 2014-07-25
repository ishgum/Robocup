#include <Servo.h> 

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

#define DIGITAL_OUT_POWER 49
#define FILTER_SIZE 8

struct Sensor {
  
  unsigned int port;
  unsigned int currentRead;
  unsigned int index;
  unsigned int filterArray[FILTER_SIZE];
  unsigned int filteredRead;
};


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

<<<<<<< .mine
Sensor infaFront;
Sensor infaLeft;
Sensor infaRight;
=======
int ana_frontDistance = 4; // analogue input pin
int ana_leftDistance = 0;
int ana_rightDistance = 1;
int ana_onoff = 3;
>>>>>>> .r5

int ana_onoff = 3; // analogue input pin


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

  
// RTOS

unsigned long tick = 0;
  
  
void setup() {
  Serial.begin(9600);
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13);  // S12 (on port S6)
  
<<<<<<< .mine
  infaFront.port = 4;
  infaLeft.port = 0;
  infaRight.port = 1;
  
  infaFront.index = 0;
  infaLeft.index = 0;
  infaRight.index = 0;
  
  
  Serial.println("Got here");
  
=======
  Serial.println("Got here");
  
>>>>>>> .r5
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  compass = HMC5883L(); // init HMC5883
  compass.SetMeasurementMode(Measurement_Continuous);
  Serial.println("Got here 2");
  
  sixDOF.getEuler(angles);
  
  Serial.println("Got here 3");
  
  float desiredAngle = angles[0];
  
  Serial.println("Got here 4");
}




// State check with debouncing
void check_state (void) {
  if (analogRead(ana_onoff) != 0 && current_state == OFF) {
   state_off = 0;
   state_on += 1;
  }
  if (analogRead(ana_onoff) == 0 && current_state == ON) {
   state_on = 0;
   state_off += 1;
  }
  
  if (state_on == 10) {
    current_state = ON;
    desiredAngle = angles[0];
  }
  if (state_off == 10) {
    current_state = OFF;
  }
}





void find_direction (void) {
  delay (500);
  if (infaFront.filteredRead > 500) {
    turning = CLOCKWISE;
    desiredAngle += 90;
  }
  else {
    turning = ANTI_CLOCKWISE;
    desiredAngle -= 90;
  }
    sweep.write(0);
}



void stop_motors (void) {
    leftWheel.write(90);
    rightWheel.write(90);
}




void find_error (void) {
  sixDOF.getEuler(angles);
  error = desiredAngle - angles[0]; 
}


void find_Wall (void) {
<<<<<<< .mine
    if (infaFront.filteredRead > 500) {
      stop_motors();
      if (infaLeft.filteredRead > 300) {
        turning = CLOCKWISE;
      }
    }
}
=======
    int front_Distance = analogRead(ana_frontDistance);
    if (front_Distance > 500) {
      stop_motors();
      if (analogRead(ana_leftDistance) > 300) {
        turning = CLOCKWISE;
      }
    }
}
      
>>>>>>> .r5



struct Sensor updateSensor (Sensor sensor) {
  sensor.currentRead = analogRead(sensor.port);
  
  sensor.filterArray[sensor.index] = sensor.currentRead;
  
  unsigned int temp_sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++)
  {
    temp_sum += sensor.filterArray[i];
  }
  
  sensor.filteredRead = temp_sum / FILTER_SIZE;
  
  sensor.index++;
  if (sensor.index == (FILTER_SIZE)) {
    sensor.index = 0;
  }
  return sensor;
}
      

void updateSensors (void) {
  updateSensor (infaFront);
  updateSensor (infaLeft);
  updateSensor (infaRight);
}
  


void loop() {
  
  check_state();
  
  if (current_state == OFF) {
    stop_motors();
  }
  
<<<<<<< .mine
  if (tick % 5000 == 0) {
  Serial.print("Left: "); Serial.print(infaFront.filteredRead);
  Serial.print("\t Right: "); Serial.print(infaLeft.filteredRead);
  Serial.print("\t Front: "); Serial.println(infaRight.filteredRead);
  }
=======
  if (tick % 5000 == 0) {
  Serial.print("Left: "); Serial.print(analogRead(ana_leftDistance));
  Serial.print("\t Right: "); Serial.print(analogRead(ana_rightDistance));
  Serial.print("\t Front: "); Serial.println(analogRead(ana_frontDistance));
  }
>>>>>>> .r5
  
  if (current_state == ON) {
    if (tick % 1000 == 0) {
      find_error();
    }
    
    if (action_state == STRAIGHT) {
      leftWheel.write(140 + error*3);
      rightWheel.write(140 - error*3);
    }
    
    if (action_state == TURNING) {      
      leftWheel.write((90 + turning*30));
      rightWheel.write((90 - turning*30));
      
      if (abs(error) < 10) {
          action_state = STRAIGHT;
      }
    }
  }
<<<<<<< .mine
  tick++;
}
=======
  tick++;
}
>>>>>>> .r5
