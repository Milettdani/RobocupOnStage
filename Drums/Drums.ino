#include "Melody.h"
#include "Player.h"

Player player;

void setup() {
  Serial.begin(115200);
  player.begin();
  player.main();
}

void loop() {
  player.main();
}
