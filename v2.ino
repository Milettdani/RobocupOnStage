#define ui unsigned int
#include <math.h>
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;

const long p[329][2] = {{48, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {4, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {-4, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10100000}, {0, 10100000}, {0, 10100000}, {0, 10100000}, {0, 10100000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000010}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000100}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00001000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00010000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00100000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 01000000}, {0, 01000000}, {0, 01000000}, {0, 01000000}, {0, 01000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 00000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}, {0, 10000000}};
const int arrSize = 329;
const double arrayTime = 0.050000;

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

void play()
{
	move(p[0][0]);
	delay(5000);
	for (int i=0; i<8; i++) {
		digitalWrite(solenoid[i], p[0][1]/pow(10,i) % 10);
	}
	delay(arrayTime*1000);

	int wt;
	for (int t=1; t<arrSize; t++) {
		wt = move(p[t][0]);
		t += round(((float)wt/100)/arrayTime);
		for(int b=0; b<8; b++) {
			digitalWrite(solenoid[b], p[t][1]/pow(10,b) % 10);
		}
		delay(arrayTime*1000);
	}
}

void setup()
{
	Serial.begin(9600);

	for (int i = 0; i < 8; i++) pinMode(solenoid[i], OUTPUT)
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enPin, OUTPUT);

	play();
	delay(5000);
	digitalWrite(enPin, LOW);
}

void loop() {
}
