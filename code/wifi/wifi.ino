/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

#include <SoftwareSerial.h> 

const char* ssid = "sss";
const char* password = "10071975";

SoftwareSerial* serial = new SoftwareSerial(D9, D10);
IPAddress ip(192, 168, 1, 11);  
IPAddress gateway(192, 168, 1, 1);  
IPAddress subnet(255, 255, 0, 0); 

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer wifiServer(80);

void setup() {
//  Serial.begin(9600); - not working
	serial->begin(9600);

//
	delay(1000);
//  WiFi.begin(ssid, password);
//
  WiFi.config(ip,gateway , subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
//    Serial.println("Connecting to WiFi..");
  }

//  Serial.println("Connected to the WiFi network");
//  Serial.println(WiFi.localIP());
//
  wifiServer.begin();
}

void loop() {
//    serial->print('\007');
    delay(100);
    WiFiClient client = wifiServer.available();
    String cmd = "";
    if (client) {
  
      while (client.connected()) {
  
        while (client.available() > 0) {
          char c = client.read();
  		    cmd += c;
          client.write(c);
        }
  
        delay(10);
      }
  	handleComand(cmd);
  	serial->print(cmd);

    client.stop();
//    Serial.println(cmd);

  }
}

void handleComand(String cmd) {

}

