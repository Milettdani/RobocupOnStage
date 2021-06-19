bool sb = false;
const int solenoid[7] = {A0, A1, A2, A3, A4, A5, 11};

const int d[30] = {136, 128, 128, 128, 136, 128, 128, 128, 136, 128, 128, 128, 192, 128, 128, 128, 136, 128, 128, 128, 136, 128, 136, 128, 136, 128, 128, 128, 200, 128};
const int arrSize = 30;
const double arrayTime = 0.250000;

int dig(long val, int n)
{
  String g = String(val);
  return String(g[n+1]).toInt();
  /*
  if (n >= 8 - g.length()) return String(g[n - (8-g.length())]).toInt();
  else return 0;*/
}

long toDec(int dec)
{
  String b2 = "";
  while (dec > 0) {
    if(dec%2 == 0) b2 += "0";
    else b2 += "1";
    dec >>= 1;
  }

  String b3 = "";
  for (int i = b2.length()-1; i>=0; i--) {
    b3 += String(b2[i]);
  }
  //Serial.println(b3);
  //Serial.println((long)b3.toInt());
  //Serial.println("\n");
  return b3.toInt();
}


void play(int dd[], as, at)
{
  int wt;
  long dec;

  unsigned long startTime = millis(), noteTime = 0;
  
  for (int t=0; t<as; t++) {
    noteTime = !noteTime ? startTime : noteTime; noteTime += (at * 1000);
    dec = toDec(dd[t]);
    for (int b=0; b<7; b++) {
      digitalWrite(solenoid[b], dig(dec, b));
      Serial.println(dig(dec, b));
    }
    Serial.println("\n");
    while(millis() - startTime < noteTime);
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), start, RISING);
  
  while (!sb) {}
  Serial.println("Starting\n");

  for (int i = 0; i < 7; i++) {pinMode(solenoid[i], OUTPUT); digitalWrite(solenoid[i], LOW);}

  play(d, arrSize, arrayTime);

  const int arrayTime2;
  const int arrSize2;
  const int d2[arrSize2]; //Get these from communication

  //Wait for start 2
  play(d2, arrSize2, arrayTime);
}

void loop() {
}

void start()
{
  sb = true;
}
