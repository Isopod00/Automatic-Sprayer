//Automatic Sprayer
//By Anthony Brogni

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>   // Core (non-specific) touchscreen library

// Libraries required for WiFi connectivity & OTA updates //
#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoOTA.h>

// Libraries Required for integration with Adafruit.io //
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Enter sensitive data (like WiFi name & password) in the secrets tab (arduino_secrets.h) //
#include "arduino_secrets.h" 

// Wifi Settings //
char ssid[] = SECRET_SSID; // WiFi network SSID (name)
char pass[] = SECRET_PASS; // WiFi network password
int status = WL_IDLE_STATUS;

// Adafruit.io Settings //
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    SECRET_USERNAME
#define AIO_KEY         SECRET_KEY

//Set up the wifi client
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

#define MQTT_CONN_KEEPALIVE 43200; //The server will keep the socket open, unless it has not heard from the device in 12 hours

// Adafruit.io Feeds //
Adafruit_MQTT_Subscribe sprayStatus = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/spraying");
Adafruit_MQTT_Publish confirmSpray = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sprayconfirmed");

const int totalSprayTime = 825; // Measured in seconds
int remainingSprays;

// The control pins for the LCD can be assigned to any digital or analog pins, but using the analog pins allows for doubling up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// The min and max values for the x and y coordinates of the touchscreen //
#define TS_MINX 130
#define TS_MINY 130
#define TS_MAXX 940
#define TS_MAXY 940

// Assign human-readable names to some common 16-bit color values //
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BACKGROUNDCOLOR CYAN // Customize the background color of the display!
#define TEXTCOLOR BLACK // Customize the color of text that is displayed!

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int hours = 8;
int minutes = 0;
int seconds = 0;

int time = 0;
int waitTime = 0;
int wait = 15000;

int motor = 46;
int motorPin2 = 45;

bool spraying = false;

int assignedHours = 8;
int assignedWait = 15000;

bool answered1 = false;
bool answered2 = false;
bool answered3 = false;
bool answered4 = false;

void setup() {
  WiFi.setPins(35,37,39); // Configure pins for the Adafruit ATWINC1500 Breakout
  
  Serial.begin(9600); // Initialize serial 

  connectToNetwork(); // Connect to home WiFi network

  tft.reset();

  pinMode(motor, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  digitalWrite(motorPin2, LOW);

  mqtt.subscribe(&sprayStatus);

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
  } else if (identifier == 0x9328) {
  } else if (identifier == 0x4535) {
  } else if (identifier == 0x7575) {
  } else if (identifier == 0x9341) {
  } else if (identifier == 0x8357) {
  } else if (identifier == 0x0101) {
    identifier = 0x9341;
  }
  else {
    identifier = 0x9341;
  }
  tft.begin(identifier);
  
  boot();
  configSystem();

  remainingSprays = totalSprayTime / (assignedWait / 1000); // divide by 1000 converts milliseconds to seconds
}

void loop() {
  if (status == WL_CONNECTED) { 
    ArduinoOTA.poll(); // Check for OTA updates over WiFi
    MQTT_connect(); // Connect or Reconnect to the MQTT service
  } else {
    connectToNetwork(); // Try reconnecting to home WiFi network
  }
  
  Adafruit_MQTT_Subscribe *subscription;
  subscription = mqtt.readSubscription();

  if (subscription == &sprayStatus) {
    if (0 == strcmp((char *)sprayStatus.lastread, "ON")) {
      spray();
    }
  }

  // Check for button presses and add time to the loop so counting by seconds is accurate //
  buttonPress();
  delay(5);
  if (time == 60) {
    time = 0;
    subtractTime();
  }
  else {
    time++;
  }
}

void connectToNetwork() {
  // Check if the WiFi board is connected //
  if (WiFi.status() != WL_NO_SHIELD) {
    
    // Attempt to connect to Wifi network //
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
  }
  
  Serial.print("Successfully connected to SSID: ");
  Serial.print(WiFi.SSID());
  Serial.println("!");

  // start the WiFi OTA library with internal (flash) based storage
  ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);
  }
}
  
