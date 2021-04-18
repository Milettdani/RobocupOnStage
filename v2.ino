#define ui unsigned int
#include <math.h>
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;

int p[12][9] = {{77, 1, 1, 0, 0, 0, 0, 0, 0}, {-3, 1, 0, 0, 1, 0, 0, 0, 0}, {-6, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0}, {-2, 1, 0, 0, 0, 0, 0, 0, 0}};
int size = 12;
const double arrayTime = 0.500000;

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
	for (int i=1; i<9; i++) {
		digitalWrite(solenoid[i-1], p[0][i]);
	}
	delay(arrayTime*1000);

	int wt;
	for (int t=1; t<size; t++) {
		wt = move(p[t][0]);
		t += round(((float)wt/100)/arrayTime);
		for(int b=1; b<9; b++) {
			digitalWrite(solenoid[b-1], p[t][b]);
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
