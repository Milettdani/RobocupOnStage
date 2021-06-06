#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

// Time between elements of final array (in seconds)
const double arrayTime = 0.5;
// Input array = {midi value, start time}
const double d[20] = {36, 0.00, 36, 1.00, 38, 2.00, 36, 3.00, 36, 4.00, 36, 5.00, 36, 5.50, 38, 6.00, 36, 6.00, 36, 7.00};

const int midi_length = 7;
const int midi[midi_length] = {38, 50, 51, 36, 42, 52, 53};
//snare, tom1, tom2, tom3, hh, ride, crash

void editFile(string str_replace)		//NEEDS EDITING
{
	ostringstream text;
	ifstream in_file("v2_drums/v2_drums.ino");

	text << in_file.rdbuf();
	string str = text.str();
	size_t pos = str.find("1};");
	size_t pos2 = str.find("int dig(long");
	str.replace(pos+4, pos2 - (pos+4), str_replace);
	in_file.close();

	ofstream out_file("v2_drums/v2_drums.ino");
	out_file << str;
}

int main()
{
	//Generate empty array
	int size = (d[sizeof(d)/sizeof(double)-1])/arrayTime; //length of final array: length of track / arrayTime
    
    string f = "\nconst int d[" + to_string(size+1) + "] = {";
	string uf;
	for (int t=0;t<size;t++) { // t+1th atTime in g
		uf = "10000000";
		// loop through d
		for (int i = 1; i<sizeof(d)/sizeof(double); i+=2) {
			if (t*arrayTime == d[i]) {
				for (int j = 0; j<midi_length; j++) {
					if (midi[j] == d[i-1]) {
						uf[j+1] = '1';
						break;
					}
				}
			}
			// Is true if at time t p[i-1] is held down at time t
		}
		uf = to_string(stoi(uf, 0, 2)) + ", ";
		f += uf;
	}
	f += "128};\nconst int arrSize = " + to_string(size+1) + ";\nconst double arrayTime = " + to_string(arrayTime) + ";\n\n";
	editFile(f);
	//cout << f;
}