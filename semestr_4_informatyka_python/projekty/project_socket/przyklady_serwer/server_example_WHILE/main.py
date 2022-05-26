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
i=1
while True:
    data = clientsocket.recv(
        1024).decode()  ##recv blokuje do czasu az: pojawi sie chociaz jeden bajt albo soket z 2 konca sie zamknie
    print('no.' + str(i) + ' ' + data)
    i+=1
    if(not data):
        print('breaking')
        break
print('end')

