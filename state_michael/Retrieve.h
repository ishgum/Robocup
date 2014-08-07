#ifndef Retrieve_h
#define Retrieve_h

#include "Arduino.h"
#include "Motors.h"

#define CW 1
#define CCW -1

unsigned int target = Wavearm.currentAngle;
unsigned int rotation = 0;
unsigned int current = Magno.currentAngle;
unsigned int p_rotation = 0;
unsigned int motor_speed = 0;

int P = 0;
int D = 0;
int KP = 1;
int KD = 1;



#endif
