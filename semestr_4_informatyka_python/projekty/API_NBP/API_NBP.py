# This is a sample Python script.
import requests
from datetime import datetime
import json
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.




class API_NBP_JSON:

    def __init__(self): # pobieranie danych z NBP do naszego pliku
        # pobranie informacji o walucie
        currency = self.get_currency()  # pobieramy walutę ITP...
        print("Wybrana waluta: ", currency)
        # wybór czy jeden konkretny dzeń czy przedział
        while True:
            try:
                choose_date = str(input("Czy chcesz uzyskać dane z jednego konkretnego dnia, czy z przedziału dni?"
                                        "\nPolecenie: /day - jedna konkretna data"
                                        "\nPolecenie /interval - przedział dni (jako pierwszą datę podaj początek przedziału, a jako drugą jego koniec"
                                        "\nPodaj polecenie: "))
                if choose_date in ["/day", "/interval"]: # sprawdzamy czy user podał dozwolone polecenie
                    break
                else:
                    raise ValueError
            except ValueError:
                print("Spróbuj ponownie, podaj łańcuch znaków")
        #obsługa poleceń
        if choose_date == "/day":
            date = self.get_date()
            print("Wybrana data: ", date)
            self.save_data_to_JSON_day(currency, date)  #funkcja zapisze dane z danego dnia do pliku
            try:
                self.read_data_from_JSON_day(currency, date) #odczyt danych za pomocą funkcji
            except json.decoder.JSONDecodeError:        #gdyby user podał datę np. z przyszłośći to wyskoczy error, który obsłuigujemy
                print("Podaną złą datę, być może z przyszłośći.")

        elif choose_date == "/interval":
            date_1 = self.get_date()
            date_2 = self.get_date()
            print("Wybrany przedział czasu: ", date_1, " ", date_2)
            self.save_data_to_JSON_interval(currency, date_1, date_2)
            try:
                self.read_data_from_JSON_interval(currency, date_1, date_2)  #odczyt danych za pomocą funkcji
            except json.decoder.JSONDecodeError:   #gdyby user podał datę np. z przyszłośći to wyskoczy  error, który obsłuigujemy
                print("Podaną zły zakres dat, być może z przyszłośći, lub w złej kolejności, najpierw podajemy datę wcześnijszą potem późniejszą.")


        else:
            print("Err")

    def get_currency(self): # pobieranie waluty od użytkownika
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


    def get_date(self): # pobieranie daty od usera
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


    def days(self): # TODO narazie się nie przyda, ale do dni wstecz może być przydatne
        while True:
            try:
                days = int(input("Podaj z ilu dni wstecz dane mają zostać zapisane: "))
                if days <= 0: # nasz drugi warunek, liczba dni to wartość dodatnia
                    raise ValueError # ta sama sztuczka co wcześniej user coś zepsuł, ValueError
                break
            except ValueError:
                print("Ilość dni powinna być DODATNIĄ liczbą całkowitą.")
        return days


    def save_data_to_JSON_day(self,currency, date):  # funckja zapisuje dane z jednego dnia do pliku
        resp = requests.get(f"http://api.nbp.pl/api/exchangerates/rates/a/{currency}/{date}/?format=JSON") # pobranie danych o danej walucie z konkretnego dnia
        file_day = open("day.json", "wb") # otwarcie pliku w trybie do odczytu
        file_day.write(resp.content) # zapis danych do pliku JSON (Stworzy się w tym folderze co program)
        print("Dane zostały zapisane do pliku: ", file_day.name) # file.name poda scieżkę do pliku
        file_day.close()      # zamknięcie plik, żeby zmienić tryb


    def save_data_to_JSON_interval(self,currency, date_1, date_2): #funkcja zapisuje dane z przedziału czsu do pliku
        resp = requests.get(f"http://api.nbp.pl/api/exchangerates/rates/a/{currency}/{date_1}/{date_2}/?format=JSON") # pobranie danych o danej walucie z przedziału
        file_interval = open("interval.json", "wb")
        file_interval.write(resp.content)
        print("Dane zostały zapisane do pliku: ", file_interval.name)
        file_interval.close()


    def read_data_from_JSON_day(self,currency, date):
        file_day = open("day.json", "rb") # zmiana  trybu na do odczytu
        data_load = json.load(file_day)
        currency_value = data_load["rates"][0]["mid"]  # pobieramy dane z pola rates naszego słownika, które jest listą co ciekawe jedno elemntową, a jedynym elementem na tej liście jest kolejny słownik którego pole mid jest naszym celem
        mid_value = data_load["currency"] # pełna nazwa waluty
        print(f"W dniu {date} wartość waluty {mid_value} wynosiła średnio: {currency_value}")


    def read_data_from_JSON_interval(self,currency, date_1, date_2):
        file_interval = open("interval.json", "rb") # zmiana  trybu na do odczytu
        data_load = json.load(file_interval)
        currency_name = data_load["currency"]
        for R in data_load["rates"]:    # zauważamy że pole rates naszego słownika zawiera listę słowników z danymi kolejnych notowań, zatem R jest właśnie jednym z tych n słowników
            effective_date = R["effectiveDate"]  #dalej działamy na R jak na standardowym słowniku
            mid_value = R["mid"]
            print(f"Średni kurs waluty {currency_name} w dniu {effective_date} wynosił {mid_value}")




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    while True:
        #WYBRANIE CO UŻYTKONICK CHCE ROBIC
        print("Możliwe działania:"
             "\n/get - pobierz  i wyświetl informację"
             "\n/end  - zakończ program")
        while True:
            try:
                choose_wisely = str(input("Podaj polecenie: ")) #sprawdzamy czy użytkownik poda dane typu string
                break                                           #jak tak to ok
            except ValueError:                                  #jak nie obsługujemy wyjątek
                print("Błąd oczekiwno łańcucha znaków. Spróbuj ponownie.")
        #OBSULUGA POLECEN
        if choose_wisely == "/get":
            NBP = API_NBP_JSON()
        elif choose_wisely == "/end":
            print("Koniec.")
            print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
            break
        else:
            print("Podano błędne polecenie, spróbuj pnownie")

        print("--------------------------------------------------------------")




# See PyCharm help at https://www.jetbrains.com/help/pycharm/
