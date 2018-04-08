//
#include <SoftwareSerial.h> 
int rx = 8;
int tx = 9;
int speed = 9600;
String readString;
SoftwareSerial* serial_ptr;  
void setup() {
  serial_ptr = new SoftwareSerial(rx, tx);
  Serial.begin(speed);
  serial_ptr->begin(speed);
  serial_ptr->listen();
// 
}

void loop() {
  if (serial_ptr->available()) {
    readString = serial_ptr->read();
    Serial.print(readString);
    Serial.println();
  }
  delay(100);
}
