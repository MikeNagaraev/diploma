/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include <SoftwareSerial.h> 
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3; //rx
//static const uint8_t D10  = 1; //tx
int speed = 9600;
SoftwareSerial* serial = new SoftwareSerial(D9, D10);
void setup() {
  serial->begin(speed);
}

void loop() {
  serial->print('\007');
  delay(100);
}
