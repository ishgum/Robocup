#ifndef GATE_H
#define GATE_H

#include "Arduino.h"
#include "Servo.h"
#include "schedule.h"

#define ANGLE_MAX 20
#define ANGLE_MIN 0

extern Servo gateServo;

class Gate
{
	public:
		Gate(void);
		bool lowerGate(void);
		bool raiseGate(void);

	private:
		int angle;
                bool gate_down;
	
};
#endif