void boot() {
  tft.fillScreen(BACKGROUNDCOLOR);
  tft.setRotation(2);
  tft.setCursor(20, 2);
  tft.setTextColor(TEXTCOLOR);
  tft.setTextSize(2);
  tft.println("Automatic Sprayer");
  tft.setCursor(100, 22);
  tft.println("v3.5");
  tft.setCursor(80, 280);
  tft.println("Made by");
  tft.setCursor(40, 300);
  tft.println("Anthony Brogni");
  tft.setCursor(30, 140);
  tft.setTextSize(4);
  tft.println("Welcome!");
  delay(4000);
}

// Function used to connect and reconnect as necessary to the MQTT server //
void MQTT_connect() {
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  if(mqtt.connect() == 0) {
    Serial.println("MQTT Connected!");
  } else {
    Serial.println("Connect to MQTT FAILED");
  }
}

void configSystem() {
  assignedHours = 8;
  assignedWait = 15000;

  tft.fillScreen(BACKGROUNDCOLOR);
  tft.setCursor(20, 2);
  tft.setTextSize(2);
  tft.println("The default spray");
  tft.setCursor(15, 22);
  tft.println("interval is every");
  tft.setCursor(50, 42);
  tft.println("eight hours.");
  tft.setCursor(20, 102);
  tft.println("Would you like it");
  tft.setCursor(20, 122);
  tft.println("to stay that way?");
  drawButton(20, 210, 80, 50, 4, "Yes", 0);
  drawButton(140, 210, 80, 50, 4, "No", 15);
  while (!answered1) {
    if (status == WL_CONNECTED) { 
      ArduinoOTA.poll(); //Check for WiFi OTA updates
    }
  
    TSPoint p = ts.getPoint();

    if (p.z > ts.pressureThreshhold) {
      if (p.x > 280 && p.x < 400 && p.y > 185 && p.y < 420) {
        //This is important because the tft and touchscreen libraries are sharing pins
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        answered1 = true;

        tft.fillScreen(BACKGROUNDCOLOR);
        config2();
      }
      else if (p.x > 255 && p.x < 385 && p.y > 610 && p.y < 860) {
        //This is important because the tft and touchscreen libraries are sharing pins
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        answered1 = true;

        tft.fillScreen(BACKGROUNDCOLOR);

        tft.setCursor(0, 0);
        tft.setTextSize(2);
        tft.println("How many hours would");
        tft.setCursor(5, 20);
        tft.println("you like to set the");
        tft.setCursor(10, 40);
        tft.println("spray interval to?");

        drawButton(15, 120, 50, 50, 4, "2", 8);
        drawButton(95, 120, 50, 50, 4, "4", 8);
        drawButton(175, 120, 50, 50, 4, "6", 8);
        drawButton(15, 200, 50, 50, 4, "8", 8);
        drawButton(95, 200, 50, 50, 4, "10", -3);
        drawButton(175, 200, 50, 50, 4, "12", -3);

        while (!answered2) {
          if (status == WL_CONNECTED) { 
            ArduinoOTA.poll(); //Check for WiFi OTA updates
          }
  
          TSPoint p = ts.getPoint();

          if (p.z > ts.pressureThreshhold) {
            //This is important because the tft and touchscreen libraries are sharing pins
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
            
            if (p.x > 520 && p.x < 640 && p.y > 180 && p.y < 295) {
              answered2 = true;
              assignedHours = 2;
            }
            else if (p.x > 520 && p.x < 640 && p.y > 445 && p.y < 580) {
              answered2 = true;
              assignedHours = 4;
            }
            else if (p.x > 520 && p.x < 640 && p.y > 700 && p.y < 850) {
              answered2 = true;
              assignedHours = 6;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 180 && p.y < 295) {
              answered2 = true;
              assignedHours = 8;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 445 && p.y < 580) {
              answered2 = true;
              assignedHours = 10;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 700 && p.y < 850) {
              answered2 = true;
              assignedHours = 12;
            }
            if (answered2) {
              tft.fillScreen(BACKGROUNDCOLOR);
              config2();
            }
          }
        }
      }
    }
  }
}

