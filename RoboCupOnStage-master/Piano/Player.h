// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include "Beat.h"

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    void begin();
    void moveNote(int value);
    int toBeep(String text);
    void playBeat(Beat beat, Beat nextBeat, int bpm);
    void playInteract(int interSize, float inter[]);
    void start(), ecuador(), pijanoo(), zombieNation(), stereoLove();
    void lamourToujours(), betterOffAlone(), wakeMeUp(), imBlue();
    void playMelodies(), updateSerial();
    int counter = 0, startTime = 0;
    bool played = false;
  private:                                                                                                                      // Private things
    const byte solenoids[8] = {A0, A1, A2, A3, A4, A5, 11, 12};                                                                 // Solenoid pins
    const byte dirPin = 6, stepPin = 7, enPin = 5, debugPin = 13;                                                               // Motor and Debug pins
    int melodyBPM = 120; long lastTime = 0; 
    void(* resetFunc) (void) = 0;
};

#endif
