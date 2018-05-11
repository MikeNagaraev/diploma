import socket               
 
sock = socket.socket()
 
host = "192.168.1.11" #ESP32 IP in local network
port = 80             #ESP32 Server Port    
 
sock.connect((host, port))
 
message = "Hello World"
sock.send(str(message).encode('utf-8'))
 
data = ""

while len(data) < len(message):
    data += sock.recv(1).decode('utf-8')
 
print(data)
 
sock.close()
