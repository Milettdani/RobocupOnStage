// RoboCup OnStage // Daniel Bacsur // ---------------------------------------------------------------------------------------- // Comments
#ifndef Beat_h                                                                                                                  // Include libraries
#define Beat_h;
#include "Arduino.h"

class Beat { // --------------------------------------------------------------------------------------------------------------- // Beat class
  public:                                                                                                                       // Pubic things
    byte key; float time; int move; String debug;                                                                               // Variables
    Beat(byte _key, float _time, int _move, String _debug = "NONE");                                                            // Constructor
};

#endif
