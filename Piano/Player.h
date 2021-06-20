// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#ifndef Player_h                                                                                                                // Include libraries
#define Player_h
#include "Arduino.h"
#include "Melody.h"
#include <FastLED.h>

class Player { // ------------------------------------------------------------------------------------------------------------- // Player class
  public:                                                                                                                       // Public things
    const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 }; //move after notes played: e.g.: {4, 384}: play(384), wait arrayTime, move 4
    const int dirPin = 6, stepPin = 7, enPin = 5;

int mmove(int value);

int dig(long val, int n);

int power(int a, int b);

long toDec(int dec);

int pos = startmove;
void play();
void begin();
};

#endif