void subtractTime() {
  if (seconds == 0) {
    if (minutes == 0) {
      if (hours == 0) {
        if (!spraying) {
          tft.fillRect(72, 19, 250, 18, BACKGROUNDCOLOR);
        }
        digitalWrite(motor, HIGH);
        delay(wait);
        digitalWrite(motor, LOW);

        hours = assignedHours;
        minutes = 0;
        seconds = 0;
      }
      else {
        if (!spraying) {
          tft.fillRect(72, 19, 250, 18, BACKGROUNDCOLOR);
        }
        hours = hours - 1;
        minutes = 59;
        seconds = 59;
      }
    }
    else {
      if (!spraying) {
        tft.fillRect(72, 19, 250, 18, BACKGROUNDCOLOR);
      }
      minutes = minutes - 1;
      seconds = 59;
    }
  }
  else {
    if (!spraying) {
      tft.fillRect(72, 19, 250, 18, BACKGROUNDCOLOR);
    }
    seconds = seconds - 1;
  }
  if (hours == 0) {
    if (minutes == 0) {
      if (seconds == 0) {
        if (!spraying) {
          tft.fillRect(0, 0, 300, 50, BACKGROUNDCOLOR);
        }
        tft.setTextSize(2);
        tft.setCursor(10, 20);
        tft.print("Spraying Enclosure");
        confirmSpray.publish(1.0);

        digitalWrite(motor, HIGH);
        delay(wait);
        digitalWrite(motor, LOW);

        confirmSpray.publish(0.0);
        remainingSprays--;
        
        hours = assignedHours;
        minutes = 0;
        seconds = 0;
      }
    }
    if (!spraying) {
      tft.fillRect(0, 19, 300, 18, BACKGROUNDCOLOR);
    }
  }
  if (!spraying) {
    tft.setTextSize(2);
    tft.setCursor(20, 1);
    tft.print("Time Until Next");
    tft.setCursor(5, 21);
    tft.print("Spray: ");
    tft.setCursor(85, 21); 
    tft.print(hours);
    tft.print(" : ");
    tft.print(minutes);
    tft.print(" : ");
    tft.print(seconds);
  }
}

void spray(){
   spraying = true;
   confirmSpray.publish(1.0);
   
   tft.fillRect(0, 0, 300, 50, BACKGROUNDCOLOR);
   tft.setTextSize(2);
   tft.setCursor(10, 20);
   tft.print("Spraying Enclosure");
   digitalWrite(motor, HIGH);
   while (spraying) {
      delay(1000);
      subtractTime();
      waitTime = waitTime + 1000;
      if (waitTime == wait) {
        waitTime = 0;
        digitalWrite(motor, LOW);
        spraying = false;
        confirmSpray.publish(0.0);
        remainingSprays--;
      }
    }
    tft.fillRect(0, 15, 300, 30, BACKGROUNDCOLOR);
    tft.setCursor(20, 1);
    tft.print("Time Until Next");
    tft.setCursor(5, 21);
    tft.print("Spray: ");
}

void endConfig() {
  wait = assignedWait;
  hours = assignedHours;
  tft.fillScreen(BACKGROUNDCOLOR);
  tft.setTextSize(2);
  tft.setCursor(20, 1);
  tft.print("Time Until Next");
  tft.setCursor(5, 21);
  tft.print("Spray: ");
  tft.print(hours);
  tft.print(" : ");
  tft.print(minutes);
  tft.print(" : ");
  tft.print(seconds);
  drawButton(50, 112, 130, 50, 4, "Spray", 0);
  drawButton(15, 250, 210, 40, 3, "Reconfigure", 0);
}

