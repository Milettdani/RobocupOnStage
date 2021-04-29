#define ui unsigned int
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;

const int arrSize = 66;
const long p[66][2] = {{40, 10000000}, {0, 00000000}, {4, 10000000}, {0, 00000000}, {-4, 10000000}, {0, 10000000}, {0, 10100000}, {0, 10000000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 00000000}, {0, 00100000}, {0, 00000000}, {0, 10000000}, {0, 00000000}, {0, 00100000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000010}, {0, 00000000}, {0, 00000010}, {0, 00000000}, {0, 00000100}, {0, 00000000}, {0, 00001000}, {0, 00000000}, {0, 00010000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000100}, {0, 00000100}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00000000}, {0, 00010000}, {0, 00000000}, {0, 00100000}, {0, 00000000}, {0, 01000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}};
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
  if (n >= 8 - g.length()) return g[n - (8-g.length())] - '0';
  else return 0;
}

void play()
{
  move(p[0][0]);
  delay(5000);
  for (int i=0; i<8; i++) {
    digitalWrite(solenoid[i], dig(p[0][1], i));
    //Serial.println(dig(p[0][1], i));
  }
  delay(arrayTime*1000);
  int wt;
  //Serial.println("\n\n");
  for (int t=1; t<arrSize; t++) {
    wt = move(p[t][0]); //wasted time while moving in ms
    //Serial.println(round(((float)wt/1000)/arrayTime*1000));
    //t += round(((float)wt/1000)/arrayTime);
    for (int b=0; b<8; b++) {
      digitalWrite(solenoid[b], dig(p[t][1], b));
      //Serial.println(dig(p[t][1], b));
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
