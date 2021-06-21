// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include <FastLED.h>

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    unsigned long play(int dd[], int as, double at, unsigned long startTime, unsigned long noteTime);
    void main();
    void begin();
    bool isPlaying = false;
    unsigned long startTime, noteTime;
  private:                                                                                                                      // Private things
    int dig(long val, int n);
    long toDec(int dec);
    void reset(), startPlaying(), stopPlaying();
    const byte SOLENOIDS[8] = {A0, A2, A3, A4, A5, 11, 12};                                                                 // Solenoid pins
    const static byte dirPin = 6, stepPin = 7, enPin = 5;                                                               // Motor and Debug pins
    const static byte NUM_LEDS = 16, LED_PIN = 5; CRGB leds[NUM_LEDS];
    const byte ledRemap[8] = {4, 3, 0, 1, 5, 2, 6};
};

#endif
