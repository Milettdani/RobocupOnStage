void(* resetFunc) (void) = 0;
const byte solenoids[8] = {A0, A2, A3, A4, A5, 11, 12};
const static byte dirPin = 6, stepPin = 7, enPin = 5;

//S
const short p[67][2] = {{4, 384}, {0, 256}, {-4, 384}, {0, 256}, {0, 384}, {0, 384}, {0, 416}, {0, 384}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 256}, {0, 256}, {0, 257}, {0, 256}, {0, 258}, {0, 256}, {0, 260}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 256}, {0, 256}, {0, 260}, {0, 260}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 288}, {0, 256}, {0, 320}, {0, 256}, {0, 384}, {0, 384}, {0, 256}, {0, 256}, {0, 384}, {0, 384}, {0, 256}};
const short arrSize = 67;
const float arrayTime = 0.250000;
const short startmove = 28;

//ENDMARK

int mmove(int value)
{
  Serial.println();
  Serial.print("MOVING:  ");
  Serial.println(value);
  int startTime = millis();
  if (value == 0) return 0;
  else if (value < 0) digitalWrite(dirPin, HIGH);                                                                               // Change MoveDir
  else if (value > 0) digitalWrite(dirPin, LOW);
  for (byte solenoid : solenoids) digitalWrite(solenoid, LOW);
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

long toDec(int dec)
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

void play()
{
  /*
  bool playing = false;
  while (!playing) {
    while (Serial.available() > 0) {
      byte data = Serial.read();
      if(data == 'A') playing = true;
    }
  }*/
  unsigned long startTime = millis();
  for (int counter = 0; counter < arrSize; counter++) {
    while(Serial.available() > 0) {
      byte data = Serial.read();
      if(data == 'B') {
        return;
      }
    }

    int wt;

    if (counter >= arrSize) return;
    Serial.println();
    Serial.print(counter);
    Serial.print("    ");
    bool keyArray[8];
    for (int i = 0; i<8; i++) {
      keyArray[i] = dig(toDec(p[counter]), i);
      digitalWrite(solenoids[i], keyArray[i]);
      Serial.print(keyArray[i]);
    }

    while (millis() - startTime < arrayTime*500*(counter+1));
    wt = mmove(p[counter][0]);
    if (round(((float)wt/1000)/arrayTime) > 0) counter += round(((float)wt/1000)/arrayTime) -1;
    while (millis() - startTime < arrayTime*1000*(counter+1));
  }
  resetFunc();
}

void setup()
{
  Serial.begin(115200);
  for (byte solenoid : solenoids) {
    pinMode(solenoid, OUTPUT);
    digitalWrite(solenoid, LOW);
  }

  Serial.print('P');
  bool contin = false;
  while (!contin) {
    while(Serial.available() > 0) {
      byte data = Serial.read();
      if (data == 'B') resetFunc();
      else if (data == 'A') contin = true;
    }
  }

  play();
  resetFunc();
}

void loop(){}