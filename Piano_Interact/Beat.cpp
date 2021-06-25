// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#include "Arduino.h"                                                                                                            // Include libraries
#include "Beat.h"

Beat::Beat(byte _key, float _time, int _move, String _debug) {                                                                  // Constuctor
  key = _key, time = _time, move = _move, debug = _debug;
}
