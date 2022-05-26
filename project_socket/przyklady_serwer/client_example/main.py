import socket
import time
s = socket.socket()
host = "127.0.0.1"
port =9999
s.connect((host,port))## polacz sie z serwerem


start=input("start>")## po inpucie wysylamy 4 wiadomosci
s.send('raz'.encode())
s.send('dwa'.encode())
#time.sleep(0.1)## !!!!!!!! SPRAWDZ DZIALANIE Z I BEZ TEJ LINIJKI
s.send('trzy'.encode())
s.send(''.encode())
stop=input("stop>")## zatrzymujemy program do inputa
s.close()
