#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index_HTML.h"

String data = "initial data...waiting...";
String buff = "";
String text = "";

boolean newData = false;


const char *ssid = "testNodeMCU";
const char *password = "password";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void setup() {
  //digitalWrite(5, HIGH);  // for debugging, write LED pin high (D1 pin)
  digitalWrite(D1, HIGH);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point…");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/data.txt", [](){
    text = (String) data;
    server.send(200, "text/html", text);
 });
  server.on("/", [](){
    server.send(200, "text/html", INDEX_HTML);
  });
  server.begin();
  Serial.println("Web server started!");
  
  Serial.println("HTTP server started");
 
}

void loop() {
  // Read serial
 while(Serial.available() > 0)
  {
    char a = Serial.read();
    if (a == '\n')
    {
      if (buff != "") {
        data = buff;
        Serial.println(data);
      }
      buff = "";
      break;  // break the read process if end of message
    }
    else
    {
      buff += a;
      Serial.println(buff);
    }
  }
  // update the webpage
  server.handleClient();
}
