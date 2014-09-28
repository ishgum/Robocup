#ifndef GATE_H
#define GATE_H

#include "Arduino.h"

class Gate
{
	public:
		Gate(void);
		bool lowerGate(void);
		bool raiseGate(void);

	private:
		int angle;
	
};
#endif
