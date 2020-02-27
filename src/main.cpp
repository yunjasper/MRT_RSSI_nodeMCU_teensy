/*
   McGill Rocket Team - Ground Station Receiver
   
   This code goes on the nodeMCU v0.9 wifi module.

  Added serial communication with nodeMCU to display
  the RSSI values on the website

   Date:   Feb 26, 2020
   Author: Jasper Yun
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index_HTML.h" // file containing the html/javascript code for the web page

String data = "initial data...waiting...";  // initial message to display
String buff = ""; // buffer for receiving string data over serial
String text = ""; // string to store message to be posted on the web page

const char *ssid = "testNodeMCU"; // details for the access point wifi network
const char *password = "password";

ESP8266WebServer server(80);  // begin the html server at port 80

/*
 * Handles requests to the server...I think. I'm not totally sure what this function 
 * does; the INDEX_HTML refers to the html/javascript code contained in the index_HTML.h file.
 */
void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

/*
 * Sets up the nodeMCU in access point mode, and prepares the server.
 */
void setup() {
  pinMode(D1, OUTPUT);  // set pin D1 to light up an LED for debugging
  digitalWrite(D1, HIGH);

  Serial.begin(115200);
  Serial.println();

  // configure the access point, print the details on the serial monitor
  Serial.print("Configuring access point…");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // when server is on the page /data.txt, send the data to the page text/html I think
  server.on("/data.txt", [](){
    text = (String) data;
    server.send(200, "text/html", text);
 });

  // when server is on home page, do this:
  server.on("/", [](){
    server.send(200, "text/html", INDEX_HTML);
  });

  // begin the server, print some messages
  server.begin();
  Serial.println("Web server started!");
  
  Serial.println("HTTP server started");
}

/*
 * Main loop checks the serial buffer and reads serial data sent from 
 * the Teensy 3.5. Then, it sets (string) data equal to the incoming message
 * that was received over serial, and this new value of data is updated on 
 * the web page through AJAX (Asynchronous JavaScript And XML).
 * 
 * Apparently, AJAX is very powerful: https://www.w3schools.com/xml/ajax_intro.asp
 */
void loop() {
  // Read serial
 while(Serial.available() > 0)
  {
    char a = Serial.read();
    if (a == '\n')
    {
      if (buff != "") {
        data = buff;  // this is what is displayed on the web page
        Serial.println(data);
      }
      buff = "";
      break;  // break the read process if end of message
    }
    else
    {
      buff += a;  // add the received character to the buffer
      //Serial.println(buff); // for debudgging
    }
  }
  // update the webpage
  server.handleClient();
}
