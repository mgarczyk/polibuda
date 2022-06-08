# bibloteki
import socket
import glob
# config
import config


class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port
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
        # dane o logowaniu
        while True:
            self.login_client = self.conn.recv(1024).decode("utf-8")
            self.pwd_client = self.conn.recv(1024).decode("utf-8")
            print(f"[RECV] Login: {self.login_client}")
            print(f"[RECV] Passw: {self.pwd_client}")
            # sprawdzenie czy isnieje w naszej bazie dane tam muszą być w postaci login hasło (pomiędzy spacja)
            self.login_code = 401
            for line in open("dane.txt", "r").readlines():
                login_info = line.split()  # nazwa i hasło oddzielamy w pliku spacjami
                if login_info[0] == self.login_client and login_info[1] == self.pwd_client:
                    print( f"Użytkownik {self.login_client}, został zalogowany.")
                    self.login_code = 200
            # odsyłamy czy mu się udało
            if self.login_code == 200:
                self.conn.sendall(bytes('200', 'UTF-8'))
                break
            else:
                    self.conn.sendall(bytes('401', 'UTF-8')) # Wysłyamy kod 401 - hasło nieprawidłowe



if __name__ == '__main__':
   while True:
       host, port = config.config()
       try:
            Server = Server(host, port)
       except OSError:
           print("[ERR] Żądany adres jest nieprawidłowy w tym kontekście, spróbuj ponownie")


