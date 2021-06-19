#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

// Time between elements of final array (in seconds)
const double arrayTime = 0.25;
// Input array = {midi value, start time}


const double d[20] = {36, 0.00, 36, 1.00, 36, 2.00, 38, 3.00, 36, 4.00, 36, 5.00, 36, 5.50, 36, 6.00, 36, 7.00, 38, 7.00};

const int midi_length = 7;
const int midi[midi_length] = {38, 50, 51, 36, 42, 52, 53};
//snare, tom1, tom2, tom3, hh, ride, crash

void editFile(string str_replace)		//NEEDS EDITING
{
	ostringstream text;
	ifstream in_file("Drums/Melody.cpp");

	text << in_file.rdbuf();
	string str = text.str();
	size_t pos = str.find("STARTMARK");
	size_t pos2 = str.find("//ENDMARK");
	str.replace(pos+1, pos2 - (pos+1), str_replace);
	in_file.close();

	ofstream out_file("Drums/Melody.cpp");
	out_file << str;
}

void writeInteract(int arr[], int as)
{
	string drumsw = to_string(as) + "\n";
	string pianow = "";
	for (int i=0; i<as; i++) {
		drumsw += to_string(arr[i]);
		if (arr[i] == 136) {
			pianow += i*arrayTime;
			if (i != as-1) pianow += ", ";
		}
		if (i != as-1) drumsw += ", ";
	}
	drumsw += "\n" + to_string(arrayTime);
	
	//Drums
	fstream dout;
	dout.open("test.txt", ios::out | ios::trunc);
	dout << drumsw;
	dout.close();
	
	//Piano
	fstream pout;
	pout.open("test.txt", ios::out | ios::trunc);
	pout << pianow;
	pout.close();
}

int main()
{
	//Generate empty array
	int size = (d[sizeof(d)/sizeof(double)-1])/arrayTime +1; //length of final array: length of track / arrayTime
    
    	string f = "\nconst int d[" + to_string(size+1) + "] = {";
	string uf;
	int of[size];
	for (int t=0;t<size;t++) { // t+1th atTime in g
		uf = "10000000";
		// loop through d
		for (int i = 1; i<sizeof(d)/sizeof(double); i+=2) {
			if (t*arrayTime == d[i]) {
				for (int j = 0; j<midi_length; j++) {
					if (midi[j] == d[i-1]) {
						uf[j+1] = '1';
					}
				}
			}
			// Is true if at time t p[i-1] is held down at time t
		}
		of[t] = stoi(uf, 0, 2);
		uf = to_string(of[t]) + ", ";
		f += uf;
	}
	f += "128};\nconst int arrSize = " + to_string(size+1) + ";\nconst double arrayTime = " + to_string(arrayTime) + ";\n\n";
	editFile(f);
	writeInteract(of, size);
	//cout << f;
}
