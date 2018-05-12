#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

String ssid = "";
String password = "";

const String GET_IP_ADDRESS = "GET_IP_ADDRESS";
const String SET_IP_ADDRESS = "SET_IP_ADDRESS";
const String SET_SSID = "SET_SSID";
const String GET_SSID = "GET_SSID";
const String GET_LOCAL_SSID = "GET_LOCAL_SSID";
const String SET_PASSWORD = "SET_PASSWORD";
const String GET_PASSWORD = "GET_PASSWORD";
const String CONNECT_TO_WIFI = "CONNECT_TO_WIFI";
const String WIFI_SESSION = "WIFI_SESSION";
const int STATE_OK = 4;


SoftwareSerial* controller = new SoftwareSerial(D9, D10);
WiFiServer wifiServer(80);
IPAddress ip(192, 168, 1, 229);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void setup() {
  controller->begin(9600);
  controller->listen();
  wifiServer.begin();
}

void loop() {
  String cmd = readFromController();
  handleCommand(cmd);
  
  delay(100);
}

void handleCommand(String cmd) {
  if (cmd == "test") {
    controller->print("test");
  }
  else if (cmd == SET_IP_ADDRESS) {
    approve(cmd);
    String newIp = readFromController();
    int state = setIpAddress(newIp);
    notifyController(state, cmd, getIpAddress());
  }
  else if (cmd == GET_IP_ADDRESS) {
    String ipAddress = getIpAddress();
    sendToController(ipAddress);
  }
  else if (cmd == SET_SSID) {
    approve(cmd);
    delay(100);
    String newSSID = readFromController();
    int state = setSSID(newSSID);
    notifyController(state, cmd, getSSID());
  }
  else if (cmd == GET_SSID) {
    String ssid = getSSID();
    sendToController(ssid);
  }
  else if (cmd == GET_LOCAL_SSID) {
    String ssid = getLocalSSID();    
    sendToController(ssid);
  }
  else if (cmd == SET_PASSWORD) {
    approve(cmd);
    String newPassword = readFromController();
    int state = setPassword(newPassword);
    notifyController(state, cmd, getPassword());
  }
  else if (cmd == GET_PASSWORD) {
    String password = getPassword();
    sendToController(password);
  }
  else if (cmd == CONNECT_TO_WIFI) {
    approve(cmd);
    int state = connectToHotspot();
    sendToController(getIpAddress());
    notifyController(state, cmd, getIpAddress());
  }
  else if (cmd == WIFI_SESSION) {
    approve(cmd);
    notifyController(STATE_OK, "WIFI_SESSION", getIpAddress());
    wifiSession();
  }
  else {
    controller->print("Unknown command: " + cmd);
  }
}

void wifiSession() { 
  while(1) {     
    WiFiClient client = wifiServer.available();
    String wifiCmd = "";    
    if (client) {
      while (client.connected()) {
        while (client.available() > 0) {
          char c = client.read();
          wifiCmd += c;        
          client.write(c);
        }
        if (wifiCmd == "exit") {
          notifyController(STATE_OK, "WIFI_SESSION", "stoped");
          client.stop();
          return;
        }
  
        delay(10);            
      }      
      sendToController(wifiCmd);
    }
    client.stop();
  }
}

void notifyController(int state, String cmd, String payload) {
  state == STATE_OK
  ? sendToController(cmd + " " + payload)
  : reportError(cmd);
}

void reportError(String cmd) {
  sendToController("Error when " + cmd);
}

void approve(String cmd) {
  sendToController(cmd + "_OK\n");
}

void sendToController(String data) {
  controller->print(data);
}

String readFromController() {
  String data = controller->readString();
  while (data[0] != '*') {
    data = controller->readString();
  }
  return data.substring(1, data.length());
}

int setSSID(String newSSID) {
  ssid = newSSID;
  return STATE_OK;
}

String getSSID() {
  return ssid;
}

String getLocalSSID() {
  return WiFi.SSID();
}

int setPassword(String newPassword) {
  password = newPassword;
  return STATE_OK;
}

String getPassword() {
  return password;
}

int setIpAddress(String newIp) {
  WiFi.config(ip, gateway, subnet);
  return STATE_OK;
}

String getIpAddress() {
  return WiFi.localIP().toString();
}

int connectToHotspot() {
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    sendToController("Connection to " + ssid);
    controller->flush();
  }
  sendToController("Connected to: " + ssid);
  return STATE_OK;
}

