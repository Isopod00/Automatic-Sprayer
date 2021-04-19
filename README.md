# Automatic Sprayer
By Anthony Brogni

This is my Automatic Sprayer project. I made the first prototype of this project back in 2017, but I was unsatisfied with the results and so I decided to go back and improve it. This project is an Arduino-controlled automatic sprayer that can be used to keep plants and pets hydrated while you're away from home. When you first plug it in you are prompted to configure the system, and then after that you're good to go! Some nice features of this project are spray schedule and spray duration control, a visual count-down clock until the next spray, and a manual spray button.

### Code

All of the code for this project is in a single .ino script that is run by the Arduino Mega. 

The main functions of the code are to:
  1. Allow the user to configure system settings such as the interval between sprays and the spray duration using the touch screen
  2. Keep track of the time remaining until the next spray and display it to the user on the screen
  3. Allow the user to manually initiate a spray whenever they want via a digital button on the touch screen

### Electronics

The electronic components used in this project are:
  1. Arduino MEGA 2560 REV3
  2. ELEGOO 2.8 Inch TFT LCD Touch Screen
  3. 5v 1 Channel Relay Module
  4. 3.3v/5v Power Supply Module
  5. Motorized Spray Bottle

### 3D Printed Parts

For this project I designed and 3D Printed a stand for the sprayer that also houses the electronics inside of it to keep everything compact.

CAD Program Used: Fusion 360
Slicer Program Used: Ultimaker Cura
Filament Used: PLA

All of the STL and sliced G-Code files can be found [here](https://github.com/Isopod00/Automatic-Sprayer/tree/master/CAD%20Files) on the project repository.