void drawButton(int x1, int y1, int width, int height, int textSize, String text, int textOffset) {
  tft.setTextColor(WHITE);
  tft.fillRect(x1, y1, width, height, BLACK);
  tft.drawRect(x1, y1, width, height, WHITE);
  tft.setCursor(x1 + 5 + textOffset, y1 + 10);
  tft.setTextSize(textSize);
  tft.print(text);
  tft.setTextColor(TEXTCOLOR);
}

void buttonPress() {
  TSPoint p = ts.getPoint();

  if (p.z > ts.pressureThreshhold) {
    //This is important because the tft and touchscreen libraries are sharing pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    
    if (p.x > 190 && p.x < 260 && p.y > 180 && p.y < 860) {
      hours = 8;
      minutes = 0;
      seconds = 0;

      answered1 = false;
      answered2 = false;
      answered3 = false;
      answered4 = false;

      configSystem();
    }
    if (p.x > 520 && p.x < 660 && p.y > 295 && p.y < 705) {
      spray();
    }
  }
  //This is important because the tft and touchscreen libraries are sharing pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

void config2()
{
  tft.setCursor(20, 2);
  tft.setTextSize(2);
  tft.println("The default spray");
  tft.setCursor(5, 22);
  tft.println("duration is fifteen");
  tft.setCursor(80, 42);
  tft.println("seconds.");
  tft.setCursor(15, 102);
  tft.println("Would you like it ");
  tft.setCursor(15, 122);
  tft.println("to stay that way?");
  drawButton(20, 210, 80, 50, 4, "Yes", 0);
  drawButton(140, 210, 80, 50, 4, "No", 15);

  while (!answered3) {
    if (status == WL_CONNECTED) { 
      ArduinoOTA.poll(); //Check for WiFi OTA updates
    }
  
    TSPoint p = ts.getPoint();

    if (p.z > ts.pressureThreshhold) {
      if (p.x > 280 && p.x < 400 && p.y > 185 && p.y < 420) {
        //This is important because the tft and touchscreen libraries are sharing pins
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        answered3 = true;
        endConfig();
      }
      else if (p.x > 255 && p.x < 385 && p.y > 610 && p.y < 860) {
        //This is important because the tft and touchscreen libraries are sharing pins
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        tft.fillScreen(BACKGROUNDCOLOR);

        answered3 = true;

        tft.setCursor(20, 0);
        tft.setTextSize(2);
        tft.println("How many seconds");
        tft.setCursor(15, 20);
        tft.println("would you like to");
        tft.setCursor(40, 40);
        tft.println("set the spray");
        tft.setCursor(45, 60);
        tft.println("duration to?");

        drawButton(15, 120, 55, 50, 4, "5", 10);
        drawButton(95, 120, 55, 50, 4, "10", 0);
        drawButton(175, 120, 55, 50, 4, "15", 0);
        drawButton(14, 200, 55, 50, 4, "20", 0);
        drawButton(94, 200, 55, 50, 4, "25", 0);
        drawButton(174, 200, 55, 50, 4, "30", 0);

        while (!answered4) {
          if (status == WL_CONNECTED) { 
            ArduinoOTA.poll(); //Check for WiFi OTA updates
          }
  
          TSPoint p = ts.getPoint();

          if (p.z > ts.pressureThreshhold) {
            if (p.x > 520 && p.x < 640 && p.y > 180 && p.y < 295) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 5000;
            }
            else if (p.x > 520 && p.x < 640 && p.y > 445 && p.y < 580) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 10000;
            }
            else if (p.x > 520 && p.x < 640 && p.y > 700 && p.y < 850) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 15000;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 180 && p.y < 295) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 20000;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 445 && p.y < 580) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 25000;
            }
            else if (p.x > 285 && p.x < 430 && p.y > 700 && p.y < 850) {
              //This is important because the tft and touchscreen libraries are sharing pins
              pinMode(XM, OUTPUT);
              pinMode(YP, OUTPUT);

              answered4 = true;
              assignedWait = 30000;
            }
            if (answered4) {
             endConfig();
            }
          }
        }
      }
    }
  }
}
