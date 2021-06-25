// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include "Beat.h"
#include <FastLED.h>

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    void begin(), serialUpdate();
    void moveNote(int value);
    int toBeep(String text);
    void playBeat(Beat beat, Beat nextBeat, int bpm),
    playMelodies(), start(), ecuador(), pijanoo(), zombieNation(), stereoLove(),
    lamourToujours(), betterOffAlone(), wakeMeUp(), imBlue();
    int counter = 0, startTime = 0;
    bool isMuted = false, isOverwritten = false;
    void updateSerial();
    void flag();
  private:                                                                                                                      // Private things
    const byte solenoids[8] = {A0, A2, A3, A4, A5, 11, 12, A1};                                                                 // Solenoid pins
    const byte dirPin = 6, stepPin = 7, enPin = 5, debugPin = 13;                                                               // Motor and Debug pins
    int melodyBPM = 120; long lastTime = 0; 
    const static int NUM_LEDS = 16, LED_PIN = 5; CRGB leds[NUM_LEDS];
    const int ledRemap[8] = {4, 3, 0, 1, 5, 2, 6, 7};
    void(* resetFunc) (void) = 0;
    long overrideTime = 0;
    byte overridePin = solenoids[3];
    
};

#endif
