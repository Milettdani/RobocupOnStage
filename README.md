## RoboCupOnStage2021 - DDStudio
#### Programming
<!--
•	Efficient programming
•	Advanced programming (optimized, elegant)
•	Innovative programming solutions
•	Development of libraries (as distinct from functions)
•	Machine Learning
-->

Here is the 
[MIDI](https://github.com/othneildrew/Best-README-Template/issues) and the
[NOTE](https://github.com/othneildrew/Best-README-Template/issues) based sofrware.

#### Mechanical Systems
<!--
•	Mechanical systems that are Reliable / Complex / Innovative
•	Mechanisms that have been developed for very high precision, or for
mechanically ‘difficult’ situations
•	Advanced and functional arms/hands/faces
•	The robot has the ability to manipulate objects
•	The robot can move on any terrain
•	Automatic balance system
•	Appropriate actuators used
-->
#### Electronic systems
<!--
•	Some of the electronics have been custom built with different functionality than offered in the market
•	Innovative use and integration of sensors
•	Useful GPS, gyroscope and accelerometer
•	Innovative use of technologies to aid the robot (e.g. cameras 360º, alternative source power (hydrogen, solar), holograms, different micro-controllers etc.)
-->
#### Robotic Communication & Interraction
<!--
•	Useful robotic communication
•	Useful vision recognition
•	Useful voice recognition
•	The robot has the ability to talk
•	Development of communication architectures
•	Sensors used to achieve robot-robot interaction, for example robots following robots
•	Sensors used to achieve robot-human interaction
-->
alma

#### Notes
We created it from scratch
The robots play on instruments designed for humans, therefore we had to solve two important tasks:
Teach them to play from “sheet music”
Make them be able to play the music they read (i.e. learn to play the instrument)
This hardware-software combination has been created so that the robots can play essentially any music (limitations: it can only be at one place at a time -> no two hands; it can only play notes together that are a given distance from each other).
<br><br>
Complex task: many different devices need to communicate and work together
Arduino (Drums), Arduino (Piano), Controller, MIDI javascript, C++ for conversion
Upload MIDI to javascript - Parses important information from file; Couldn’t find a way to properly edit a file -> Copy Drums, copy Piano buttons copy the needed text
From this data the executables (created in C++) create an array of numbers, which stores the state of each solenoid at a given time as well as the slider’s position. Due to memory problems on the Arduino, we couldn’t use the numbers as we intended to, since they could not be stored in “int”-s (100000001). To overcome this we looked at these numbers as if they were in base 2 and converted them to base 10 (e.g. 100000001 became 257)
For the piano we also had to figure out how much it had to move between each note. To do this we created a function that returns the color of a given note (white or black) and a function that can return the distance between two notes (one unit being the distance between a black and white key, since that is the smallest movement we will have to make). This was not as simple as it seems, since there isn’t a black key next to each white key and the values for the notes are given by the previous one +1. This means that two notes with a difference of 6 could be 6, 7 or 8 units apart. With these functions we could easily calculate when the piano cannot play a given note in its current position.
This information is then passed on to the controller program, which communicates with the Arduinos.
<br><br>
To make the drums more human we wanted to have two robotic arms, but we decided it would be too much time and not very efficient.
We had to make the piano as steady and stable as possible, so we decided it should have 1 dimension of movement.





#### David xd
* Latest MIDI
* main.cpp (with movement)
* latest main_drums.cpp
* Drums safety with clapper
* Drums midi
* Piano safety with interact
* Piano MIDI with interact!
* controller with clapper and special
* Clapper code
