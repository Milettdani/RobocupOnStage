#define ui unsigned int
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 }; //move after notes played: e.g.: {4, 384}: play(384), wait arrayTime, move 4
const int dirPin = 6, stepPin = 7, enPin = 5;

const short p[67][2] = {{4, 384}, {0, 256}, {-4, 384}, {0, 256}, {0, 384}, {0, 384}, {0, 416}, {0, 384}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 256}, {0, 256}, {0, 257}, {0, 256}, {0, 258}, {0, 256}, {0, 260}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 256}, {0, 256}, {0, 260}, {0, 260}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 288}, {0, 256}, {0, 320}, {0, 256}, {0, 384}, {0, 384}, {0, 256}, {0, 256}, {0, 384}, {0, 384}, {0, 256}};
const int arrSize = 67;
const double arrayTime = 0.250000;
const int startmove = 28;

int mmove(int value)
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

int dig(long val, int n)
{
  String g = String(val);
  return String(g[n+1]).toInt();
  /*
  if (n >= 8 - g.length()) return String(g[n - (8-g.length())]).toInt();
  else return 0;*/
}

int power(int a, int b)
{
  int f = 1;
  for (int i = 0; i<b; i++) {
    f *= a;
  }
  return f;
}

long toDec(short dec)
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

int pos = startmove;
void play()
{
  int wt;
  long dec;
  //unsigned long startTime = millis(), noteTime = 0;
  unsigned long startTime = millis();
  int testTime = millis();
  bool a = true;
  for (int t=0; t<arrSize; t++) {
    //noteTime = !noteTime ? startTime : noteTime; noteTime += (arrayTime * 1000);
    dec = toDec(p[t][1]);
    for (int b=0; b<8; b++) {
      //Serial.println(dec);
      //Serial.println(b);
      digitalWrite(solenoid[b], dig(dec, b));
      Serial.print(dig(dec, b));
    }
    //Serial.println("Moving...");
    //Serial.println(p[t][0]);
    //
    delay(arrayTime*1000 - (millis() - startTime) + wt - a);
    startTime = millis();// - ((millis() - startTime) - 250);
    a = !a;
    //Serial.println(startTime);
    //Serial.print('\t');
    //Serial.print(millis()-startTime);
    pos += p[t][0];
    wt = mmove(p[t][0]);
    //Serial.print('\t');
    //Serial.print(arrayTime*1000-wt);
    //Serial.println();
    if (round(((float)wt/1000)/arrayTime) > 0) t += round(((float)wt/1000)/arrayTime) -1;
    //while(millis() - startTime < noteTime);
  }
  Serial.println(millis() - testTime);
}

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("Starting\n");

  for (int i = 0; i < 8; i++) {pinMode(solenoid[i], OUTPUT); digitalWrite(solenoid[i], LOW);}
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW); 

  //move to starting pos then wait
  mmove(startmove);
  //delay(5000);
  Serial.println("END");

  bool contin = true;
  while(contin)
    while(Serial.available() > 0)
      if(Serial.read() == 'A')
        contin = false;
        
  play();
  mmove(28 - pos); // Move to interraction (C)

  contin = true;
  while(contin)
    while(Serial.available() > 0)
      if(Serial.read() == 'S') {
        
      }

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

void loop() {
}
