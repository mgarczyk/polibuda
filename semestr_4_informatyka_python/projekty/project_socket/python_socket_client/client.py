# bibloteki
import socket
import hashlib
# pliki
import config


class Client_socket:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as self.C_SOC: # używamy żeby nie musieć używać s.close() za każdym razem po przesłaniu danych, AF_inet, host jako adres IPv4, STOCK_STERAM, przesy łamy za pomocą TCP
            try:
                self.C_SOC.connect((self.host, self.port))  # nawiązanie połączenia z serwerem (druga strona socketu)
                self.authorization()
                self.send_filename()
            except TimeoutError or ConnectionRefusedError:
                print("[ERR] Próba połączenia nie powiodła się, ponieważ połączona strona nie odpowiedziała poprawnie po ustalonym okresie czasu lub utworzone połączenie nie powiodło się, ponieważ połączony host nie odpowiedział")



    def authorization(self):
        while True:  # autoryzacja
            self.input_password()
            self.C_SOC.sendall(bytes(self.hash, 'UTF-8'))
            self.code = self.C_SOC.recv(1024)
            self.code = self.code.decode("utf-8")
            if self.code == '401':
                print("[ERR - 401] Podano błędne hasło, spróbuj ponownie.")
            elif self.code == '200':
                self.list_of_files = self.C_SOC.recv(1024)
                self.list_of_files = self.list_of_files.decode("utf-8")
                print("[INFO] Lista plików na serwerze: ", self.list_of_files)
                break


    def input_password(self):  # użytkownik podaje hasło
        while True:
            try:
                self.pwd = input("[INFO] Podaj hasło:"
                            "\n")
                break
            except ValueError:
                print("[ERR] Błąd, podaj ponownie")
        self.plaintext = self.pwd.encode()  # haszowanie
        self.d = hashlib.sha256(self.plaintext)
        self.hash = self.d.hexdigest()



    def send_filename(self):
        # pobieramy nazwe pliku
        while True:
           while True:
               try:
                   self.filename = str(input("[INFO] Podaj nazwę pliku wraz z rozszerzeniem."
                                             "\n"))
                   break
               except ValueError:
                   print("[ERR] Podano błędne dane")
           # wywyłamu
           self.C_SOC.sendall(bytes(self.filename, 'UTF-8'))  # wysyłamy nazwę pliku do serwera
           # serwer zwraca kod informacyjny 200 lub 404
           self.code = self.C_SOC.recv(1024)
           self.code = self.code.decode("utf-8")
           if self.code == '404':
                print("[ERR-404] Nie znaleziono takeigo pliku. Spróbuj ponownie.")
           elif self.code == '200':
               self.recive_file()
               print(f"[END] Zakończono pobieranie pliku {self.filename}")
               break

    def recive_file(self):
        with open(f'recived/{self.filename}', "wb") as f: # plik zapisujemy jako bajty
            recived_chunk = self.C_SOC.recv(1024)
            while recived_chunk: # pętla wykonuje się dopóki otrzymywane dane nie są puste
                f.write(recived_chunk)
                recived_chunk = self.C_SOC.recv(1024)
            self.C_SOC.close()
        f.close()

    def __del__(self):
        print(f"[END] Zakończ połączenie dla {self.host}, {self.port}")


if __name__ == '__main__':
    while True:
        host, port = config.config()
        while True:
            try:
                choose = str(input("[INFO] Czy chcesz pobrać dane z serwera? Y/N"
                                   "\n"))
                if choose not in ["Y", "N"]:
                    raise ValueError
                break
            except ValueError:
                print("Błędne dane.")
        if choose == "Y":
            Client = Client_socket(host, port)
            Client.__del__()
        else:
            print("Koniec")
            quit()