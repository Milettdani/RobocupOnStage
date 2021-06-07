bool sb = false;
const int solenoid[7] = {A0, A1, A2, A3, A4, A5, 11};

const int d[15] = {136, 128, 136, 128, 192, 128, 136, 128, 136, 128, 136, 136, 200, 128, 128};
const int arrSize = 15;
const double arrayTime = 0.500000;

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


void play()
{
  int wt;
  long dec;
  for (int t=0; t<arrSize; t++) {
    dec = toDec(d[t]);
    for (int b=0; b<7; b++) {
      digitalWrite(solenoid[b], dig(dec, b));
      Serial.println(dig(dec, b));
    }
    Serial.println("\n");
    delay(arrayTime*1000);
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), start, RISING);
  
  while (!sb) {}
  Serial.println("Starting\n");

  for (int i = 0; i < 8; i++) {pinMode(solenoid[i], OUTPUT); digitalWrite(solenoid[i], LOW);}

  play();
  delay(5000);
}

void loop() {
}

void start()
{
  sb = true;
}
