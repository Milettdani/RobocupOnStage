#define ui unsigned int
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;

const long p[66][2] = {{40, 384}, {0, 256}, {4, 384}, {0, 256}, {-4, 384}, {0, 384}, {0, 416}, {0, 384}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 256}, {0, 256}, {0, 256}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 384}, {0, 256}, {0, 288}, {0, 256}, {0, 264}, {0, 264}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 256}, {0, 256}, {0, 258}, {0, 256}, {0, 258}, {0, 256}, {0, 260}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 256}, {0, 256}, {0, 260}, {0, 260}, {0, 256}, {0, 256}, {0, 264}, {0, 256}, {0, 272}, {0, 256}, {0, 288}, {0, 256}, {0, 320}, {0, 256}, {0, 384}, {0, 384}, {0, 256}, {0, 256}, {0, 384}, {0, 384}};
const int arrSize = 66;
const double arrayTime = 0.250000;

int move(int value)
{
	int startTime = millis();
	if(value == 0) {digitalWrite(enPin, HIGH); return 0;}
	else if(value < 0) digitalWrite(dirPin, HIGH);
	else if(value > 0) digitalWrite(dirPin, LOW);
	for (int i = 0; i < 147 * abs(value); i++) {
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(320);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(320);
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
  move(p[0][0]);
  delay(5000);
  long dec = toDec(p[0][1]);
  for (int i=0; i<8; i++) {
    //Serial.println("dec:");
    //Serial.println(dec);
    //Serial.println(i);
    digitalWrite(solenoid[i], dig(dec, i));
    Serial.println(dig(dec, i));
    //Serial.println("\n");
  }
  delay(arrayTime*1000);
  int wt;
  Serial.println("\n\n");
  for (int t=1; t<arrSize; t++) {
    wt = move(p[t][0]); //wasted time while moving in ms
    Serial.println("Moving...");
    Serial.println(p[t][0]);
    Serial.println("\n");
    //Serial.println(round(((float)wt/1000)/arrayTime*1000));
    //t += round(((float)wt/1000)/arrayTime);
    dec = toDec(p[t][1]);
    for (int b=0; b<8; b++) {
      //Serial.println(dec);
      //Serial.println(b);
      digitalWrite(solenoid[b], dig(dec, b));
      Serial.println(dig(dec, b));
      //Serial.println("\n");
    }
    delay(arrayTime*1000);
    //Serial.println("\n");
  }
}

void setup()
{
	Serial.begin(9600);
  Serial.println("Starting\n");

	for (int i = 0; i < 8; i++) {pinMode(solenoid[i], OUTPUT); digitalWrite(solenoid[i], LOW);}
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enPin, OUTPUT);
	digitalWrite(enPin, LOW);	

	play();
	delay(5000);
	digitalWrite(enPin, HIGH);
}

void loop() {
}
