#include <iostream>
#include <string>
#include <math.h>
using namespace std;

// Time between elements of final array (in seconds)
double arrayTime = 0.5;
// Input array = {midi value, start time, hold time}
double p[36] = {77, 0.00, 0.500, 74, 0.50, 0.500, 69, 1.00, 0.500, 76, 1.50, 0.500, 72, 2.00, 0.500, 69, 2.50, 0.500, 76, 3.00, 0.500, 72, 3.50, 0.500, 69, 4.00, 0.500, 74, 4.50, 0.500, 71, 5.00, 0.500, 67, 5.50, 0.500};
double mp[6] = {0.00, 12, 5.00, 16, 13.5, 13}; //movement positions: {time to move at, midi note to move to}

class atTime {
    public:
        int pos; // Position of the first solenoid at the time
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

int main()
{
    //Generates empty array
    int size = (p[sizeof(p)/sizeof(double)-1] + p[sizeof(p)/sizeof(double)-2])/arrayTime +1;
    atTime f[size];
    
    // Make an array that contains every note (midi) held down at a time
    
    // loop through the array-1
        // get the position, from the time
        // get the notes held down at that time
        // generate relative positions
        // check for errors
    
    // turn everything off
    
}
