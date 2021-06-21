<!-- ABOUT THE PROJECT -->
## About The Project
...

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

[Video](https://github.com/) &
[Raw Materials](https://github.com/)


## TODO:
- [ ] Make `main_drums.cpp` read array from .txt
- [X] Make `main_drums.cpp` write arrays to .txt files.
- [ ] Make communicators write to serial from .txt-s
