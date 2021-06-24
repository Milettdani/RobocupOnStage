// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#include "Arduino.h"                                                                                                            // Include libraries
#include "Player.h"
#include "Beat.h"
    
void Player::begin() { // ----------------------------------------------------------------------------------------------------- // Constuctor
  for (int solenoid : solenoids) { pinMode(solenoid, OUTPUT); digitalWrite(solenoid, LOW); }                                    // Setup Solenoid PinModes
  pinMode(stepPin, OUTPUT); pinMode(dirPin, OUTPUT);                                                                            // Motor PinModes
  pinMode(enPin, OUTPUT); pinMode(debugPin, OUTPUT);
  digitalWrite(enPin, LOW);
}

void Player::playInteract(int interSize, float inter[])
{
  bool start = false;
  while (!start) {
  while(Serial.available() > 0) {
    byte data = Serial.read();
    if(data == 'A') 
      start = true;
  }
  }
  unsigned long startTime = millis();
  for (int i = 0; i<interSize; i++) {
    while (millis() - startTime < inter[i]*1000);
    digitalWrite(solenoids[i%3 * 2], HIGH);
    Serial.println(i%3 * 2);
    int del = i<interSize-1 ? 1000*(inter[i+1] - inter[i]) -25 > 750 ? 750 : 1000*(inter[i+1] - inter[i]) -25 : 750;
    delay(del);
    digitalWrite(solenoids[i%3 * 2], LOW);
  }
}


void Player::moveNote(int value) { // ----------------------------------------------------------------------------------------- // Move Half Note
  if (value == 0) return 0;
  else if (value < 0) digitalWrite(dirPin, HIGH);                                                                               // Change MoveDir
  else if (value > 0) digitalWrite(dirPin, LOW);                                                                                // Change MoveDir
  for (int i = 0; i < 588 * abs(value); i++) {                                                                                  // Move
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(96);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(96);
  }
}
void Player::updateSerial() {
  while(Serial.available() > 0) {
    byte data = Serial.read();
    if(data == 'A' && !played) 
      playMelodies();
      played = true;
    else if(data == 'B')
      resetFunc();
  }
}
void Player::playBeat(Beat beat, Beat nextBeat, int bpm) { // ----------------------------------------------------------------- // Beat Player
  updateSerial();
  startTime = !startTime ? millis() : startTime;                                                                                // Start the Timer when the FirstBeat is Being Played
  bool startBin[8] = {0}; byte startBinCounter = 0, startKey = beat.key;                                                        // Define Local Variables
  while (startKey > 0) {                                                                                                        // Logic for BinaryConversation
    startBin[7 - startBinCounter++] = startKey % 2;
    startKey = startKey / 2;
  }
  bool cmplxA = beat.move == 0 && beat.key == nextBeat.key, cmplxB = beat.move != 0;                                            // Logic for Complex Timing
  float cmplxDel = cmplxA ? 60000 / bpm * 0.15 : cmplxB ? 112.896*abs(beat.move) : 0;                                             // Convert Logic into Values
  
  Serial.print(counter++);                                  Serial.print("  ");                                                 // SerialPrint Datas
  Serial.print(millis()-startTime);                         Serial.print("  ");
  Serial.print(lastTime);                                   Serial.print("  ");
  for (bool i : startBin) Serial.print(i == 0 ? "-" : "1"); Serial.print("  ");
  Serial.print(beat.time);                                  Serial.print("  ");
  Serial.print("CMPLXA="); Serial.print(cmplxA);            Serial.print("  ");
  Serial.print("CMPLXB="); Serial.print(cmplxB);            Serial.print("  ");
  Serial.print("MOVE="); Serial.print(beat.move);           Serial.print("  ");
  Serial.print(beat.debug);                                 Serial.println();

  lastTime += 60000 / bpm * beat.time;                                                                                          // Update the BeatEndTime
  for (byte i = 0; i < 8; i++) digitalWrite(solenoids[i], startBin[i]);                                                         // DigitalWrite Solenoids
  int beep = toBeep(beat.debug); if (beep) tone(debugPin, beep); else noTone(debugPin);                                         // Play Sound on Buzzer
  while(millis() < lastTime-cmplxDel+startTime);                                                                                // Wait with Sound
  for (byte i = 0; i < 8; i++) digitalWrite(solenoids[i], 0); noTone(debugPin);                                                 // Reset Solenoids
  moveNote(beat.move);                                                                                                          // Move
  while(millis() < lastTime+startTime);                                                                                         // Wait without Sound0
}
int Player::toBeep(String text) { // ------------------------------------------------------------------------------------------ // String to Hz
  return
    text == "C2" ?  65 : text == "C#2" ?  69 :                                                                                  // 2-line C
    text == "D2" ?  73 : text == "D#2" ?  77 :
    text == "E2" ?  82 :
    text == "F2" ?  87 : text == "F#2" ?  92 :
    text == "G2" ?  97 : text == "G#2" ? 103 :
    text == "A2" ? 110 : text == "A#2" ? 116 :
    text == "B2" ? 123 :
    text == "C3" ? 130 : text == "C#3" ? 138 :                                                                                  // 3-line C
    text == "D3" ? 146 : text == "D#3" ? 155 :
    text == "E3" ? 164 :
    text == "F3" ? 174 : text == "F#3" ? 184 :
    text == "G3" ? 195 : text == "G#3" ? 207 :
    text == "A3" ? 220 : text == "A#3" ? 233 :
    text == "B3" ? 246 :
    text == "C4" ? 264 : text == "C#4" ? 277 :                                                                                  // 4-line C
    text == "D4" ? 293 : text == "D#4" ? 311 :
    text == "E4" ? 329 :
    text == "F4" ? 349 : text == "F#4" ? 369 :
    text == "G4" ? 391 : text == "G#4" ? 415 :
    text == "A4" ? 440 : text == "A#4" ? 466 :
    text == "B4" ? 493 : 0;
}

