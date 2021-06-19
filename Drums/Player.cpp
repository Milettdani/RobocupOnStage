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

void Player::updateSerial() { // ---------------------------------------------------------------------------------------------- // UpdateSerial function
  while(Serial.available() > 0) {
    byte data = Serial.read();
    if(data == '1') {
      if(isPlaying) break;
      play();
    }
    else if(data == '2') {
      if(!isPlaying) break;
      isPlaying = false;
      for(int solenoid : SOLENOIDS)
        digitalWrite(solenoid, LOW);
      for(int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++)
        leds[i] = CRGB::Black;
      FastLED.show();
    }
    else
      Serial.print(data);
  }
}

int Player::dig(long val, int n) { // ----------------------------------------------------------------------------------------- // ??? function
  String g = String(val);
  return String(g[n+1]).toInt();
}

long Player::toDec(int dec) { // ---------------------------------------------------------------------------------------------- // Convert to decimal function
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
  return b3.toInt();
}

void Player::play() { // ------------------------------------------------------------------------------------------------------ // Play melody function
  isPlaying = true;
  unsigned long startTime = millis(), noteTime = 0;
  
  for (int t=0; t<arrSize; t++) {
    noteTime = !noteTime ? startTime : noteTime, noteTime += (arrayTime * 1000);
    bool keyArray[7] = {0}; long dec = toDec(d[t]);
    for(int i = 0; i < 7; i++) {
      keyArray[i] = dig(dec, i);
      Serial.print(keyArray[i]);
      digitalWrite(SOLENOIDS[i], keyArray[i]);
    }
    for(int i = 0; i < sizeof(keyArray) / sizeof(keyArray[0]); i++)
      for(int n = 0; n < 2; n++)
        leds[ledRemap[i]*2+n] = ledRemap[i] == 0 || ledRemap[i] == 1 ? keyArray[i] ? CRGB::Maroon : CRGB::White : keyArray[i] ? CRGB::Green : CRGB::White;
    FastLED.show();
    
    Serial.println();
    while(millis() < noteTime) { updateSerial(); if(!isPlaying) return; }
  }
  isPlaying = false;
}
