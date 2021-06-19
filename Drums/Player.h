// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include <FastLED.h>

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    void play(int dd[], int as, double at);
    void main();
    void begin();
  private:                                                                                                                      // Private things
    int dig(long val, int n);
    long toDec(int dec);
    const byte SOLENOIDS[8] = {A0, A1, A2, A3, A4, A5, 11};                                                                 // Solenoid pins
    const static byte dirPin = 6, stepPin = 7, enPin = 5;                                                               // Motor and Debug pins
    const static byte NUM_LEDS = 16, LED_PIN = 5; CRGB leds[NUM_LEDS];
    const static byte ledRemap[8] = {6, 7, 3, 0, 1, 5, 2, 4};
};

#endif