void Player::playMelodies() { // ---------------------------------------------------------------------------------------------- // Play Melodies
  //start();  
  ecuador();
  pijanoo();
  zombieNation();
  stereoLove();
  lamourToujours();
  betterOffAlone();
  //wakeMeUp();
  imBlue();

  bool contin = true;
    while(contin)
      while(Serial.available() > 0)
        if(Serial.read() == 'S') {
          int dataLength = Serial.readStringUntil('X').toInt();
          float arrB[dataLength];// = new double[dataLength];
          for(int i = 0; i < dataLength; i++)
            arrB[i] = Serial.readStringUntil('X').toDouble();
          playInteract(dataLength, arrB);

          /*
           * PLAY 2
           */
          contin = false;
        }
        Serial.println("END");
}
void Player::start() {
  const Beat startBeats[] = {
    Beat(0, 1, 0), Beat(0, 1, 0), Beat(0, 1, 0), Beat(0, 1, 0),

    Beat(16, 0, 0)
  }; for (int n = 0; n < sizeof(startBeats) / sizeof(startBeats[0]) - 1; n++) playBeat(startBeats[n], startBeats[n + 1], melodyBPM);
}
void Player::ecuador() { // --------------------------------------------------------------------------------------------------- // Ecuador 4x8 beats
  const Beat ecuadorBeats[] = {
    Beat(16, 0.75, 1, "B3"), Beat(128, 0.75, -1, "F#3"), Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(2, 0.5, 1, "E4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, 0, "A3"),
    Beat(16, 0.75, 1, "B3"), Beat(128, 0.75, -1, "F#3"), Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(2, 0.5, 1, "E4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, 0, "A3"),
    Beat(4, 0.75, 0, "D4"),  Beat(32, 0.75, 1, "A3"),    Beat(1, 0.5, 1, "F#4"), Beat(4, 0.5, -1, "E4"),  Beat(1, 0.5, -1, "F#4"), Beat(2, 0.5, 0, "E4"),   Beat(32, 0.5, 0, "A3"),
    Beat(4, 0.75, 0, "D4"),  Beat(16, 0.75, 0, "B3"),    Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(4, 0.5, 1, "D4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, 0, "A3"),
    Beat(16, 0.75, 1, "B3"), Beat(128, 0.75, -1, "F#3"), Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(2, 0.5, 1, "E4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, 0, "A3"),
    Beat(16, 0.75, 1, "B3"), Beat(128, 0.75, -1, "F#3"), Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(2, 0.5, 1, "E4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, 0, "A3"),
    Beat(4, 0.75, 0, "D4"),  Beat(32, 0.75, 1, "A3"),    Beat(1, 0.5, 1, "F#4"), Beat(4, 0.5, -1, "E4"),  Beat(1, 0.5, -1, "F#4"), Beat(2, 0.5, 0, "E4"),   Beat(32, 0.5, 0, "A3"),
    Beat(4, 0.75, 0, "D4"),  Beat(16, 0.75, 0, "B3"),    Beat(4, 0.5, 1, "D4"),  Beat(8, 0.5, -1, "C#4"), Beat(4, 0.5, 1, "D4"),   Beat(8, 0.5, -1, "C#4"), Beat(32, 0.5, -1, "A3"),
    Beat(16, 0, 0)
  }; for (int n = 0; n < sizeof(ecuadorBeats) / sizeof(ecuadorBeats[0]) - 1; n++) playBeat(ecuadorBeats[n], ecuadorBeats[n + 1], melodyBPM);
}
void Player::pijanoo() { // --------------------------------------------------------------------------------------------------- // Pijanoo 4x8 beats
  const Beat pijanooBeats[] = {
    Beat(16, 0.5, 0, "A#3"), Beat(16, 0.5, 1, "A#3"), Beat(32, 0.5, 0, "A3"), Beat(32, 0.5, 0, "A3"),  Beat(64, 0.75, 0, "G3"), Beat(64, 0.75, 0, "G3"), Beat(64, 0.5, -1, "G3"),
    Beat(16, 0.5, 0, "A#3"), Beat(16, 0.5, 1, "A#3"), Beat(32, 1, -2, "A3"),  Beat(32, 0.75, 0, "G3"), Beat(32, 0.75, 0, "G3"), Beat(32, 0.5, -1, "G3"),
    Beat(8, 0.5, 0, "A#3"),  Beat(8, 0.5, 1, "A#3"),  Beat(16, 0.5, 0, "A3"), Beat(16, 0.5, 0, "A3"),  Beat(32, 0.75, 0, "G3"), Beat(32, 0.75, 0, "G3"), Beat(32, 0.5, -1, "G3"),
    Beat(8, 0.5, 0, "A#3"),  Beat(8, 0.5, 1, "A#3"),  Beat(16, 1, -2, "A3"),  Beat(16, 0.75, 0, "G3"), Beat(16, 0.75, 0, "G3"), Beat(16, 0.5, -1, "G3"),
    Beat(4, 0.5, 0, "A#3"),  Beat(4, 0.5, 1, "A#3"),  Beat(8, 0.5, 0, "A3"),  Beat(8, 0.5, 0, "A3"),   Beat(16, 0.75, 0, "G3"), Beat(16, 0.75, 0, "G3"), Beat(16, 0.5, -1, "G3"),
    Beat(4, 0.5, 0, "A#3"),  Beat(4, 0.5, 1, "A#3"),  Beat(8, 1, -2, "A3"),   Beat(8, 0.75, 0, "G3"),  Beat(8, 0.75, 0, "G3"),  Beat(8, 0.5, -1, "G3"),
    Beat(2, 0.5, 0, "A#3"),  Beat(2, 0.5, 1, "A#3"),  Beat(4, 0.5, 0, "A3"),  Beat(4, 0.5, 0, "A3"),   Beat(8, 0.75, 0, "G3"),  Beat(8, 0.75, 0, "G3"),  Beat(8, 0.5, -1, "G3"),
    Beat(2, 0.5, 0, "A#3"),  Beat(2, 0.5, 1, "A#3"),  Beat(4, 1, -2, "A3"),   Beat(4, 0.75, 0, "G3"),  Beat(4, 0.75, 0, "G3"),  Beat(4, 0.5, -1, "G3"),
    Beat(0, 0, 0)
  }; for (int n = 0; n < sizeof(pijanooBeats) / sizeof(pijanooBeats[0]) - 1; n++) playBeat(pijanooBeats[n], pijanooBeats[n + 1], melodyBPM);
}
void Player::zombieNation() { // ---------------------------------------------------------------------------------------------- // Zombie Nation 4x8 beats
  const Beat zombieNationBeats[] = {                       
    Beat(0, 0.5, 0),         Beat(128, 0.5, 0, "A#3"), Beat(32, 0.5, 0, "C#4"), Beat(16, 0.5, 1, "D#4"), Beat(8, 0.5, 0, "F4"),  Beat(0, 1.5, -1),
    Beat(0, 0.5, 0),         Beat(128, 0.5, 0, "A#3"), Beat(32, 0.5, 0, "C#4"), Beat(16, 0.5, 1, "D#4"), Beat(8, 0.5, -1, "F4"), Beat(4, 0.5, 1, "F#4"),   Beat(8, 0.5, 1, "F4"), Beat(64, 0.5, 0, "C#4"),
    Beat(32, 0.5, 0, "D#4"), Beat(0, 1.5, 0),          Beat(64, 0.5, 0, "C#4"), Beat(0, 0.5, -1),        Beat(8, 0.5, -1, "F4"), Beat(128, 0.5, 0, "A#3"),
    Beat(0, 4, 0),
    Beat(0, 0.5, 0),         Beat(128, 0.5, 0, "A#3"), Beat(32, 0.5, 0, "C#4"), Beat(16, 0.5, 1, "D#4"), Beat(8, 0.5, -1, "F4"), Beat(0, 1.5, 0),
    Beat(0, 0.5, 0),         Beat(128, 0.5, 0, "A#3"), Beat(32, 0.5, 0, "C#4"), Beat(16, 0.5, 1, "D#4"), Beat(8, 0.5, -1, "F4"), Beat(4, 0.5, 1, "F#4"),   Beat(8, 0.5, 1, "F4"), Beat(64, 0.5, 0, "C#4"),
    Beat(32, 0.5, 0, "D#4"), Beat(0, 1.5, 0),          Beat(64, 0.5, 0, "C#4"), Beat(0, 0.5, -1),        Beat(8, 0.5, -1, "F4"), Beat(128, 0.5, 0, "A#3"),
    Beat(0, 4, -2),
    Beat(128, 0, 0)
  }; for (int n = 0; n < sizeof(zombieNationBeats) / sizeof(zombieNationBeats[0]) - 1; n++) playBeat(zombieNationBeats[n], zombieNationBeats[n + 1], melodyBPM);
}
void Player::stereoLove() { // ------------------------------------------------------------------------------------------------ // Stereo Love 4x8 beats
  const Beat stereoLoveBeats[] = {                       
    Beat(128, 0.75, 1, "G#3"), Beat(8, 0.75, 0, "E4"), Beat(8, 0.5, 1, "E4"),   Beat(16, 0.5, -1, "D#4"), Beat(8, 0.5, -1, "E4"), Beat(2, 0.5, 1, "F#4"),   Beat(8, 0.5, 1, "E4"),
    Beat(16, 0.5, -1, "D#4"),  Beat(8, 0.5, -1, "E4"), Beat(16, 0.5, 0, "C#4"), Beat(8, 0.5, -1, "D#4"),  Beat(32, 0.5, 1, "B3"), Beat(16, 0.5, -1, "C#4"), Beat(64, 0.5, 0, "A3"), Beat(32, 0.5, 1, "B3"),
    Beat(128, 1, 0, "G#3"),    Beat(0, 3, 0),
    Beat(0, 4, 0),
    Beat(128, 0.75, 1, "G#3"), Beat(8, 0.75, 0, "E4"),  Beat(8, 0.5, 1, "E4"),   Beat(16, 0.5, -1, "D#4"), Beat(8, 0.5, -1, "E4"), Beat(2, 0.5, 1, "F#4"),   Beat(8, 0.5, 1, "E4"),
    Beat(16, 0.5, -1, "D#4"),  Beat(8, 0.5, -1, "E4"),  Beat(16, 0.5, 0, "C#4"), Beat(8, 0.5, -1, "D#4"),  Beat(32, 0.5, 1, "B3"), Beat(16, 0.5, -1, "C#4"), Beat(64, 0.5, 0, "A3"), Beat(32, 0.5, 0, "B3"),
    Beat(4, 0.75, 1, "E4"),    Beat(2, 0.75, 0, "F#4"), Beat(1, 0.5, 0, "G#4"),  Beat(0, 2, 2),
    Beat(16, 0.75, -1, "D#4"), Beat(8, 0.75, 1, "E4"),  Beat(4, 0.5, 0, "F#4"),  Beat(0, 2, 2),
    Beat(16, 0, 0)
  }; for (int n = 0; n < sizeof(stereoLoveBeats) / sizeof(stereoLoveBeats[0]) - 1; n++) playBeat(stereoLoveBeats[n], stereoLoveBeats[n + 1], melodyBPM);
}
void Player::lamourToujours() { // -------------------------------------------------------------------------------------------- // Lamour Toujours 4x8 beats
  const Beat lamourToujoursBeats[] = {                       
    Beat(8, 2, 2, "F#3"),  Beat(16, 1, 0, "F#3"), Beat(16, 0.5, 1, "F#3"), Beat(1, 0.5, 1, "D4"),
    Beat(2, 2, 0, "C#4"),  Beat(2, 1, 0, "C#4"),  Beat(2, 0.5, -1, "C#4"), Beat(1, 0.5, 0, "D4"),
    Beat(4, 2, 0, "B3"),   Beat(4, 1, 0, "B3"),   Beat(4, 0.5, 0, "B3"),   Beat(8, 0.5, 0, "A3"),
    Beat(4, 1, 0, "B3"),   Beat(4, 1, 0, "B3"),   Beat(4, 0.5, 0, "B3"),   Beat(8, 0.5, 0, "A3"), Beat(4, 0.5, 0, "B3"), Beat(8, 0.5, -1, "A3"),
    Beat(16, 2, 0, "F#3"), Beat(16, 1, 0, "F#3"), Beat(16, 0.5, 1, "F#3"), Beat(1, 0.5, 1, "D4"),
    Beat(2, 2, 0, "C#4"),  Beat(2, 1, 0, "C#4"),  Beat(2, 0.5, -1, "C#4"), Beat(1, 0.5, 0, "D4"),
    Beat(4, 2, 0, "B3"),   Beat(4, 1, 0, "B3"),   Beat(4, 0.5, 0, "B3"),   Beat(8, 0.5, 0, "A3"),
    Beat(4, 1, 0, "B3"),   Beat(4, 1, 0, "B3"),   Beat(4, 0.5, 0, "B3"),   Beat(8, 0.5, 0, "A3"), Beat(4, 0.5, 0, "B3"), Beat(8, 0.5, 0, "A3"),
    Beat(4, 0, 0)
  }; for (int n = 0; n < sizeof(lamourToujoursBeats) / sizeof(lamourToujoursBeats[0]) - 1; n++) playBeat(lamourToujoursBeats[n], lamourToujoursBeats[n + 1], melodyBPM);
}
void Player::betterOffAlone() { // -------------------------------------------------------------------------------------------- // Better Off Alone 4x8 beats
  const Beat betterOffAloneBeats[] = {                       
    Beat(4, 0.5, 1, "B3"),  Beat(0, 0.5, 1),           Beat(8, 0.5, -1, "B3"),  Beat(16, 0.5, 1, "G#3"), Beat(0, 2, 2),
    Beat(0, 1.5, 1),        Beat(128, 0.5, 0, "F#3"),  Beat(1, 0.75, 0, "F#4"), Beat(1, 0.75, 0, "F#4"), Beat(4, 0.5, -1, "D#4"),
    Beat(16, 0.5, 0, "B3"), Beat(0, 0.5, 0),           Beat(16, 0.5, 1, "B3"),  Beat(64, 0.5, 0, "G#3"), Beat(0, 2, 0),
    Beat(0, 1.5, 0),        Beat(128, 0.5, -1, "F#3"), Beat(2, 0.75, 0, "E4"),  Beat(2, 0.75, 1, "E4"),  Beat(4, 0.5, -1, "D#4"),
    Beat(16, 0.5, 0, "B3"), Beat(0, 0.5, 0),           Beat(16, 0.5, 1, "B3"),  Beat(64, 0.5, 0, "G#3"), Beat(0, 2, 0),
    Beat(0, 1.5, 0),        Beat(128, 0.5, 0, "F#3"),  Beat(1, 0.75, 0, "F#4"), Beat(1, 0.75, 0, "F#4"), Beat(4, 0.5, -1, "D#4"),
    Beat(16, 0.5, 0, "B3"), Beat(0, 0.5, 0),           Beat(16, 0.5, 1, "B3"),  Beat(64, 0.5, 0, "G#3"), Beat(0, 2, 0),
    Beat(0, 1.5, 0),        Beat(128, 0.5, -1, "F#3"), Beat(2, 0.75, 0, "E4"),  Beat(2, 0.75, 1, "E4"),  Beat(4, 0.5, -1, "D#4"),
    Beat(16, 0, 0)
  }; for (int n = 0; n < sizeof(betterOffAloneBeats) / sizeof(betterOffAloneBeats[0]) - 1; n++) playBeat(betterOffAloneBeats[n], betterOffAloneBeats[n + 1], melodyBPM);
}
void Player::wakeMeUp() { // -------------------------------------------------------------------------------------------------- // WON'T PLAY
  const Beat wakeMeUpBeats[] = {
    Beat(16, 1, 0, "B3"),    Beat(16, 0.75, 0, "B3"), Beat(16, 0.25, 0, "A3"),
    Beat(16, 0.25, 0, "B3"), Beat(4, 0.25, 0, "D4"),  Beat(16, 0.75, 0, "B3"), Beat(32, 0.25, 0, "A3"), Beat(16, 0.25, 0, "B3"), Beat(32, 0.25, 0, "A3"),
    Beat(4, 1, 0, "D4"),     Beat(4, 0.75, 0, "D4"),  Beat(4, 0.25, 0, "D4"),
    Beat(2, 0.25, 0, "E4"),  Beat(4, 0.25, 0, "D4"),  Beat(2, 0.5, 1, "E4"),   Beat(1, 0.5, -1, "F#4"), Beat(4, 0.5, 0, "D4"),
    Beat(16, 1, 0, "B3"),    Beat(16, 0.75, 0, "B3"), Beat(16, 0.25, 0, "A3"),
    Beat(16, 0.25, 0, "B3"), Beat(4, 0.25, 0, "D4"),  Beat(16, 0.75, 0, "B3"), Beat(32, 0.25, 0, "A3"), Beat(16, 0.25, 0, "B3"), Beat(32, 0.25, 0, "A3"),
    Beat(4, 1, 0, "D4"),     Beat(4, 0.75, 0, "D4"),  Beat(4, 0.25, 0, "D4"),
    Beat(2, 0.25, 0, "E4"),  Beat(4, 0.25, 0, "D4"),  Beat(2, 0.5, 1, "E4"),   Beat(1, 0.5, -1, "F#4"), Beat(4, 0.5, 0, "D4"),
    Beat(16, 1, 0, "B3"),    Beat(16, 0.75, 0, "B3"), Beat(16, 0.25, 0, "A3"),
    Beat(16, 0.25, 0, "B3"), Beat(4, 0.25, 0, "D4"),  Beat(16, 0.75, 0, "B3"), Beat(32, 0.25, 0, "A3"), Beat(16, 0.25, 0, "B3"), Beat(32, 0.25, 0, "A3"),
    Beat(4, 1, 0, "D4"),     Beat(4, 0.75, 0, "D4"),  Beat(4, 0.25, 0, "D4"),
    Beat(2, 0.25, 0, "E4"),  Beat(4, 0.25, 0, "D4"),  Beat(2, 0.5, 1, "E4"),   Beat(1, 0.5, -1, "F#4"), Beat(4, 0.5, 0, "D4"),
    Beat(16, 1, 0, "B3"),    Beat(16, 0.75, 0, "B3"), Beat(16, 0.25, 0, "A3"),
    Beat(16, 0.25, 0, "B3"), Beat(4, 0.25, 0, "D4"),  Beat(16, 0.75, 0, "B3"), Beat(32, 0.25, 0, "A3"), Beat(16, 0.25, 0, "B3"), Beat(32, 0.25, 0, "A3"),
    Beat(4, 1, 0, "D4"),     Beat(4, 0.75, 0, "D4"),  Beat(4, 0.25, 0, "D4"),
    Beat(2, 0.25, 0, "E4"),  Beat(4, 0.25, 0, "D4"),  Beat(2, 0.5, 1, "E4"),   Beat(1, 0.5, -1, "F#4"), Beat(4, 0.5, -1, "D4"),
    Beat(16, 0, 0)
  }; for (int n = 0; n < sizeof(wakeMeUpBeats) / sizeof(wakeMeUpBeats[0]) - 1; n++) playBeat(wakeMeUpBeats[n], wakeMeUpBeats[n + 1], melodyBPM);
}
void Player::imBlue() { // ---------------------------------------------------------------------------------------------------- // I'm Blue 4x8 beats
  const Beat imBlueBeats[] = {                       
    Beat(16, 1, -1, "A#3"), Beat(2, 0.5, 0, "D3"),   Beat(32, 0.5, -1, "G3"), Beat(8, 0.5, -1, "A#3"), Beat(2, 0.5, 0, "C4"),   Beat(32, 0.5, 0, "F3"), Beat(8, 0.5, -1, "A3"),
    Beat(4, 1, 1, "A#3"),   Beat(32, 0.5, 1, "G3"),  Beat(8, 0.5, 1, "A#3"),  Beat(2, 0.5, -1, "D4"),  Beat(1, 0.5, -1, "D#4"), Beat(16, 0.5, 0, "G3"), Beat(1, 0.5, 0, "D4"),
    Beat(2, 0.5, -1, "C4"), Beat(4, 0.5, 1, "A#3"),  Beat(128, 0.5, 0, "D3"), Beat(16, 0.5, 1, "G3"),  Beat(8, 0.5, -1, "A#3"), Beat(2, 0.5, 0, "C4"),  Beat(32, 0.5, 0, "F3"),  Beat(8, 0.5, -1, "A3"),
    Beat(4, 1, 1, "A#3"),   Beat(32, 0.5, 1, "G3"),  Beat(8, 0.5, 1, "A#3"),  Beat(2, 0.5, -1, "D4"),  Beat(1, 0.5, -1, "D#4"), Beat(16, 0.5, 0, "G3"), Beat(1, 0.5, 0, "D4"),
    Beat(2, 0.5, -1, "C4"), Beat(4, 0.5, 1, "A#3"),  Beat(128, 0.5, 0, "D3"), Beat(16, 0.5, 1, "G3"),  Beat(8, 0.5, -1, "A#3"), Beat(2, 0.5, 0, "C4"),  Beat(32, 0.5, 0, "F3"),  Beat(8, 0.5, -1, "A3"),
    Beat(4, 1, 1, "A#3"),   Beat(32, 0.5, 1, "G3"),  Beat(8, 0.5, 1, "A#3"),  Beat(2, 0.5, -1, "D4"),  Beat(1, 0.5, -1, "D#4"), Beat(16, 0.5, 0, "G3"), Beat(1, 0.5, 0, "D4"),
    Beat(2, 0.5, -1, "C4"), Beat(4, 0.5, -1, "A#3"), Beat(64, 0.5, 0, "D3"),  Beat(8, 0.5, -1, "G3"),  Beat(2, 0.5, 1, "A#3"),  Beat(4, 0.5, 0, "A3"),  Beat(128, 0.5, 0, "C3"), Beat(16, 0.5, 0, "F3"),
    Beat(8, 1, 0, "G3"),    Beat(0, 3, 0),
    Beat(0, 0, 0)
  }; for (int n = 0; n < sizeof(imBlueBeats) / sizeof(imBlueBeats[0]) - 1; n++) playBeat(imBlueBeats[n], imBlueBeats[n + 1], melodyBPM);
}
