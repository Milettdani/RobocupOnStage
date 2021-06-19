// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#include "Arduino.h"                                                                                                            // Include libraries
#include "Player.h"
#include <FastLED.h>
#include "Melody.h"

void Player::begin() { // ----------------------------------------------------------------------------------------------------- // Begin function
  for (int i = 0; i < 7; i++) pinMode(SOLENOIDS[i], OUTPUT);                                                                     // Set pinMode for solenoids
  pinMode(LED_BUILTIN, OUTPUT);                                                                                                 // Set pinMode for buildt in LED
  FastLED.addLeds<WS2812, LED_PIN, BRG>(leds, NUM_LEDS);                                                                        // Set up FastLed library
  FastLED.setBrightness(64);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  for(int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

int Player::dig(long val, int n)
{
  String g = String(val);
  return String(g[n+1]).toInt();
  /*
  if (n >= 8 - g.length()) return String(g[n - (8-g.length())]).toInt();
  else return 0;*/
}

long Player::toDec(int dec)
{
  String b2 = "";
  while (dec > 0) {
    if(dec%2 == 0) b2 += "0";
    else b2 += "1";
    dec >>= 1;
  }

  String b3 = "";
  for (int i = b2.length()-1; i>=0; i--) {
    b3 += String(b2[i]);
  }
  //Serial.println(b3);
  //Serial.println((long)b3.toInt());
  //Serial.println("\n");
  return b3.toInt();
}

void Player::play(int dd[], int as, double at)
{
  int wt;
  long dec;

  unsigned long startTime = millis(), noteTime = 0;
  
  for (int t=0; t<as; t++) {
    noteTime = !noteTime ? startTime : noteTime; noteTime += (at * 1000);
    dec = toDec(dd[t]);
    for (int b=0; b<7; b++) {
      digitalWrite(SOLENOIDS[b], dig(dec, b));
      Serial.println(dig(dec, b));
    }
    Serial.println("\n");
    while(millis() < noteTime);
  }
}
void Player::main() {
  play(d, arrSize, arrayTime);
/*
  const int arrayTime2;
  const int arrSize2;
  const int d2[arrSize2]; //Get these from communication

  //Wait for start 2
  play(d2, arrSize2, arrayTime);*/
}
