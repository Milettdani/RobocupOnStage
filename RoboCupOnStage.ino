const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;
const int BPM1 = 70, BPM2 = 110;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) { pinMode(solenoid[i], OUTPUT); }
  pinMode(stepPin, OUTPUT); pinMode(dirPin, OUTPUT); pinMode(enPin, OUTPUT);
}

void loop() {
  delay(5000);
  /*move(20); PlayMelodyOne(); move(-20);
  move(24); PlayMelodyTwo();*/

  //  Play song 1

  //  End song 1

  //  Play song 2

  //End song 2
  digitalWrite(enPin, HIGH);
}

float move(int value) {
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

void Wait(float bpm, float beat, float delayTime = 0) {
  float calculatedTime = 60000 / bpm * beat;
  if(calculatedTime > delayTime) delay(calculatedTime - delayTime);
}


bool isBlack(int N)
{
  int n = N%12;
  if (n == 1 || n == 3 || n == 6 || n == 8 || n == 10) return true;
  else return false;
}

void findNext(int n1, int n2, int n3)
{
  Max = max(max(n1, n2), n3);
  Min = min(min(n1, n2), n3);
  int a;

  if (Max-Min <= 12) {
    a = (Max-Min)/2;
    if (isBlack(a) != isBlack(n1)) {
      if (a-Min > Max-a) a -= 1;
      else a += 1;
    }
  } else if (abs(n1-n2) > 12) {
    if (n1>n2) a = n1-7;
    else a = n1;
  } else {
    if (n3 < n1) a = max(n1, n2)-7;
    else a = min(n1, n2);
  }
}
void moveTo(a, b) //a = current position; b = destination
{
  m = abs(b-a);
  int c1 = 4 - a%12;
  if (c1 < 0) c1 = 12 + c1;
  int c2 = 12 - a%12;
  if (c2 < 0) c2 = 12 + c2;
  
  if (m >= c1) m += ceil(m/12);
  if (m >= c2) m += ceil(m/12);
  
  if (b<a) m = -m;
  move(m-6);
}



/*
void PrepareMelodyOne() {
  
}
void PlayMelodyOne() {
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.85);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.85);                                  Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.85);                                  Serial.println("E5");
  digitalWrite(solenoid[6], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 1);                                     Serial.println("E5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1)); 
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 1);                                     Serial.println("B4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 2);                                     Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.85);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 2);                                     Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);
  
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.5);                                   Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.35);                                  Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(-1)); // END
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.5);                                   Serial.println("E4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[6], LOW);  Wait(BPM1, 0.15, move(2));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(1)); // END
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.5);                                   Serial.println("Db5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15, move(2));
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.5);                                   Serial.println("B5");
  digitalWrite(solenoid[7], LOW);

  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.35);                                  Serial.println("G5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.5);                                   Serial.println("E5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.35);                                  Serial.println("G5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.5);                                   Serial.println("E5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.35);                                  Serial.println("Db5");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[0], LOW);  Wait(BPM1, 0.15, move(-2));
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.5);                                   Serial.println("A4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.5);                                   Serial.println("B4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.35);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.85);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.85);                                  Serial.println("Db5");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.35);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G5");
  digitalWrite(solenoid[6], LOW);
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.1);                                   Serial.println("DB5");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.1);                                   Serial.println("G5");
  digitalWrite(solenoid[7], LOW);  Wait(BPM1, 0.15, move(1));
  
  digitalWrite(solenoid[6], HIGH); Wait(BPM1, 0.35);                                  Serial.println("F#5");
  digitalWrite(solenoid[6], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.5);                                   Serial.println("F#5");
  digitalWrite(solenoid[7], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[0], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.1);                                   Serial.println("A4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.35);                                  Serial.println("G4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.1);                                   Serial.println("E4");
  digitalWrite(solenoid[0], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.25);                                  Serial.println("E4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[0], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D4");
  digitalWrite(solenoid[0], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.1);                                   Serial.println("E4");
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.1);                                   Serial.println("F#4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("G4");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(2));
  
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.5);                                   Serial.println("G4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.1);                                   Serial.println("A4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15, move(2));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.35);                                  Serial.println("B4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.1);                                   Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("D5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.1);                                   Serial.println("Db5");
  digitalWrite(solenoid[4], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.25);                                  Serial.println("B4");
  digitalWrite(solenoid[2], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM1, 0.25);                                  Serial.println("A4");
  digitalWrite(solenoid[1], LOW);
  digitalWrite(solenoid[2], HIGH); Wait(BPM1, 0.1);                                   Serial.println("B4");
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.1);                                   Serial.println("Db4");
  digitalWrite(solenoid[3], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[4], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[4], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.1);                                   Serial.println("E5");
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[7], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[7], LOW);
}
void PlayMelodyTwo() {
  digitalWrite(solenoid[0], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[0], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[5], HIGH); Wait(BPM1, 0.5);                                  Serial.println("D5");
  digitalWrite(solenoid[5], LOW);
  digitalWrite(solenoid[5], HIGH); Wait(BPM2, 0.35);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[5], LOW);  Wait(BPM1, 0.15, move(1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 1);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);

  digitalWrite(solenoid[0], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[0], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[2], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[2], LOW);  Wait(BPM1, 0.15, move(-1));
  digitalWrite(solenoid[3], HIGH); Wait(BPM1, 0.25);                                  Serial.println("D5");
  digitalWrite(solenoid[3], LOW);
  digitalWrite(solenoid[1], HIGH); Wait(BPM2, 0.1);                                  Serial.println("F#5");          //
  digitalWrite(solenoid[1], LOW);  Wait(BPM1, 0.15, move(1));
}
*/