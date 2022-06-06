# This is a sample Python script.
import hashlib
import os
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
           what_user_want()
           return

    print("Podano błędne dane zarejestruj się lub spróbuj ponownie.")


def what_user_want():
    while True:
        while True:
            try:
                choose = str(input("Co chcesz zrobić?"
                                   "\nzapisz tekst - /store_text"
                                   "\nzapisz obrazek  - /store_imager"
                                   "\npokaż zawartość folderu - /show_files"
                                   "\nodzytaj plik - /inspect_file"
                                   "\nzakończ - /exit"
                                   "\n"))
                break
            except ValueError:
                print("Błędny typ danych, spróbij ponownoe")
        if choose == '/store_text':
            store_text()
        elif choose == '/store_image':
            store_image()
        elif choose == '/show_files':
            show_files()
        elif choose == '/inspect_file':
            inspect_file(filename='sd')
        elif choose == '/exit':
            return
        else:
            print("Błędne dane, spróbij ponownie")


def store_text():
    print("store txt")

def store_image():
    print("store_image")

def show_files():
    print("show_files")

def inspect_file(filename):
    print("inspect_file", filename)



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
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
        if choose == '/register':
            register()
        elif choose == '/login':
           login()
        elif choose == '/exit':
            quit()
        else:
            print("Błędne dane, spróbij ponownie")

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
