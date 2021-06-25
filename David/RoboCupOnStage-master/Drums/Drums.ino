// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#include "Melody.h"
#include "Player.h"

Player player;

void setup() {
  Serial.begin(115200);
  player.begin();
  pinMode(LED_BUILTIN, OUTPUT); 
  delay(2000);
  Serial.print('D');
}

void loop() {
  player.main();
  digitalWrite(LED_BUILTIN,
    player.isPlaying ? ((millis() - player.startTime) % 250) < 100 ?
    HIGH : LOW : (millis() % 2000) < 100 ? HIGH : LOW
  );
}
