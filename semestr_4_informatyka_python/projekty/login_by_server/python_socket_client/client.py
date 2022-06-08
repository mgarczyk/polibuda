
import socket
import os.path
from os import path
from PIL import Image
import glob
from pathlib import Path
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
            except TimeoutError or ConnectionRefusedError:
                print("[ERR] Próba połączenia nie powiodła się, ponieważ połączona strona nie odpowiedziała poprawnie po ustalonym okresie czasu lub utworzone połączenie nie powiodło się, ponieważ połączony host nie odpowiedział")



    def authorization(self):
        while True:  # autoryzacja
            self.input_password()
            self.C_SOC.sendall(bytes(self.login, 'UTF-8'))
            self.C_SOC.sendall(bytes(self.pwd, 'UTF-8'))
            self.code = self.C_SOC.recv(1024)
            self.code = self.code.decode("utf-8")
            if self.code == '401':
                print("[ERR - 401] Podano błędne hasło lub nie ma takiego użytkownika spróbuj ponownie.")
            elif self.code == '200':
                print(f"Uzytkownik {self.login}, został zalogowany do serwera.")
                # jeżeli nie istnieje to tworzymy folder na dane userów
                if not path.exists('users_files'):
                    os.mkdir('users_files')
                # jeżeli nie istnieje to tworzymy folder danego aktualnie zalogowanego usera
                if not path.exists(f'users_files/{self.login}'):
                    os.mkdir(f'users_files/{self.login}')
                self.what_user_want()  # tutaj podpunkt 2

                break


    def input_password(self):  # użytkownik podaje hasło
        while True:
            try:
                self.login = str(input("[INFO] Podaj login:"
                                   "\n"))
                self.pwd = str(input("[INFO] Podaj hasło:"
                            "\n"))
                break
            except ValueError:
                print("[ERR] Błąd, podaj ponownie")

    def what_user_want(self):
        while True:
            while True:
                try:
                    choose = str(input("Co chcesz zrobić?"
                                       "\nzapisz tekst - /store_text"
                                       "\nzapisz obrazek  - /store_image"
                                       "\npokaż zawartość folderu - /show_files"
                                       "\nodzytaj plik - /inspect_file"
                                       "\nwyloguj - /logout"
                                       "\nzakończ - /quit"
                                       "\n"))
                    break
                except ValueError:
                    print("Błędny typ danych, spróbij ponownoe")
            if choose == '/store_text':
                self.store_text()
            elif choose == '/store_image':
                self.store_image()
            elif choose == '/show_files':
                self.show_files()
            elif choose == '/inspect_file':
                while True:
                    try:
                        self.create_file_name = str(input("\nPodaj nazwę pliku, wraz z rozszerzeniem: "))
                        break
                    except ValueError:
                        print("Podano zły typ danych.")
                self.inspect_file()
            elif choose == '/logout':
                return
            elif choose == '/quit':
                Client.__del__()
                quit()
            else:
                print("Błędne dane, spróbij ponownie")

    def store_text(self):
        while True:
            try:
                filename = str(input("Podaj nazwe pliku: "))
                data = str(input("Podaj zawartość do zapisania w pliku: "))
                break
            except  ValueError:
                print("Błędny typ danych")

        with open(f'users_files/{self.login}/{filename}.txt', 'w') as f:
            f.write(data)
            print(f"Plik {filename}.txt, został zapisany w katalogu użytkownika {self.login}")

    def store_image(self):

        while True:
            try:
                path_to_image = str(input("Podaj ścieżkę, do obrazka: "))
                filename = os.path.basename(path_to_image)  # nazwa będzie ta sama co porzednia
                break
            except ValueError:
                print("Błędny ty danych lub brak folderu users_files")
        try:
            picture = Image.open(path_to_image)
            picture = picture.save(f'users_files/{self.login}/{filename}')
            print(f"Plik {filename}, został zapisany w katalogu użytkownika {self.login}")
        except FileNotFoundError:
            print("Brak takiej ścieżki, spróbuj ponownie.")

    def show_files(self):
        print(f"Zawartość katalogu należącego do użytkownika {self.login}: \n")
        print("\n", glob.glob(f"users_files/{self.login}/*"), "\n")


    def inspect_file(self):
        ext = Path(self.create_file_name).suffix
        if ext == '.txt':
            with open(f'users_files/{self.login}/{self.create_file_name}', 'r') as f:
                print(f"Zawartość pliku {self.create_file_name}: ", f.read())
        elif ext == '.png':
            try:
                img = Image.open(f'users_files/{self.login}/{self.create_file_name}')
                img.show()

            except FileNotFoundError:
                print("Nie znaleziono takiego pliku spróbuj ponownie.")


    def __del__(self):
        print(f"[END] Zakończ połączenie dla {self.host}, {self.port}")


if __name__ == '__main__':
    host, port = config.config()
    while True:
        while True:
            Client = Client_socket(host, port)
            Client.__del__()
