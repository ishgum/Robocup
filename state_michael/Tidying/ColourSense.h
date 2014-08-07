
#ifndef ColourSense_h
#define ColourSense_h

#include "Arduino.h"

#include "Adafruit_TCS34725.h"


#define redpin 3
#define greenpin 5
#define bluepin 6

#define BLACK 400
#define TOLERANCE 50
#define MAX_COLOUR 1000

#define ARENA 0
#define HOME 1
#define ENEMY 2

#define commonAnode true


class ColourSense
{
	public:
		ColourSense (void);
                void findColour(void);
                void init(void);
                void detectBase (void);
                void setHome (void);
                
                uint16_t colour, red, green, blue;
                int area;
	private:
                Adafruit_TCS34725 tcs;
                int homeColour;
};

#endif
