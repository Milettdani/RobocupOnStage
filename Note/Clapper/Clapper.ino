void setup()
{
  Serial.begin(115200);
  pinMode( 12, INPUT );
  Serial.print("C");
}

unsigned long lastTap = 0; /* when the last tap happened */
unsigned long currentTimer[2] = { 500, 500 };  /* array of most recent tap counts */
long lastClap = 0;
int remCount = 0;

void loop()
{
  int tapState = digitalRead( 12 );
  if( tapState == HIGH && millis() - lastTap > 100 )
    if(millis() - lastTap > 2000) {
      currentTimer[0] = 500;
      currentTimer[1] = 500;
      lastTap = millis();
    }
    else
      tap();
  long avg = (currentTimer[0] + currentTimer[1]) / 2;
  if(remCount > 0) {
    if(lastClap + avg < millis()){
      if(remCount != 4) Serial.print("DS");
      lastClap += avg;
      remCount--;
    }
  }
}

void tap()
{
  currentTimer[1] = currentTimer[0];
  currentTimer[0] = millis() - lastTap;
  lastTap = millis();
  lastClap = lastTap;
  remCount = 4;
}
