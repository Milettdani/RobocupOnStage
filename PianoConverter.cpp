#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

// Time between elements of final array (in seconds)
// Input array = {midi value, start time, hold time}
//movement positions: {time to move at (seconds), midi note to move to}; play note then move
float* mp;

class atTime {
	public:
		int pos; // Position of the first solenoid at the time (in midi)
		int states[8]; // Solenoid state: on/off state of solenoids at the time
};

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
	if (om >= c1) m += ceil((float)om/(14+c1));
	if (om >= c2) m += ceil((float)om/(14+c2));
	
	if (b<a) m = -m + 1;
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

void editFile(string str_replace)
{
	ostringstream text;
	ifstream in_file("Piano/Piano.ino");

	text << in_file.rdbuf();
	string str = text.str();
	size_t pos = str.find(" 5;");
	size_t pos2 = str.find("int m");
	str.replace(pos+4, pos2 - (pos+4), str_replace);
	in_file.close();

	ofstream out_file("Piano/Piano.ino");
	out_file << str;
}

void movement(int startmove, int pSize, double p[])
{
	int pos = startmove;
	mp[0] = 0.0;
	mp[1] = (double)startmove;
	//cout << mp[0] << endl << mp[1] << endl;
	for (int i = 3; i<pSize; i+=3) {
		if (isBlack(p[i]) != isBlack(pos)) {
			mp[(i * 2) /3 +1] = pos+1;
			mp[(i * 2) /3] = p[i+1];
			pos += 1;
		}
		if (halfNotes(pos, p[i]) > 14) {
			mp[(i * 2) /3 +1] = halfNotes(pos, p[i]) - 14;
			mp[(i * 2) /3] = p[i+1];
			pos = mp[(i * 2) /3 +1];
		} else if (halfNotes(pos, p[i]) < 0) {
			mp[(i * 2) /3 +1] = halfNotes(pos, p[i]);
			mp[(i * 2) /3] = p[i+1];
			pos = mp[(i * 2) /3 +1];
		}
		//cout << mp[(i*2)/3] << endl << mp[(i*2)/3 +1] << endl;
	}
}

int main()
{
    //Find array
    fstream pread;
	pread.open("PianoRead.txt", ios::in);
	string tp;
	getline(pread, tp);
	double arrayTime = stod(tp);
	getline(pread, tp);
    int startmove = stoi(tp);
    getline(pread, tp);
	int pSize = stoi(tp);
	double p[pSize];
	int counter = 0;
	while (getline(pread, tp)) {
        if (counter < pSize) {
            p[counter] = stod(tp);
            counter++;
        }
    }
    
    mp = new float[(pSize*2)/3];
    movement(startmove, pSize, p);

	//Generate empty array
	int size = (p[pSize-1] + p[pSize-2])/arrayTime; //length of final array: length of track / arrayTime
	atTime g[size];
    
    string f = "\nconst int p[" + to_string(size+1) + "][2] = {";
	int ppos = startmove;
	int pppos = startmove;
	string uf;
	for (int t=0;t<size;t++) { // t+1th atTime in g
		uf = "{";
		pppos = ppos;
		for (int j = 0; j<pSize; j+=2) if (abs(mp[j] - t*arrayTime) < 0.005) {
			ppos = mp[j+1];
			break;
		}
		string spos = to_string(halfNotes(pppos, ppos));
		uf += spos + ", ";
		string uff = "100000000";
		// loop through p
		for (int i = 1; i<pSize; i+=3) {
			if (t*arrayTime >= p[i] && t*arrayTime < p[i+1] + p[i]) uff[(halfNotes(pppos, p[i-1])/2)+1] = '1';
			// Is true if at time t p[i-1] is held down at time t
		}
		uf += to_string(stoi(uff, 0, 2)) + "}, ";
		f += uf;
	}
	f += "{0, 256}};\nconst int arrSize = " + to_string(size+1) + ";\nconst double arrayTime = " + to_string(arrayTime) + ";\nconst int startmove = " + to_string(startmove) + ";\n\n";
	editFile(f);
	//cout << f;
}
