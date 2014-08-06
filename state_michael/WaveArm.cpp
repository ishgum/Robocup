
#include "WaveArm.h"





WaveArm::WaveArm(void)
{
  currentAngle = 0;
  currentDirection = ARM_CLOCKWISE;

}


void WaveArm::armPos(void) {
    currentAngle = currentAngle + currentDirection;
    if (currentAngle >= MAX_ANGLE) {
      currentDirection = ARM_ANTI;
    }
    if (currentAngle <= MIN_ANGLE) {
      currentDirection = ARM_CLOCKWISE;
    }
}

