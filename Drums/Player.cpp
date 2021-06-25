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

void Player::startPlayingInter()
{
  for (int t = 0; t<arrSize; t++) {
    bool keyArray[7] = {0};
    Serial.println();
    for (int i=0; i<7; i++) {
      keyArray[i] = dig(toDec(d[t]), i);
      digitalWrite(SOLENOIDS[i], keyArray[i]);
      //Serial.println("helo");
      Serial.print(keyArray[i]);
    }
    for(int i = 0; i < sizeof(keyArray) / sizeof(keyArray[0]); i++)
      for(int n = 0; n < 2; n++)
        leds[ledRemap[i]*2+n] = keyArray[i] ? CRGB::Red : CRGB::Black;
    FastLED.show();

    delay(arrayTime*1000);
  }
}

void Player::startInteract()
{
  //Serial.println("wating for I and helo");
  bool s = false;
  while (!s) {
    while(Serial.available() > 0) {
      //Serial.println("inside while");
      byte data = Serial.read();
      if(data == 'I') {
        //for (int i = 0; i<arrSize; i++) Serial.println(d[i]);
        //Serial.println("looped");
        //Serial.println("found I!! :)");
        startPlayingInter();
      }
    }
  }
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
  //Serial.println("helo");
  isPlaying = true;
  //Serial.println(isPlaying);
  for (int i = 0; i<arrSize; i++) {
    startTime = millis(), noteTime = startTime;
    main();
  }
}
void Player::stopPlaying() {
  isPlaying = false;
  Serial.println("\nEND\n\n");
  reset();
}

unsigned long Player::play(short dd[], short as, float at, unsigned long startTime, unsigned long noteTime) {
  //Serial.println("inside play");
  int t = (millis() - startTime) / (at * 1000);
  if(t >= as) return 0;
  noteTime += (at * 1000);
  bool keyArray[7] = {0};
  Serial.println();
  for (int i=0; i<7; i++) {
    keyArray[i] = dig(toDec(dd[t]), i);
    digitalWrite(SOLENOIDS[i], keyArray[i]);
    //Serial.println("helo");
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
    if(data == 'A') {
      startPlaying();
    }
    else if(data == 'B') {
      stopPlaying();
    }
    else if(data == 'S') {
      Serial.println("Got S");
      arrSize = (short)Serial.readStringUntil('X').toInt();
      //d = new short[arrSize];
      for(int i = 0; i < arrSize; i++)
        d[i] = (short)Serial.readStringUntil('X').toInt();
      arrayTime = Serial.readStringUntil('X').toFloat();
      //Serial.println("Got data");
      startInteract();
      //startPlaying();
    }
  }

  //PLAY
  if(isPlaying){
    //Serial.println("inside main");
    noteTime = play(d, arrSize, arrayTime, startTime, noteTime);
    if(!noteTime) stopPlaying();
  }
}
