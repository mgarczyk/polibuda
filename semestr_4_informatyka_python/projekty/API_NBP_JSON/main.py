# This is a sample Python script.
import requests
from datetime import datetime
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def get_currency(): # pobieranie waluty od użytkownika
    # obsluga wyjatku zly typ danych przy podawaniu waluty
    while True:
        try:
            currency = str(input("Obsługiwane waluty:"          
                                     "\npolecenie - nazwa"
                                     "\nusd - dolar amerykański"
                                     "\neur - euro"
                                     "\nchf - frank szwajacarski"
                                     "\nPodaj walutę:  "))
            if currency in ["usd", "eur", "chf"]:  # nasz drugi warunek waluta musi być wśród obsługiweanych
                break
            else:
                raise ValueError # jak nie jest to uznajemy to za ValueError (user coś popsuł)
        except ValueError:
            print("Podano coś co nie jest łańcuchem znaków albo waluta nie jest obsługiwana. Spróbuj ponownie")
    return currency


def get_date(): # pobieranie daty od usera
    format = "%Y-%m-%d"
    # sprawdzimy czy podana przez usera data jest zgodna z formatem
    check = False
    while check is False:  # dopóki tu jest fałsz - podano zły format daty
        print("Foramt daty to: RRRR-MM-DD (rok-miesiąc-dzień)")
        try:
            date = str(input("Podaj datę: "))
            check = bool(datetime.strptime(date, format))   # sprawdzenie foramtu za pomocą gotowej funkcji z wykorzystaniem bibloteki datetime, jak jest ok check = True i koniec pętli
        except ValueError:                                  # jak nie zgadza się z formatem to ValueError i zabawa zaczyna się od nowa
            check = False
    return date


def days(): # TODO narazie się nie przyda, ale do dni wstecz może być przydatne
    while True:
        try:
            days = int(input("Podaj z ilu dni wstecz dane mają zostać zapisane: "))
            if days <= 0: # nasz drugi warunek, liczba dni to wartość dodatnia
                raise ValueError # ta sama sztuczka co wcześniej user coś zepsuł, ValueError
            break
        except ValueError:
            print("Ilość dni powinna być DODATNIĄ liczbą całkowitą.")
    return days


def get_from_NBP_to_JSON(): # pobieranie danych z NBP do naszego pliku
    # pobranie informacji o walucie
    currency = get_currency()  # pobieramy walutę ITP...
    print("Wybrana waluta: ", currency)
    # wybór czy jeden konkretny dzeń czy przedział
    while True:
        try:
            choose_date = str(input("Czy chcesz uzyskać dane z jednego konkretnego dnia, czy z przedziału dni?"
                                    "\nPolecenie: /day - jedna konkretna data"
                                    "\nPolecenie /interval - przedział dni"
                                    "\nPodaj polecenie: "))
            if choose_date in ["/day", "/interval"]: # sprawdzamy czy user podał dozwolone polecenie
                break
            else:
                raise ValueError
        except ValueError:
            print("Spróbuj ponownie, podaj łańcuch znaków")
    #obsługa poleceń
    if choose_date == "/day":
        date = get_date()
        print("Wybrana data: ", date)
        resp = requests.get(f"http://api.nbp.pl/api/exchangerates/rates/a/{currency}/{date}/?format=JSON") # pobranie danych o danej walucie z konkretnego dnia
        file_day = open("day.txt", "wb") # tu zapiszemy dane
        file_day.write(resp.content) # zapis danych do pliku JSON (Stworzy się w tym folderze co program)
        print("Dane zostały zapisane do pliku: ", file_day.name) # file.name poda scieżkę do pliku
        file_day.close()
    elif choose_date == "/interval":
        date_1 = get_date()
        date_2 = get_date()
        print("Wybrany przedział czasu: ", date_1, " ", date_2)
        resp = requests.get(f"http://api.nbp.pl/api/exchangerates/rates/a/{currency}/{date_1}/{date_2}/?format=JSON") # pobranie danych o danej walucie z przedziału
        file_interval = open("interval.txt", "wb")
        file_interval.write(resp.content)
        print("Dane zostały zapisane do pliku: ", file_interval.name)
        file_interval.close()

    else:
        print("Err")

def read_from_JSON():
    print("TODP read JSON")


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    while True:
        #WYBRANIE CO UŻYTKONICK CHCE ROBIC
        print("Możliwe działania:"
             "\n/rd - odczyt z pliku"
             "\n/get - pobierz informację"
             "\n/end  - zakończ program")
        while True:
            try:
                choose_wisely = str(input("Podaj polecenie: ")) #sprawdzamy czy użytkownik poda dane typu string
                break                                           #jak tak to ok
            except ValueError:                                  #jak nie obsługujemy wyjątek
                print("Błąd oczekiwno łańcucha znaków. Spróbuj ponownie.")
        #OBSULUGA POLECEN
        if choose_wisely == "/rd":
            read_from_JSON()
        elif choose_wisely == "/get":
            get_from_NBP_to_JSON()
        elif choose_wisely == "/end":
            print("Koniec.")
            print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
            break
        else:
            print("Podano błędne polecenie, spróbuj pnownie")

        print("--------------------------------------------------------------")




# See PyCharm help at https://www.jetbrains.com/help/pycharm/
