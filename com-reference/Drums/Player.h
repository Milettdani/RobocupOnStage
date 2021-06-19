// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include <FastLED.h>

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    void play();
    void begin();
    void updateSerial();
  private:                                                                                                                      // Private things
    int dig(long val, int n);
    long toDec(int dec);
    bool isPlaying = false;
    const byte SOLENOIDS[8] = {A0, A1, A2, A3, A4, A5, 11};                                                                 // Solenoid pins
    const byte dirPin = 6, stepPin = 7, enPin = 5;                                                               // Motor and Debug pins
    const static int NUM_LEDS = 16, LED_PIN = 5; CRGB leds[NUM_LEDS];
    const int ledRemap[8] = {6, 7, 3, 0, 1, 5, 2, 4};
};

#endif
