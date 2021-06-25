<!-- ABOUT THE PROJECT -->
## Piano Interact
```cpp
void playInteract(int interSize, float inter[])
{
  for (int i = 0; i<interSize; i++) {
    digitalWrite(solenoid[i%3 * 2], HIGH);
    int del = i<interSize-1 ? 1000*(inter[i+1] - inter[i]) -25 > 750 ? 750 : 1000*(inter[i+1] - inter[i]) -25 : 750;
    delay(del);
    digitalWrite(solenoid[i%3 * 2], LOW);
  }
}
```

## Run Plan
1. Put long MIDI into HTML
2. Paste out into DrumsRead.txt
3. run main_drums.exe -> into toDrums and toPiano.txt
4. run Drums.ino in Arduino
5. send start signal

### Interaction:

6. upload short MIDI to HTML
7. paste out into DrumsRead.txt
8. run main_drums.exe
9. send array from toDrums.txt (with "X" instead of "\n") to Drums, send array from toPiano.txt (with "X" instead of "\n") to Piano + 2nd start signal


## Video Script
#### Title & Identification
<!-- Team Name --> Hi, I'm David Halasz - and I'm Daniel Bacsur.
<!-- Country & Sub-league --> We are DDStudio from Hungary, Budapest and this is our entry for the robocup onstage preliminary competition.

#### Introduction and Summary
From the team, we both loved theaters and acted in musicals. When the covid situation started, we thought we would have a musical performance for the RoboCup jury as well. Hence the idea of making a robotic band.

#### Method / Robot Production / Design
<!-- A description of the choices made during the robots’ production, including the rationale underlying those choices.
Production includes the design, construction, programming, component selection, and overall process. Teams should indicate the programming language, sensors used, time and cost of development. -->
Our performance consists of a piano, a drum set, a so-called ‘clapping robot’ and an automated visual system.
The whole band is controlled by a computer that we wanted to use a raspberry pi for, but we had several problems with the ARM64 based system, so we stayed with windows.

The PC runs a program that communicates with the arduinos via UART to send starting signals and an array of what notes they have to play, which we get from a MIDI file. This program also controls scenes and sounds for the projector using a package called OBS-websocket.

#### Piano
we have attached a slider above the synthesizer on this slider there are eight solenoids which press down on the keys and a stepper motor which is responsible for the movement of the slider these are controlled by a simple mosfet system and an arduino nano microcontroller

#### Drum
we put a solenoid over each drum and symbol

the solenoids are connected to a mosfet system identical to the one on the piano and yet again an arduino nano

#### The Band
During the performance the band, consisting of the two robots accompanied by us playing another piano and a guitar, will play a song together. The plan was to then ask a member of the jury to play something on the drums, that the drums will play back with an accompaniment form the piano, with which the drum communicates to tell it when it has to play. Unfortunately, due to COVID-19 and the event being held online, we cannot accomplish this, hence we had to play something on the drums instead of a jury member. :((

#### Conclusion
We hope you enjoyed this video and will enjoy our performance. Thank you for your attention! This was DDStudio.

[Video](https://github.com/) &
[Raw Materials](https://github.com/)


## TODO:
- [ ] Change arrays from int to short, arrayTime from double to float
- [ ] Maybe combine 2 elemts of array
