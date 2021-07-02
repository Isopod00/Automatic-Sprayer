# Automatic Sprayer
By Anthony Brogni

This is my Automatic Sprayer project. I originally made a prototype of this project in 2017 but was not completely satisfied with the results, so I decided to go back and improve it. I have been making changes to this project ever since, and I believe it has improved greatly over the past 4 years. This project is an Arduino-controlled automatic sprayer that can be used to keep plants and pets hydrated while you're away from home. When you first plug it in you are prompted to configure the system, and then after that, you're good to go! Some nice features of this project are spray scheduling and spray duration control, a visual countdown clock to the next spray, and a manual spray button. Another notable feature that I recently added is Wifi-connectivity so that the project can connect to the user's home Wifi network, enabling over-the-air software updates.

![Full Project](https://github.com/Isopod00/Automatic-Sprayer/blob/Wifi-Enabled/Pictures/Full%20Stand.jpg?raw=true)

### Code

All of the code for this project is contained in a single [.ino script](https://github.com/Isopod00/Automatic-Sprayer/blob/Wifi-Enabled/Code/AutomaticSprayer/AutomaticSprayer.ino) that is run by an Arduino Mega 2560. 

The main functions of the code are to:
  1. Connect to my home wifi network to allow for over-the-air software updates
  2. Allow the user to configure system settings such as the interval between sprays and the spray duration using the touch screen
  3. Keep track of the time remaining until the next spray and display it to the user on the touch screen
  4. Allow the user to manually initiate a spray whenever they want via a digital button on the touch screen

The code for this project utilizes the Elegoo_GFX, Elegoo_TFTLCD, Touchscreen, WiFi101, and ArduinoOTA libraries, all of which can be found [here](https://github.com/Isopod00/Automatic-Sprayer/tree/Wifi-Enabled/Code/Libraries) in the project repository. The SPI library is also used, which is included in the Arduino IDE by default.

![Display](https://github.com/Isopod00/Automatic-Sprayer/blob/Wifi-Enabled/Pictures/Touchscreen%20Display.jpg?s=5)

### Electronics

The electronic components used in this project are:
  1. [Arduino MEGA 2560 REV3](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Projects-Compliant/dp/B01H4ZLZLQ/ref=sr_1_2_sspa?dchild=1&keywords=arduino+mega+2560&qid=1618870818&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyVUw2SFRZWkRSU0xXJmVuY3J5cHRlZElkPUEwMDYwOTc4TElIWk83ODlLWUZBJmVuY3J5cHRlZEFkSWQ9QTA4NzI5MDdCNVpYUFFCWjJFNFUmd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl)
  2. [ELEGOO 2.8 Inch TFT LCD Touch Screen](https://www.amazon.com/Elegoo-EL-SM-004-Inches-Technical-Arduino/dp/B01EUVJYME/ref=sr_1_2_sspa?dchild=1&keywords=elegoo+2.8+inch+tft&qid=1618870743&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExMzNKMTNMNzBIU0YwJmVuY3J5cHRlZElkPUEwMTIzMzQ5MzQ0MjlIRTRDUENXMiZlbmNyeXB0ZWRBZElkPUEwOTIyMDM3WFhPWkY1RTM2RjgyJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
  3. [L298N Motor Driver Board](https://www.amazon.com/HiLetgo-Controller-Stepper-H-Bridge-Mega2560/dp/B07BK1QL5T/ref=sr_1_1_sspa?dchild=1&keywords=L298N+motor+driver&qid=1623290580&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzQVVTUEhXUFhIUUhXJmVuY3J5cHRlZElkPUEwMDEwODE5M0tUWDEwVTZWR002SiZlbmNyeXB0ZWRBZElkPUEwOTgyODY3MVg4MjZTUFgxWjNFSCZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)
  4. [3.3v/5v Power Supply Module](https://www.amazon.com/JBtek-Breadboard-Supply-Arduino-Solderless/dp/B010UJFVTU/ref=sr_1_5?dchild=1&keywords=3.3v%2F5v+Power+Supply+Module&qid=1618870883&sr=8-5)
  5. [Motorized Spray Bottle](https://www.amazon.com/Dynamic-1-touch-multi-purpose-motorized-bottle/dp/B01LXJ0SPG/ref=sr_1_8?dchild=1&keywords=motorized+spray+bottle&qid=1618870772&sr=8-8)
  6. [ELEGOO 9V 1A Barrel Plug Power Adapter](https://www.amazon.com/ELEGOO-100V-240V-Converter-Adapter-Certificate/dp/B074BRR5YN/ref=sr_1_3?dchild=1&keywords=elegoo+9v+1a+power+supply&qid=1619274712&sr=8-3)
  7. [DC Barrel Plug Splitter](https://www.amazon.com/PHC-DC-3Y-Barrel-Splitter-Female/dp/B009AZZ4ES/ref=sr_1_10?dchild=1&keywords=1+Female+to+2+Male+barrel+jack+splitter&qid=1619274904&sr=8-10)
  8. [Flexible Breadboard Jumper Wires](https://www.amazon.com/Elegoo-EL-CP-004-Multicolored-Breadboard-arduino/dp/B01EV47GI4/ref=sr_1_2_sspa?crid=1GCV6BB0OBNDY&dchild=1&keywords=elegoo%2Bjumper%2Bcables&qid=1624300165&sprefix=elegoo%2Bjumper%2B%2Caps%2C181&sr=8-2-spons&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyVTg0SVlWTVEzMk9aJmVuY3J5cHRlZElkPUEwNTUxMTAxMUxIUVQ0VUJHUk9CVCZlbmNyeXB0ZWRBZElkPUEwOTQ1MzIxMUVLUFZPSjk1OTFYOSZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU&th=1)
  9. [Adafruit ATWINC1500 WiFi Breakout Board](https://www.amazon.com/Adafruit-2999-ATWINC1500-WiFi-Breakout/dp/B01GVI1NKA/ref=sr_1_1?dchild=1&keywords=adafruit+ATWINC1500&qid=1619275000&sr=8-1)

![Components](https://github.com/Isopod00/Automatic-Sprayer/blob/Wifi-Enabled/Pictures/Components%20in%20the%20Stand.jpg)

### 3D Printed Parts

For this project I designed and 3D Printed a stand for the sprayer that also houses the electronics inside of it to keep everything compact.

**CAD Program Used:** Fusion 360

**Slicer Program Used:** Ultimaker Cura                       
                          
**3D Printer Used:** Ender 5 Pro

**Filament Used:** Black PLA

All of the STL and sliced G-Code files can be found [here](https://github.com/Isopod00/Automatic-Sprayer/tree/Wifi-Enabled/CAD%20Files) in the project repository.
