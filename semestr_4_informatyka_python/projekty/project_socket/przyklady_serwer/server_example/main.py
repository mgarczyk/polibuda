import socket



serversocket=socket.socket()
host="127.0.0.1"
port=9999
print(host)
print(port)
serversocket.bind((host,port))##przypisuje ip:port do gniazda


serversocket.listen(5)## ustawienie w stan oczekiwania na polaczenia, w argumencie max liczba polaczen ustawiajacych sie w kolejce do socketa
print('nasluchuje')
(clientsocket,address)=serversocket.accept()#akceptowanie przychodzacego polaczenia
print("polaczenie od : ", address)

data=clientsocket.recv(1024).decode()
print('no.1 ' + data)
data=clientsocket.recv(1024).decode()##recv blokuje do czasu az pojawi sie chociaz jeden bajt albo soket z 2 konca sie zamknie
print('no.2 ' + data)
data=clientsocket.recv(1024).decode()
print('no.3 ' + data)
data=clientsocket.recv(1024).decode()
print('no.4 ' + data)
data=clientsocket.recv(1024).decode()
print('no.5 ' + data)