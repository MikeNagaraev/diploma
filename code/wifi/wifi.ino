/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

const char* ssid = "Dima";
const char* password = "15032009";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer wifiServer(80);

void setup() {

  Serial.begin(115200);

  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}

void loop() {

  WiFiClient client = wifiServer.available();
  String str = "";
  if (client) {

    while (client.connected()) {

      while (client.available() > 0) {
        char c = client.read();
        str += c;
        client.write(c);
      }

      delay(10);
    }

    client.stop();
    Serial.println(str);
    Serial.println("Client disconnected");

  }
}

