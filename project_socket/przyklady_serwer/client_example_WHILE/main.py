import socket
import time
s = socket.socket()
host = "127.0.0.1"
port =9999
s.connect((host,port))## polacz sie z serwerem

i=1
while i<4:
    s.send(str(i).encode())
    i+=1
    if(i==2):
        s.send(str('').encode())


s.close()
