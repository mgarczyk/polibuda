import hashlib
import os
from PIL import Image
import glob
from pathlib import Path
import matplotlib.pyplot as plt
import shutil


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
            print("Podano nieprawidłowy typ danych.")

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
            print(f"Użytkownik {username}, został zalogowany.") 
            return True, username

    print("Podano błędne dane zarejestruj się lub spróbuj ponownie.")
    return False, username

def save_file(username):
    while True:
        try:
            src = str(input("\nPodaj źródło pliku: "))
            filename = str(input("\nPodaj jak plik ma nazywać się po zapisaniu (wraz z rozrszerzeniem): "))
            break
        except ValueError:
            print("Podano zły typ danych.")
    dst = f'users_files/{username}/{filename}'
    try:
        shutil.copy2(src, dst)
    except FileNotFoundError:
        print("Nie istnieje plik źródłowy o podanej nazwie.")

def list_files():
    print(glob.glob(f"users_files/*"))
    while True:
        try:
            username = str(input("\nPodaj nazwę użytkownika którego folder chcesz wyśiwtlić: "))
            break
        except ValueError:
            print("Podano zły typ danych.")
    print(f"Zawartość katalogu należącego do użytkownika {username}: \n")
    print(glob.glob(f"users_files/{username}/*"))

def view_files(username, filename):
    ext = Path(filename).suffix
    if ext in [".jpg", ".jpeg", ".png"]:
        try:
            img = Image.open(f'users_files/{username}/{filename}')
            img.show()
        except FileNotFoundError:
            print("Nie znaleziono takiego pliku spróbuj ponownie.")
    elif ext == '.txt':
         with open(f'users_files/{username}/{filename}', 'r') as f:
            print(f"Zawartość pliku {filename}: ", f.read())
    else:
        print("Błędne rozszerzenie.")

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
                                   "\nStwórz użytkownika - create user"
                                   "\nZobacz plik - view file"
                                   "\nZapisz plik - save file"
                                   "\nWypisz pliki - list files"
                                   "\nWyjdź - exit"
                                   "\n"))
                break
            except ValueError:
                print("Błędny typ danych, spróbij ponownoe")
        if choose in ['create user', 'create user ']:
            register()
        elif choose in ['view file', 'view file  ']:
            login_check, username = login()
            if login_check:
                while True:
                    try:
                        filename = str(input("\nPodaj nazwę pliku, wraz z rozszerzeniem: "))
                        break
                    except ValueError:
                        print("Podano zły typ danych.")
                view_files(username, filename)
            else:
                print("Błędne dane, spróbuj ponownie.")    
        elif choose in ['save file', 'save file ']:
            login_check, username = login()
            if login_check:
                save_file(username)
            else:
                print("Błędne dane, spróbuj ponownie.") 
        elif choose in ['list files', 'list files ']:
            list_files()
        elif choose in ['exit', 'exit ']:
            quit()
        else:
            print("Błędne dane, spróbuj ponownie")