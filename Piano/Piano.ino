#define ui unsigned int
const int solenoid[8] = { A0, A1, A2, A3, A4, A5, 11, 12 }; //move after notes played: e.g.: {4, 384}: play(384), wait arrayTime, move 4
//const int dirPin = 6, stepPin = 7, enPin = 5;

void playInteract(int interSize, float inter[])
{
  for (int i = 0; i<interSize; i++) {
    digitalWrite(solenoid[i%3 * 2], HIGH);
    int del = i<interSize-1 ? 1000*(inter[i+1] - inter[i]) -25 > 750 ? 750 : 1000*(inter[i+1] - inter[i]) -25 : 750;
    delay(del);
    digitalWrite(solenoid[i%3 * 2], LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  for (int i=0; i<8; i++) {
    pinMode(solenoid[i], OUTPUT);
    digitalWrite(solenoid[i], LOW);
  }

  int s = 3;
  float inter[3] = {1.500000, 2.0, 2.25};
  playInteract(s, inter);
  Serial.println("END");
}

void loop(){}