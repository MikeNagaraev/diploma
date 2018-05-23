import socket               
from constants import *
import os
import re

BUFFER_SIZE=1024

def send_data(data):
    wifi_module.send(str(data + STOP_SYMBOL).encode('utf-8'))

def get_data():
    return wifi_module.recv(BUFFER_SIZE).decode('utf-8')

def validate_command(cmd):
    return True

def execute(cmd):
    if cmd == "exit":
        wifi_module.close()
        os._exit(1)
    else:
        send_data(cmd)
        print(get_data())



is_valid_address = False

REGULAR_IP = '^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$'
regex = re.compile(REGULAR_IP)


while (is_valid_address == False):
    addr = input("\nInput host addres: ")
    if (regex.match(addr)):
        is_valid_address = True
        HOST = addr


wifi_module = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
wifi_module.connect((HOST, PORT))


while True:
    try:
        cmd = input("Type command: ")
        if validate_command(cmd):
            execute(cmd)
    except KeyboardInterrupt:
        print("KeyboardInterrupt was handled")
        wifi_module.close()
        os._exit(1)
    except socket.error as e:
        print("WiFi session was stoped")
        wifi_module.close()
        os._exit(1)
