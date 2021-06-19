// RoboCup OnStage // Daniel Bacsur & David Halasz // ------------------------------------------------------------------------- // Comments
#include "Melody.h"                                                                                                             // Include libraries
#include "Player.h"

Player player;
                                                                                                                                // 
void setup() { // ------------------------------------------------------------------------------------------------------------- // Setup function
  Serial.begin(115200);
  player.begin();
  delay(2000);
}
void loop() {
  player.updateSerial();
}
