# Automatic Sprayer
By Anthony Brogni

This is my Automatic Sprayer project. I made the first prototype of this project back in 2017, but I was unsatisfied with the results and so I decided to go back and improve it. This project is an Arduino-controlled automatic sprayer that can be used to keep plants and pets hydrated while you're away from home. When you first plug it in you are prompted to configure the system, and then after that you're good to go! Some nice features of this project are spray schedule and spray duration control, a visual count-down clock until the next spray, and a manual spray button.

### Code

All of the code for this project is in a single .ino script that is run by the Arduino Mega. 

The main functions of the code are to:
  1. Connect to my home wifi network to allow for OTA software update functionality
  2. Allow the user to configure system settings such as the interval between sprays and the spray duration using the touch screen
  3. Keep track of the time remaining until the next spray and display it to the user on the screen
  4. Allow the user to manually initiate a spray whenever they want via a digital button on the touch screen

The code for this project utilizes the Elegoo_GFX, Elegoo_TFTLCD, Touchscreen, SPI, WiFi101, and ArduinoOTA libraries, all of which can be found [here](https://github.com/Isopod00/Automatic-Sprayer/tree/master/Libraries) in the project repository.

### Electronics

The electronic components used in this project are:
  1. [Arduino MEGA 2560 REV3](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Projects-Compliant/dp/B01H4ZLZLQ/ref=sr_1_2_sspa?dchild=1&keywords=arduino+mega+2560&qid=1618870818&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyVUw2SFRZWkRSU0xXJmVuY3J5cHRlZElkPUEwMDYwOTc4TElIWk83ODlLWUZBJmVuY3J5cHRlZEFkSWQ9QTA4NzI5MDdCNVpYUFFCWjJFNFUmd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl)
  2. [ELEGOO 2.8 Inch TFT LCD Touch Screen](https://www.amazon.com/Elegoo-EL-SM-004-Inches-Technical-Arduino/dp/B01EUVJYME/ref=sr_1_2_sspa?dchild=1&keywords=elegoo+2.8+inch+tft&qid=1618870743&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExMzNKMTNMNzBIU0YwJmVuY3J5cHRlZElkPUEwMTIzMzQ5MzQ0MjlIRTRDUENXMiZlbmNyeXB0ZWRBZElkPUEwOTIyMDM3WFhPWkY1RTM2RjgyJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
  3. [5v 1 Channel Relay Module](https://www.amazon.com/Tolako-Arduino-Indicator-Channel-Official/dp/B00VRUAHLE/ref=sr_1_3?dchild=1&keywords=5v+1+Channel+Relay+Module&qid=1618870851&sr=8-3)
  4. [3.3v/5v Power Supply Module](https://www.amazon.com/JBtek-Breadboard-Supply-Arduino-Solderless/dp/B010UJFVTU/ref=sr_1_5?dchild=1&keywords=3.3v%2F5v+Power+Supply+Module&qid=1618870883&sr=8-5)
  5. [Motorized Spray Bottle](https://www.amazon.com/Dynamic-1-touch-multi-purpose-motorized-bottle/dp/B01LXJ0SPG/ref=sr_1_8?dchild=1&keywords=motorized+spray+bottle&qid=1618870772&sr=8-8)
  6. [ELEGOO 9V 1A Barrel Plug Power Adapter](https://www.amazon.com/ELEGOO-100V-240V-Converter-Adapter-Certificate/dp/B074BRR5YN/ref=sr_1_3?dchild=1&keywords=elegoo+9v+1a+power+supply&qid=1619274712&sr=8-3)
  7. [DC Barrel Plug Splitter](https://www.amazon.com/PHC-DC-3Y-Barrel-Splitter-Female/dp/B009AZZ4ES/ref=sr_1_10?dchild=1&keywords=1+Female+to+2+Male+barrel+jack+splitter&qid=1619274904&sr=8-10)
  8. [Adafruit ATWINC1500 WiFi Breakout Board](https://www.amazon.com/Adafruit-2999-ATWINC1500-WiFi-Breakout/dp/B01GVI1NKA/ref=sr_1_1?dchild=1&keywords=adafruit+ATWINC1500&qid=1619275000&sr=8-1)

### 3D Printed Parts

For this project I designed and 3D Printed a stand for the sprayer that also houses the electronics inside of it to keep everything compact.

**CAD Program Used:** Fusion 360

**Slicer Program Used:** Ultimaker Cura 

**3D Printer Used:** Ender 5 Pro

**Filament Used:** Black PLA

All of the STL and sliced G-Code files can be found [here](https://github.com/Isopod00/Automatic-Sprayer/tree/master/CAD%20Files) in the project repository.
