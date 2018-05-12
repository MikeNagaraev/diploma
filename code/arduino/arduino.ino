#include <SoftwareSerial.h> 

const int rx = 10;
const int tx = 11;
const int speed = 9600;
const String GET_IP_ADDRESS = "GET_IP_ADDRESS";
const String SET_IP_ADDRESS = "SET_IP_ADDRESS";
const String SET_SSID="SET_SSID";
const String GET_SSID="GET_SSID";
const String SET_PASSWORD="SET_PASSWORD";
const String GET_PASSWORD="GET_PASSWORD";
const String CONNECT_TO_WIFI="CONNECT_TO_WIFI";
SoftwareSerial* wifiModule = new SoftwareSerial(rx, tx);;  

void setup() {
  Serial.begin(speed); 
  wifiModule->begin(speed);
  wifiModule->listen();  
  Serial.println("Connection wifi...");
}

void loop() {
  String cmd = Serial.readString();
  cmd = cmd.substring(0, cmd.length() - 2);
  if (cmd.length() > 0) {
    sendToWifiModule(cmd);
    Serial.println("From serial: " + cmd);
  }  
  if (wifiModule->available()) {
    String data = wifiModule->readString();
    Serial.println("From wifiModule: " + data);
  }
  delay(100);
}

void sendToWifiModule(String data) {
    wifiModule->print("*" + data);  
}

void test() {
  sendToWifiModule("test");
}

void setIpAddress(String ip) {
  sendToWifiModule(SET_IP_ADDRESS);
  while(wifiModule->readString() != "SET_IP_ADDRESS_OK");
  sendToWifiModule(ip);
}

void getIpAddress() {  
  sendToWifiModule(GET_IP_ADDRESS);
  return wifiModule->readString();
}


