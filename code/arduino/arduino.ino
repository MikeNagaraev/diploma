#include <SoftwareSerial.h>

const int rx = 10;
const int tx = 11;
const int speed = 9600;

const String HELP = "HELP";
const String MOVEMENT = "MOVEMENT";
const String SENSORS = "SENSORS";
const String WIFI_SESSION = "WIFI_SESSION";

int RIGHT_UP = 7;
int RIGHT_DOWN = 6;
int LEFT_UP = 5;
int LEFT_DOWN = 4;
bool wifiSession = false;

SoftwareSerial* wifiModule = new SoftwareSerial(rx, tx);

void setup() {
  Serial.begin(speed);
  wifiModule->begin(speed);
  wifiModule->listen();
  pinMode (LEFT_DOWN, OUTPUT);
  pinMode (LEFT_UP, OUTPUT);
  pinMode (RIGHT_DOWN, OUTPUT);
  pinMode (RIGHT_UP, OUTPUT);
}

void loop() {
  String cmd = Serial.readString();
  
  cmd = cmd.substring(0, cmd.length() - 2);  
  if (cmd == WIFI_SESSION) {
    wifiSession = true;
  }
  if (cmd.length() > 0) {
    sendToWifiModule(cmd);
    Serial.println("From serial: " + cmd);
  }
  if (wifiModule->available()) {
    String cmd = wifiModule->readString();
    Serial.println("From wifiModule: " + cmd);

    if (wifiSession) {
      Serial.println("wifi session enabled \n");
      startWifiSession();  
    }    
  }
  
  delay(100);
}

void startWifiSession() {
  while(wifiSession) {
    if (wifiModule->available()) {
      String cmd = wifiModule->readString();
      Serial.println("From wifiModule: " + cmd);
  
      handleCmd(cmd);
    }
  }
}


void sendToWifiModule(String data) {
  wifiModule->print("*" + data);
}

void handleCmd(String cmd) {
  if (cmd == "HELP") {
    sendToWifiModule("- " + MOVEMENT + "\n- " + SENSORS);
  }
  else if (cmd == MOVEMENT) {
    movementMenu();
    sendToWifiModule(MOVEMENT + " exit");
  }
  else if (cmd == SENSORS) {

  }
  else if (cmd == "stop") {
    wifiSession = false;
    sendToWifiModule("WiFi session stopped");
  }
  else {
    sendToWifiModule("Unknown command: " + cmd);
  }
}

void movementMenu() {
  sendToWifiModule("1.Forward\n2.Back\n3.Left\n4.Right\n5.Stop\n0.Exit");
  while (1) {
    if (wifiModule->available()) {
      String cmd = wifiModule->readString();
      if (cmd == "1") {
        moveForward();
      }
      else if (cmd == "2") {
        moveBack();
      }
      else if (cmd == "3") {
        moveLeft();
      }
      else if (cmd == "4") {
        moveRight();
      }
      else if (cmd == "5") {
        moveStop();
      }
      else if (cmd == "0") {
        return;
      }
      sendToWifiModule(cmd);
    }
  }
}

void moveForward() {
  digitalWrite (RIGHT_DOWN, LOW);
  digitalWrite (RIGHT_UP, HIGH);
  digitalWrite (LEFT_UP, HIGH);
  digitalWrite (LEFT_DOWN, LOW);
}

void moveBack() {
  digitalWrite (RIGHT_DOWN, HIGH);
  digitalWrite (RIGHT_UP, LOW);
  digitalWrite (LEFT_UP, LOW);
  digitalWrite (LEFT_DOWN, HIGH);
}

void moveLeft() {
  digitalWrite (RIGHT_DOWN, LOW);
  digitalWrite (RIGHT_UP, HIGH);
  digitalWrite (LEFT_UP, LOW);
  digitalWrite (LEFT_DOWN, LOW);
}

void moveRight() {
  digitalWrite (RIGHT_DOWN, LOW);
  digitalWrite (RIGHT_UP, LOW);
  digitalWrite (LEFT_UP, HIGH);
  digitalWrite (LEFT_DOWN, LOW);
}

void moveStop() {
  digitalWrite (RIGHT_DOWN, LOW);
  digitalWrite (RIGHT_UP, LOW);
  digitalWrite (LEFT_UP, LOW);
  digitalWrite (LEFT_DOWN, LOW);
}

