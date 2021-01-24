#define ul unsigned long
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
	int counter = 0;
	int len = sizeof(p)/sizeof(double);
	int pos = 24;
	while (counter < len/3) {
		int n1 = counter * 3;
		int n2 = (counter+1) * 3;
		int n3 = (counter+2) * 3;

		if (p[n2 +1] == 0) {	//Time to n2 == 0 => is chord
			int chord[8] = {n1, len+1, len+1, len+1, len+1, len+1, len+1, len+1};
			for (int i = 1; i<8; i++) {
				if (p[(counter+i) * 3 +1] == 0) { // ni is part of the chord
					chord[i] = (counter+i) * 3;
				} else {
					//Find highest note in chord
					int m = 0;
					int ma;
					for (int ii = 0; ii<8; ii++) {
						if (p[chord[ii]] >= m) {
							m = p[chord[ii]];
							ma = ii;
						}
					}
					//Find lowest note in chord
					int mi = m;
					for (int ii = 0; ii<8; ii++) if (p[chord[ii]] <= mi) mi = p[chord[ii]];
					pos = toNext(pos, mi, ma, ma);
					counter = play(pos, chord, true);
					break;
				}
			}
		} else {	//Time to n2 != 0 => not chord
			pos = toNext(pos, p[n1], p[n2], p[n3]);
			int pout[8] = {n1, n2, n3, len+1, len+1, len+1, len+1, len+1};
			counter = play(pos, pout, false);
		}
	}
	//  End song 1

	//  Play song 2

	//End song 2
	digitalWrite(enPin, HIGH);
}

ul move(int value)
{
	ul startTime = millis();
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


bool isBlack(int N) //Checks if given note is black
{
	int n = N%12;
	if (n == 1 || n == 3 || n == 6 || n == 8 || n == 10) return true;
	else return false;
}

int halfNotes(a, b) //Calculates distance between two notes in "half-notes".    //ARGS: a = first note; b = second note
{
	m = abs(b-a);
	int c1 = 4 - a%12;
	if (c1 < 0) c1 = 12 + c1;
	int c2 = 12 - a%12;
	
	if (m > c1) m += ceil(m/12);
	if (m > c2) m += ceil(m/12);
	
	if (b<a) m = -m;
	return m;
}

void toNext(int cp, int n1, int n2, int n3) //Finds next position of piano and moves there.   //ARGS: current position; next note; note after next note; note after note after next note
{
	Max = max(max(n1, n2), n3);
	Min = min(min(n1, n2), n3);
	int a;

	if (Max-Min <= 12) {
		a = (Max-Min)/2;
		if (isBlack(Min + a) != isBlack(n1)) {
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

	move(halfNotes(cp, a)-6);
}

int play(int pos, int n[8], bool chord)
{
	int c = n[0]/3;
	if (!chord) {
		nn[3] = {n[0], n[1], n[2]}; //Index of 1st 3 midi values
		for (int no : nn) {
			int note = p[no]; //midi value
			if (halfNotes(pos, note)/2 <= 8) {
				digitalWrite(solenoid[halfNotes(pos, note)/2], HIGH);
				delay(p[no+2]); // duration
				digitalWrite(solenoid[halfNotes(pos, note)/2], LOW);
				c++;
			}
		}
	} else {
		int counter = 0;
		for (int no : n) {
			if (no > sizeof(p)/sizeof(double)) break;
			else {
				c++;
				counter++;
			}
		}
		float durations[counter];
		float m = 0.0;
		for (int i = 0; i<counter; i++) {	//Hit solenoids
			durations[i] = p[n[i+2]];
			m = max(m, durations[i]);
			digitalWrite(solenoid[halfNotes(pos, p[n[i]])/2], HIGH);
		}

		float mi = m;
		int f;
		for (int i = 0; i<counter; i++) {	//Delays the minimum then releases solenoid with minimum duration
			mi = m;
			for (int ii = 0; ii<counter; ii++) {
				if (durations[ii] <= mi) {
					mi = durations[ii];
					f = ii;
				}
			}
			delay(mi);
			digitalWrite(solenoid[halfNotes(pos, p[n[f]])/2], LOW);
			durations[f] = m+1;
		}
	}

	return c;
}