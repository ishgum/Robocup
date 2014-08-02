
#include "Motors.h"

Motors::Motors(void)
{
  Servo leftWheel;
  Servo rightWheel;
  leftWheel.attach(12);  // S11 (on port S6)
  rightWheel.attach(13); // S12 (on port S6)
}


// Updates a single sensor using a MAF

void Motors::fullStop (void) {
  leftWheel.write(ZERO_VALUE);
  rightWheel.write(ZERO_VALUE); 
}


void Motors::drive (signed int error, signed int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  
  leftWheel.write(ZERO_VALUE + dir*(speedMotors + error));
  rightWheel.write(ZERO_VALUE + dir*(speedMotors - error));
}


void Motors::turn (unsigned int speedPercent, signed int dir) {
  unsigned int speedMotors = (FULL_SPEED*speedPercent)/100;
  if (speedMotors > FULL_SPEED) {
    speedMotors = FULL_SPEED;
  }
  leftWheel.write(ZERO_VALUE + dir*speedMotors);
  rightWheel.write(ZERO_VALUE - dir*speedMotors);
}
