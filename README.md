# DDStudio Robocup Onstage - Technical Interview

## Background
* The robots play on instruments designed for humans, therefore we had to solve two important tasks:
  * we had to teach them to play from “sheet music”,
  * make them be able to play the music they read (i.e. learn to play the instrument)
* This hardware-software combination has been created so that the robots can play essentially any music (limitations: it can only be at one place at a time -> no two hands; it can only play notes together that are a given distance from each other).

## Programming
* Complex task: many different devices need to communicate and work together
  * Arduino (Drums), Arduino (Piano), Controller, MIDI javascript, C++ for conversion
* Upload MIDI to javascript - Parses important information from file; Couldn’t find a way to properly edit a file -> Copy Drums, copy Piano buttons copy the needed text
* From this data the executables (created in C++) create an array of numbers, which stores the state of each solenoid at a given time as well as the slider’s position. Due to memory problems on the Arduino, we couldn’t use the numbers as we intended to, since they could not be stored in “int”-s (100000001). To overcome this we looked at these numbers as if they were in base 2 and converted them to base 10 (e.g. 100000001 became 257)
* For the piano we also had to figure out how much it had to move between each note. To do this we created a function that returns the color of a given note (white or black) and a function that can return the distance between two notes (one unit being the distance between a black and white key, since that is the smallest movement we will have to make). This was not as simple as it seems, since there isn’t a black key next to each white key and the values for the notes are given by the previous one +1. This means that two notes with a difference of 6 could be 6, 7 or 8 units apart. With these functions we could easily calculate when the piano cannot play a given note in its current position.
* This information is then passed on to the controller program, which communicates with the Arduinos and a recording software called OBS. This controller starts two local instances: one for the virtual camera and one for the slideshow. Once run, the program gives a start signal to the Arduinos and to OBS to start the slideshow. Later in the performance we use this program to send the interaction data to the Arduinos. We call this function “special”.

## Mechanical Systems
* To make the drums more human we wanted to have two robotic arms, but we decided it would not be very efficient, since it could only play two notes at a time and could have trouble moving at high enough speeds to reach all the drums in time.
* We wanted to make the piano as steady and stable as possible, but still resemble a human in playing style, so we decided there should be a slider, with 1 dimension of movement, with solenoids attached to it to resemble fingers on a human hand. The slider sits on an aluminium extrusion and is moved by a connected stepper motor that is latched onto a rubber timing belt. This construction was beneficial for the slider’s movement to be as precise as possible.
* Since a big part of our performance relied on sound and sound quality, we put together a sound system, where all the instruments’ audio is connected to a mixer. Like this we have full control over the sound that we hear and separately what the jury hears. Unfortunately during the performance this wasn’t very audible because of zoom.

## Electronic Systems
* For controlling the solenoids and the stepper motor, we needed to combine the 12V necessary for them to function with the Arduino’s 5V logic output. To resolve this issue we designed a PCB for a MOSFET system using Autodesk Eagle to design that was then manufactured by JLCPCB (not a sponsor).
* For the clapper-robot we use a digital microphone, which gives a signal, when it detects a sound that is above a given amplitude threshold.

## Robotic Communication & Interaction
* During our performance we play random notes on the drums that are recorded into a DAW. This is then exported as a MIDI file and uploaded into our MIDI converting program. The converted code is then sent to the robots. The drums play back what we recorded/played and the piano plays arpeggios over it. During this process we interact with the robots by telling them what to play and the drum communicates with the piano to tell it how it should play the arpeggios.
* A similar interaction happens with the clapper-robot: the robot records the time between our claps, which it then sends to the drums for it to play our claps back.

