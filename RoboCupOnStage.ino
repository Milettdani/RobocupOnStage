const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;
const int firstMelodyBPM = 70, secondMelodyBPM = 110;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) { pinMode(solenoid[i], OUTPUT); }
  pinMode(stepPin, OUTPUT); pinMode(dirPin, OUTPUT); pinMode(enPin, OUTPUT);
}

void loop() {
  delay(5000);
  //Move(20); PlayMelodyOne(); Move(-20);*/
  Move(24); PlayMelodyTwo();
  digitalWrite(enPin, HIGH);
  while(true) { }
}

void Wait(float bpm, float beat, float delayTime = 0) {
  float calculatedTime = 60000 / bpm * beat;
  if(calculatedTime > delayTime) delay(calculatedTime - delayTime);
}
float Move(int value) {
  float startTime = millis();
  if(value == 0) digitalWrite(enPin, HIGH);
  else if(value < 0) digitalWrite(dirPin, HIGH);
  else if(value > 0) digitalWrite(dirPin, LOW);
  for(int i = 0; i < 147 * abs(value); i++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(320);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(320);
  }
  return millis() - startTime;
}
                                                                                                                                //
void PrepareMelodyOne() {
  
}
void PlayMelodyOne() {
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("E5");
  digitalWrite(solenoid[6], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 1);                                     Serial.println("E5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1)); 
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 1);                                     Serial.println("B4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 2);                                     Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 2);                                     Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);
  
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1)); // END
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("E4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[6], LOW);  Wait(firstMelodyBPM, 0.15, Move(2));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(1)); // END
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("Db5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15, Move(2));
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("B5");
  digitalWrite(solenoid[7], LOW);

  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("G5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("E5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("G5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("E5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[0], LOW);  Wait(firstMelodyBPM, 0.15, Move(-2));
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("B4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("DB5");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("G5");
  digitalWrite(solenoid[7], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  
  digitalWrite(solenoid[6], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[0], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("A4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("G4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("E4");
  digitalWrite(solenoid[0], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("E4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("E4");
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(2));
  
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15, Move(2));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("Db4");
  digitalWrite(solenoid[3], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[4], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[7], LOW);
}
void PlayMelodyTwo() {
  digitalWrite(solenoid[0], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[0], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[5], HIGH); Wait(firstMelodyBPM, 0.5);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(secondMelodyBPM, 0.35);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[5], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 1);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);

  digitalWrite(solenoid[0], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[0], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[2], LOW);  Wait(firstMelodyBPM, 0.15, Move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(firstMelodyBPM, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(secondMelodyBPM, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[1], LOW);  Wait(firstMelodyBPM, 0.15, Move(1));
}
