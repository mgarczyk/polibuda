# bibloteki
import socket
import glob
# config
import config


class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.hash = "c406b7ea178297c7d15d64979baeb6c456f36b5808ef8749665bfce89467684c"
        print(f"Tworzę socket {self.host}, na porcie {self.port}")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as self.S_SOC:  # używamy żeby nie musieć używać s.close() za każdym razem po przesłaniu danych, AF_inet, host jako adres IPv4, STOCK_STERAM, przesy łamy za pomocą TCP
            self.S_SOC.bind((self.host, self.port))  # podwójny nawias, bo to jako krotka musi być
            while True:  # tutaj czekamy i wysyłamy dane
                print("[LISTEN]")
                self.S_SOC.listen(5)  # oczeiwanie na połączenie
                self.conn, self.addr = self.S_SOC.accept()  # nawiązanie połączenia z klientem
                print(f"[CONN]:  {self.addr}")
                with self.conn:
                    self.check_pwd()


    def check_pwd(self):  # jako pierwsze otrzymamy zahaszowane hasło, należy je odkodować z bitów, odhaszować i porównać z prawidłowym
        self.pwd_client = self.conn.recv(1024)
        print(f"[RECV] Hash: {self.pwd_client!r}")
        self.pwd_client = self.pwd_client.decode("utf-8")  # konwertujemy z bajtów na string
        if self.pwd_client == self.hash:
            self.conn.sendall(bytes('200', 'UTF-8'))
            self.send_list_of_files()
            self.handle_file()
        else:
                self.conn.sendall(bytes('401', 'UTF-8')) # Wysłyamy kod 401 - hasło nieprawidłowe


    def send_list_of_files(self):
        self.list_of_files = ""
        for name in glob.glob('files/*'):
            self.list_of_files += name
            self.list_of_files += " "
        self.conn.sendall(bytes(self.list_of_files, 'UTF-8'))

    def handle_file(self):
        self.filename_coded = self.conn.recv(1024)  # klient wysyła nazwę pliku
        self.filename = self.filename_coded.decode("utf-8")
        print(f"[RECV] Filename:  {self.filename!r}")
        self.is_file_exist()
        self.if_file_exist_send()

    def is_file_exist(self):
        self.check_filename = False  # sprawdzamy czy taki plik jest zapisany na serwerze
        for name in glob.glob('files/*'):
            if name == 'files\\' + self.filename:
                self.check_filename = True

    def if_file_exist_send(self):
        if self.check_filename == True:
            self.conn.sendall(bytes('200', 'UTF-8'))
            # samo wysyłanie pliku
            with open(f'files/{self.filename}', "rb") as f:  # plik otwieramy w trybie odczytu bajtów
               data_chunk = f.read(1024) # dane dzielimy na 1kB fragmenty
               while data_chunk:
                   self.conn.send(data_chunk)
                   data_chunk = f.read(1024)
               print(f"[SEND] Wysłano plik {self.filename}")
               self.conn.close()
            f.close()

        else:
            self.conn.sendall(bytes('404', 'UTF-8')) # Wysłyamy kod 404 - plik nie istnieje

if __name__ == '__main__':
   while True:
       host, port = config.config()
       try:
            Server = Server(host, port)
       except OSError:
           print("[ERR] Żądany adres jest nieprawidłowy w tym kontekście, spróbuj ponownie")


