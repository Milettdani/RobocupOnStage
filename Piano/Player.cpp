// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#include "Arduino.h"                                                                                                            // Include libraries
#include "Player.h"
#include "Melody.h"

int Player::mmove(int value)
{
  Serial.println("MOVING");
  Serial.println(value);
  int startTime = millis();
  if (value == 0) return 0;
  else if (value < 0) digitalWrite(dirPin, HIGH);                                                                               // Change MoveDir
  else if (value > 0) digitalWrite(dirPin, LOW);
  for (int i = 0; i<8; i++) {
    digitalWrite(solenoid[i], LOW);
  }
  // Change MoveDir
  for (int i = 0; i < 588 * abs(value); i++) {                                                                                  // Move
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(80);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(80);
  }
  return millis() - startTime;
}

int Player::dig(long val, int n)
{
  String g = String(val);
  return String(g[n+1]).toInt();
  /*
  if (n >= 8 - g.length()) return String(g[n - (8-g.length())]).toInt();
  else return 0;*/
}

int Player::power(int a, int b)
{
  int f = 1;
  for (int i = 0; i<b; i++) {
    f *= a;
  }
  return f;
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


void Player::play()
{
  //move to starting pos then wait
  mmove(startmove);
  //delay(5000);

  int wt;
  long dec;
  unsigned long startTime = millis(), noteTime = 0;
  for (int t=0; t<arrSize; t++) {
    Serial.println("\n");
    Serial.print("t = ");
    Serial.println(t);
    Serial.println("\n");
    noteTime = !noteTime ? startTime : noteTime; noteTime += (arrayTime * 1000);
    dec = toDec(p[t][1]);
    for (int b=0; b<8; b++) {
      //Serial.println(dec);
      //Serial.println(b);
      digitalWrite(solenoid[b], dig(dec, b));
      Serial.println(dig(dec, b));
      //Serial.println(dig(dec, b));
      //Serial.println("\n");
    }
    Serial.println("\n");
    //Serial.println("Moving...");
    //Serial.println(p[t][0]);
    while(millis() - startTime < noteTime);
    Serial.print("waiting ");
    Serial.println(arrayTime*1000);
    pos += p[t][0];
    wt = mmove(p[t][0]); //wasted time while moving in ms
    Serial.print("wt = ");
    Serial.println(wt);
    Serial.println("\n");
    if (round(((float)wt/1000)/arrayTime) > 0) t += round(((float)wt/1000)/arrayTime) -1;
    //Serial.println("\n");
  }
}

void Player::begin()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("Starting\n");

  for (int i = 0; i < 8; i++) {pinMode(solenoid[i], OUTPUT); digitalWrite(solenoid[i], LOW);}
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW); 

  play();
  mmove(28 - pos); // Move to interraction (C)

  float inter[32]; // timestamps for when to play chords
  int startTime = millis();
  short counter = 0;
  while (true) {
    if (millis() - startTime == inter[counter]*1000) {
      digitalWrite(solenoid[0], HIGH);
      digitalWrite(solenoid[2], HIGH);
      digitalWrite(solenoid[4], HIGH);
      delay(100);
      digitalWrite(solenoid[0], LOW);
      digitalWrite(solenoid[2], LOW);
      digitalWrite(solenoid[4], LOW);
      counter++;
    }
  }


  digitalWrite(enPin, HIGH);
}
