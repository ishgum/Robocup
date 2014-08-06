
#ifndef ColourSense_h
#define ColourSense_h

#include "Arduino.h"

#include "Adafruit_TCS34725.h"


#define redpin 3
#define greenpin 5
#define bluepin 6


#define commonAnode true


class ColourSense
{
	public:
		ColourSense (void);
                void findColour(void);
                void init(void);
                
                uint16_t colour, red, green, blue;
	private:
                Adafruit_TCS34725 tcs;
};

#endif
