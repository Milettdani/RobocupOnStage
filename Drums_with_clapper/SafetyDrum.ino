// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#include "Player.h"                                                                                                             // Include libraries

Player player;                                                                                                                  // Declare player

void setup() { // ------------------------------------------------------------------------------------------------------------- // Setup
  Serial.begin(115200);                                                                                                         // Begin sebug on serial port
  player.begin();                                                                                                               // Begin player                                                                                                                  // Start delay
  Serial.print('D');
}
void loop() { // -------------------------------------------------------------------------------------------------------------- // Main Loop
  player.updateSerial();
}
