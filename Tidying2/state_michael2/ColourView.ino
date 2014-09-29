

#include "Adafruit_TCS34725.h"
#include "state_michael2.h"

//
//#define redpin 3
//#define greenpin 5
//#define bluepin 6
//
#define COLOUR_BLACK 400
#define COLOUR_TOLERANCE 50
#define MAX_COLOUR 1000

#define AREA_ARENA 0
#define AREA_HOME 1
#define AREA_ENEMY 2

#define EXPECTED_BOTTOM 500
#define DISTANCE_TOLERANCE 20


Adafruit_TCS34725 tcs;
static int homeColour;


uint16_t colour, red, green, blue;

int area;

void initColourView() {
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  setHomeColour();
  
}




void findColour(void)
{
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &colour);
  tcs.setInterrupt(true);  // turn off LED 
}


void detectBase(void) {
  if (abs(infaBottom.filteredRead - EXPECTED_BOTTOM) < DISTANCE_TOLERANCE) {
    area = AREA_ARENA;
  }
  
  if (colour < COLOUR_BLACK) {
    area = AREA_ARENA;
  }
  else if (colour < (homeColour + COLOUR_TOLERANCE) && colour > (homeColour - COLOUR_TOLERANCE)) {
    area = AREA_HOME;
  }
  else if (colour < MAX_COLOUR) {
    area = AREA_ENEMY;
  }
  Serial.println(area);
}


void setHomeColour(void) {
  findColour();
  homeColour = colour;
}



void checkColour(void) {
  findColour();
  detectBase();
  if (area == AREA_ENEMY) {
    navigationState.updateState(STATE_EVACUATE);
  }
  if (area == AREA_ARENA) {
    setMotorSpeed(70);
    setTurnSpeed(70);
  }
  if (area == AREA_HOME) {
    setMotorSpeed(50);
    setTurnSpeed(50);
  }
}


