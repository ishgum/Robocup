
#include "WaveArm.h"





WaveArm::WaveArm(void)
{
  currentAngle = 0;
  currentDirection = ARM_CLOCKWISE;

}

void WaveArm::armPos() {
    currentAngle = currentAngle + currentDirection;
    if (currentAngle >= MAX_ANGLE) {
      currentDirection = ARM_ANTI;
    }
    if (currentAngle <= MIN_ANGLE) {
      currentDirection = ARM_CLOCKWISE;
    }
    //Serial.print("currentAngle: ");
    //Serial.println(currentAngle);
}

void WaveArm::waveArm(bool waving, Servo servo, unsigned long tick){
    if (tick % 10 == 0 && waving) {
      servo.write(currentAngle); 
      armPos();
   }
}

//called when weight located
//move arm to centre position
//if weight still not there
//assume weight to be on outside
//rotate CW until weight hit
//sit, good boy!

void WaveArm::moveToCentre() {
  delay(100);///////////////////////////BADBADBADBADBADBADBADBAD????????????????????????????????????????///////////////////
  currentAngle += ARM_ANTI;
}


//moves arm to centre
bool WaveArm::align(Servo servo){
  centred = false;
  moveToCentre();
  if(currentAngle == CENTRE_ANGLE){
    centred = true;
  }
  servo.write(currentAngle);
  return centred;
}

