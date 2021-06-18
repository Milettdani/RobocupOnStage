#define ul unsigned long
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 };
const int dirPin = 6, stepPin = 7, enPin = 5;

ul del;

//ADD: check if last 3 or less notes - if so load last notes into toNext
void setup() {
	Serial.begin(9600);

	for (int i = 0; i < 8; i++) { pinMode(solenoid[i], OUTPUT); }
	pinMode(stepPin, OUTPUT); pinMode(dirPin, OUTPUT); pinMode(enPin, OUTPUT);

	delay(5000);
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

void loop() {
	/*move(20); PlayMelodyOne(); move(-20);
	move(24); PlayMelodyTwo();*/
}

void move(int value)
{
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
	del = millis();
}


bool isBlack(int N) //Checks if given note is black
{
	int n = N%12;
	if (n == 1 || n == 3 || n == 6 || n == 8 || n == 10) return true;
	else return false;
}

int halfNotes(int a, int b) //Calculates distance between two notes in "half-notes".    //ARGS: a = first note; b = second note
{
	int m = abs(b-a);
	int c1 = 4 - a%12;
	if (c1 < 0) c1 = 12 + c1;
	int c2 = 12 - a%12;
	
	int om = m;
	if (om > c1) m += ceil((float)om/(14+c1));
	if (om > c2) m += ceil((float)om/(14+c2));
	
	if (b<a) m = -m;
	return m;
}

int toMidi(int m, int h)	//Finds midi-value of note that is [h] half notes away from midi note [m]
{
    int cc1 = 4;
    int cc2 = 12;
    if (h<0) {cc1 = 0; cc2 = 8;}
    int c1 = cc1 - m%12;
    if (c1<0) c1 = 12 + c1;
    int c2 = cc2 - m%12;
    if (c2<0) c2 = 12 + c2;
    
    int hh = abs(h);
    int oh = hh;
    if (oh>c1) hh -= ceil((float)oh/(14+c1));
    if (oh>c2) hh -= ceil((float)oh/(14+c2));
    
    if (h<0) hh = -hh;
    return m + hh;
}

// ADD: don't move if in position for next notes
int toNext(int cp, int n1, int n2, int n3)	//Finds next position of piano and moves there.   //ARGS: current position; next note; note after next note; note after note after next note
{
	Max = max(max(n1, n2), n3);
	Min = min(min(n1, n2), n3);
	int a;

	if (Max - Min <= 12) {
		a = halfNotes(Min, Max)/2 -6;
		if (isBlack(toMidi(Min, a)) != isBlack(n1)) {
			if (halfNotes(Min, toMidi(Min, a+6)) >= halfNotes(toMidi(Min, a+6), Max)) a -= 1;
			else a += 1;
		}
	} else if (abs(n1-n2) <= 12) {
		if (n3 >= max(n1, n2)) a = 0;
		else a = halfNotes(n3, max(n1, n2)) -14;
	} else {
		if (n2>n1) a = halfNotes(min(n1, n3), n1);
		else a = halfNotes(min(n2, n3), n1) -14;
	}
	move(halfNotes(cp, Min)+a);
	return toMidi(Min, a);	//New position
}

int play(int pos, int n[8], bool chord)
{
	ul ct = del;
	int c = n[0]/3;
	if (!chord) {
		int nn[3] = {n[0], n[1], n[2]}; //Index of 1st 3 midi values
		for (int no : nn) {
			int note = p[no]; //midi value
			if (halfNotes(pos, note)/2 <= 8) {
				delay(p[no+1] - (double)(millis()-ct));
				ct = millis();
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
		delay(p[n[0]+1] - (double)(millis()-ct));
		ct = millis();
		for (int i = 0; i<counter; i++) {	//Hit solenoids
			durations[i] = p[n[i]+2];
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
