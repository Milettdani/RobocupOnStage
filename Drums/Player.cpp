// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#include "Arduino.h"                                                                                                            // Include libraries
#include "Player.h"
#include <FastLED.h>
#include "Melody.h"


void Player::begin() { // ----------------------------------------------------------------------------------------------------- // Begin function
  for (int i = 0; i < 7; i++) pinMode(SOLENOIDS[i], OUTPUT);                                                                     // Set pinMode for solenoids
                                                                                                  // Set pinMode for buildt in LED
  FastLED.addLeds<WS2812, LED_PIN, BRG>(leds, NUM_LEDS);                                                                        // Set up FastLed library
  FastLED.setBrightness(64);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  reset();
}
void Player::reset() {
  FastLED.clear();
  FastLED.show();
  for(byte solenoid : SOLENOIDS)
    digitalWrite(solenoid, LOW);
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
void Player::startPlaying() {
  isPlaying = true;
  startTime = millis(), noteTime = startTime;
}
void Player::stopPlaying() {
  isPlaying = false;
  Serial.println("\nEND\n\n");
  reset();
}

unsigned long Player::play(int dd[], int as, double at, unsigned long startTime, unsigned long noteTime) {
  int t = (millis() - startTime) / (at * 1000);
  if(t >= as) return 0;
  noteTime += (at * 1000);
  bool keyArray[7] = {0};
  Serial.println();
  for (int i=0; i<7; i++) {
    keyArray[i] = dig(toDec(dd[t]), i);
    digitalWrite(SOLENOIDS[i], keyArray[i]);
    Serial.print(keyArray[i]);
  }
  for(int i = 0; i < sizeof(keyArray) / sizeof(keyArray[0]); i++)
    for(int n = 0; n < 2; n++)
      leds[ledRemap[i]*2+n] = keyArray[i] ? CRGB::Red : CRGB::Black;
  FastLED.show();
  return noteTime;
}
void Player::main() {
  while(Serial.available() > 0) {
    byte data = Serial.read();    
    if(data == '1') {
      startPlaying();
    }
    else if(data == '2') {
      stopPlaying();
    }
    else if(data == 'S') {
      arrSize = Serial.readStringUntil('X').toInt();
      d[arrSize] = {0};
      for(int i = 0; i < arrSize; i++)
        d[i] = Serial.readStringUntil('X').toInt();
      arrayTime = Serial.readStringUntil('X').toDouble();

      startPlaying();
    }
  }

  //PLAY
  if(isPlaying){
    noteTime = play(d, arrSize, arrayTime, startTime, noteTime);
    if(!noteTime) stopPlaying();
  }
}
