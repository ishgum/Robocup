#ifndef GATE_H
#define GATE_H

#include "Arduino.h"
#include "Servo.h"
#include "schedule.h"

#define ANGLE_MAX 120
#define ANGLE_MIN 90

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
