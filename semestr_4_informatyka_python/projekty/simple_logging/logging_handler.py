# This is a sample Python script.
import hashlib
import os
from PIL import Image
import glob
from pathlib import Path
import matplotlib.pyplot as plt
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.



def register():
    # login
    while True:
        try:
            username = str(input("Podaj login: "))
            for line in open("dane.txt","r").readlines():
                login_info = line.split() # nazwa i hasło oddzielamy w pliku spacjami
                if login_info[0] == username:
                    raise ValueError # sytułacja w której podany login jest taki sam jak już istniejnący
            break
        except ValueError:
            print("Taki login już istnieje, albo podano błędny typ danych spróbuj ponownie.")
    # hasło
    while True:
        try:
            password = str(input("Podaj hasło: "))
            password_hash = hashlib.sha256(password.encode()).hexdigest()
            break
        except ValueError:
            print("Podano nierawidłowy typ danych.")
    # zapis
    with open('dane.txt', "a") as data:
        data.write(username)
        data.write(" ")
        data.write(password_hash + '\n')

    print(f"Użytkowniku {username}, udało Ci się zarejestrować, zaloguj się by uzyskać dostęp do funkcjonalności.")
    os.mkdir(f'users_files/{username}')



def login():

    while True:
        try:
            username = str(input("Podaj nazwe użytkownika: "))
            break
        except ValueError:
            print("Podano nierawidłowy typ danych.")

    while True:
        try:
            password = str(input("Podaj hasło: "))
            password_hash = hashlib.sha256(password.encode()).hexdigest()
            break
        except ValueError:
            print("Podano nierawidłowy typ danych.")

    for line in open("dane.txt","r").readlines():
        login_info = line.split() # nazwa i hasło oddzielamy w pliku spacjami
        if login_info[0] == username and login_info[1] == password_hash:
            print(f"Użytkownik {username}, został zalogowany.") # TODO tu reszta funkcjonalności się odpala z innych funkcji
            what_user_want(username)
            return

    print("Podano błędne dane zarejestruj się lub spróbuj ponownie.")


def what_user_want(username):
    while True:
        while True:
            try:
                choose = str(input("Co chcesz zrobić?"
                                   "\nzapisz tekst - /store_text"
                                   "\nzapisz obrazek  - /store_image"
                                   "\npokaż zawartość folderu - /show_files"
                                   "\nodzytaj plik - /inspect_file"
                                   "\nzakończ - /exit"
                                   "\n"))
                break
            except ValueError:
                print("Błędny typ danych, spróbij ponownoe")
        if choose == '/store_text':
            store_text(username)
        elif choose == '/store_image':
            store_image(username)
        elif choose == '/show_files':
            show_files(username)
        elif choose == '/inspect_file':
            while True:
                try:
                    filename = str(input("\nPodaj nazwę pliku, wraz z rozszerzeniem: "))
                    break
                except ValueError:
                    print("Podano zły typ danych.")
            inspect_file(username, filename)
        elif choose == '/exit':
            return
        else:
            print("Błędne dane, spróbij ponownie")


def store_text(username):
   while True:
       try:
           filename = str(input("Podaj nazwe pliku: "))
           data = str(input("Podaj zawartość do zapisania w pliku: "))
           break
       except  ValueError:
           print("Błędny typ danych")

   with open(f'users_files/{username}/{filename}.txt', 'w') as f:
        f.write(data)
        print(f"Plik {filename}.txt , został zapisany w katalogu użytkownika {username}")


def store_image(username):
    while True:
        try:
            filename = str(input("Podaj jak plik ma się nazywać po zapisaniu: "))
            break
        except  ValueError:
            print("Błędny typ danych")
    while True:
        try:
            path_to_image = str(input("Podaj ścieżkę, do obrazka: "))
            break
        except ValueError:
            print("Błędny ty danych lub brak folderu users_files")
    try:
        picture = Image.open(path_to_image)
        picture = picture.save(f'users_files/{username}/{filename}.png')
        print(f"Plik {filename}.png , został zapisany w katalogu użytkownika {username}")
    except FileNotFoundError:
        print("Brak takiej ścieżki, spróbuj ponownie.")





def show_files(username):
    print(f"Zawartość katalogu należącego do użytkownika {username}: \n")
    print(glob.glob(f"users_files/{username}/*"))

def inspect_file(username, filename):
    ext = Path(filename).suffix
    if ext == '.txt':
        with open(f'users_files/{username}/{filename}', 'r') as f:
            print(f"Zawartość pliku {filename}: ", f.read())
    elif ext == '.png':
        try:
            img = Image.open(f'users_files/{username}/{filename}')
            img.show()
        except FileNotFoundError:
            print("Nie znaleziono takiego pliku spróbuj ponownie.")




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # jeżeli plik nie istnieje tworzymy go
    fle = Path('dane.txt')
    fle.touch(exist_ok=True)
    # w pliku coś powinno być żeby uniknąć błędu, zatem jeżeli jest pusty to dopiszemy coś
    if os.stat("dane.txt").st_size == 0:
        with open('dane.txt', "a") as data:
            data.write('test')
            data.write(" ")
            data.write('lorem_ipsum' + '\n')
    # sprawdzenie czy istnieje folder na dane
    if not os.path.isdir('users_files'):
        os.mkdir('users_files')

    # główna pętla
    while True:
        while True:
            try:
                choose = str(input("Co chcesz zrobić?"
                                   "\nlogin - /login"
                                   "\nrejestracja - /register"
                                   "\nzakończ - /exit"
                                   "\n"))
                break
            except ValueError:
                print("Błędny typ danych, spróbij ponownoe")
        if choose in ['/register', '/register ']:
            register()
        elif choose in ['/login', '/login ']:
            login()
        elif choose in ['/exit', '/exit ']:
            quit()
        else:
            print("Błędne dane, spróbij ponownie")

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
