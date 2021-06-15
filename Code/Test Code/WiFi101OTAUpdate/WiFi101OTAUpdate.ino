/* This example connects to a WPA encrypted WiFi network.
 Then it prints the MAC address of the Wifi module,
 the IP address obtained, and other network details.
 It then polls for sketch updates over WiFi, sketches
 can be updated by selecting a network port from within
 the Arduino IDE: Tools -> Port -> Network Ports, or by 
 using the custom "Arduino OTA" programmer and Sketch -> Upload Using Programmer.

 Circuit:
 * WiFi module attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 16 January 2017
 by Sandeep Mistry */
 
#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoOTA.h>

#include "arduino_secrets.h" 

/////// Wifi Settings - please enter your sensitive data in the Secret tab (arduino_secrets.h)///////
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password

int status = WL_IDLE_STATUS;

void setup() {
  //Initialize serial:
  Serial.begin(9600);

  //Configure pins for the Adafruit ATWINC1500 Breakout
  WiFi.setPins(35,37,39);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }

  // start the WiFi OTA library with internal (flash) based storage
  ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);

  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // check for WiFi OTA updates
  ArduinoOTA.poll();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
