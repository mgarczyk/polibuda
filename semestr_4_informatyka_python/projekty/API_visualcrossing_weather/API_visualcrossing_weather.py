import os
import requests
from datetime import datetime
import json
import matplotlib.pyplot as plt

class weather_API():


    def __init__(self):
        self.api_key = '69P92SS4PSXYDQ9NPTYFAUVPP'
        #tworzenie folderu data zawierającego pliki z danymi
        if os.path.exists('data') and any(os.scandir('data')):         # zabezpiecznie plików przed nadpisaniem (folder istnieje i zawiera pliki)
            print("\nIstnieje folder, z danymi do wyświetlania, następnym razem użyj /disp by sprawdzić dostępne miasta")
        else:
            try:
                os.mkdir('data')   # próbujemy stworzyć ten folder, jak okaże się że z jakiegoś powodu istnieje jako pusty to zabezpieczamy przed próbą ponownego tworzenia i błędem
            except FileExistsError:
                print("")

    #POBIERANIE DANYCH Z API visualcrossing.com
    def get_data_from_API(self):
        order = input("\nWybierz czy chcesz wybrać miasto po nazwie czy współrzędnych geograficznych - polecenia:"
                      "\n/name - po nazwie miasta"
                      "\n/coords - po współrzędnych"
                      "\nPodaj polecenie: ")

        if order == "/name":
            while True:
                try:
                    city_name = str(input("Podaj nazwę miasta: "))
                    break
                except ValueError:
                    print("Podano nieprawidłową nazwę spróbuj ponownie")
            self.get_data_by_city_name(city_name)
        elif order == "/coords":
            city_name = self.translate_coordinates_to_city_name()  # nazwę miasta zanjudjemy po koordynatach
            self.get_data_by_city_name(city_name)                  # i uruchamiamy tę samą funkcję co powyżej
        else:
            print("Błędne polecenie")

    def get_data_by_city_name(self, city_name):
        start = self.get_date_from_user()
        end = self.get_date_from_user()
        resp = requests.get(f"https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/{city_name}/{start}/{end}?unitGroup=metric&include=days&key={self.api_key}&contentType=json")
        file_day = open(f"data/{city_name}.json", "wb") # otwarcie pliku w trybie do odczytu
        file_day.write(resp.content) # zapis danych do pliku JSON (Stworzy się w tym folderze co program)
        print("Dane zostały zapisane do pliku: ", file_day.name) # file.name poda scieżkę do pliku
        file_day.close()      # zamknięcie plik, żeby zmienić tryb


    #POBIERANIE DANYCH OD USERA
    def get_date_from_user(self): # pobieranie daty od usera
        format = "%Y-%m-%d"
        # sprawdzimy czy podana przez usera data jest zgodna z formatem
        check = False
        while check is False:  # dopóki tu jest fałsz - podano zły format daty
            print("Format daty to: RRRR-MM-DD (rok-miesiąc-dzień)")
            try:
                date = str(input("Podaj datę: "))
                check = bool(datetime.strptime(date, format))   # sprawdzenie foramtu za pomocą gotowej funkcji z wykorzystaniem bibloteki datetime, jak jest ok check = True i koniec pętli
            except ValueError:                                  # jak nie zgadza się z formatem to ValueError i zabawa zaczyna się od nowa
                check = False
        return date

    def get_coordinates_from_user(self):
        while True:
            print("Podaj dane z dokładnością do dwóch miejsc po przecinku: ")
            try:
                lat = round(float(input("Podaj szerokość geograficzną: ")),2)
                if lat < -90 or lat > 90:
                    raise ValueError
                break
            except:
                print("\nSzerokość geograficzna musi być w przedziale od -90 do 90 stopni")

        while True:
            try:
                lon = round(float(input("Podaj długość geograficzną: ")),2)
                if lon < -180 or lat > 180:
                    raise ValueError
                break
            except:
                print("\nSzerokość geograficzna musi być w przedziale od -180 do 180 stopni")

        print("\nPodana szerokość: ", lat,
              "\nPodana długość: ", lon,
              "\n")
        return  lat, lon

    #TLUMACZ KOORDYNATY NA NAZWE MIASTA - REALIZOWANE ZA POMOCĄ SLOWNIKA (PLIKU CSV) - https://simplemaps.com/data/world-cities (od razu konwertuję na json)
    def translate_coordinates_to_city_name(self):
        try:
            with open('csv/csvjson.json', 'r') as csv_json:
                coord_dict = json.load(csv_json)
        except FileNotFoundError:
            print("\nPlik zawierający dane z koordynatami nie istnieje. Funkcja ta nie będzie działać, spróbuj zainstalować ponownie lub użyć opcji /name")
            return 0

        #tłumacznie koordynatow
        while True:
            lat, lon = self.get_coordinates_from_user()
            for C in coord_dict:
               if C['lat'] == lat and C['lon'] == lon:  #koordynaty są odpowiednio w tych 'komórkach' słownika
                   city_name = C['city_ascii']
                   print("\nMiasto, które zostało przypisane do podanych koordynatów to: ", city_name)
                   return city_name  # zwracamy znalezione miasto
            print("\nPodano koordynaty, któych nie ma w bazie spróbuj ponownie.")

    #WYŚWIETLANIE DANYCH
    def plot_historical_temp(self):
        self.check_is_data_files_exists()              #funkcja sprawdza czy dane do ryswoania istnieją czy trzeba je pobrać
        file_name = self.choose_data_file_to_plot()    #funkcja pozwala na wybór nazwy pliku z danymi do wyświetlenia
        temperature = []
        dates = []
        name, ext = os.path.splitext(file_name)       #nazwa miasta do wykresu wyciągamy ją z nazwy pliku
        with open('data/' + file_name) as data_file:  #odpalamy nasz pliczek jako obiekt json
            data = json.load(data_file)
        for D in data["days"]:                       #zauważamy że kolene dni są zawarte w polu days (D - to jeden dzień z zakresu)
            temperature.append(D["temp"])            #temperatury w danym dniu do jednej listy
            dates.append(D["datetime"])              #daty na drugą
            print(D["datetime"], ": ", D["temp"], "°C")
        plt.plot(dates, temperature)
        plt.grid()
        plt.title(f'Wykres temperatury w danym przedziale dni w mieście {name} ')
        plt.xlabel('Przedział dni')
        plt.ylabel('Temperatura w °C')
        plt.show()



    def check_is_data_files_exists(self):
        #OBSLUGA PLIKOW
        os.path.exists('data')  # pozwoli sprawdzić czy istnieje folder data (zawierający dane do wykresów), jak folder nie istnieje wyrzuci wyjątek FileNotFoundError
        if any(os.scandir('data')):  # sprawdzi czy w tym folderze wogóle są dane
            print("\nPosiadamy dane na temat miast: ")
            list_of_files = os.listdir('data')  #wypisanie nazw miast, czyli dostępnych plików bez rozrzerzeń, tu bierzemy listę plików z foderu data
            for F in list_of_files:             #dla każdego
                name, ext = os.path.splitext(F) #dzielimy go na nazwę i rozrzerzenie
                print(name)                     #wypisujemy nazwy
        else:
            raise FileNotFoundError # jak nie wystąpi bład który wyłapie exepct

    def choose_data_file_to_plot(self):
        #WYBIERANIE PLIKU
        while True:
            try:
                city_name = str(input("Podaj miasto dla którego dane chcesz wyświetlić: "))
                file_name = city_name + '.json' #nazwa pliczku to zawsze nazwa miasta + rozszerzczenie
                if os.path.isfile('data/'+ file_name):
                    break
                else:
                    raise ValueError
            except ValueError:
                print("Podano nieprawdołowe miassto, lista dozowolonych poniżej: ")
                list_of_files = os.listdir('data')  #wypisanie nazw miast, czyli dostępnych plików bez rozrzerzeń
                for F in list_of_files:
                    name, ext = os.path.splitext(F)
                    print(name)
        return file_name


if __name__ == '__main__':
    while True:
        while True:
            try:
                choose_wisely = input("\nPodaj polecenie:"
                         "\n/get - pobierz dane"
                         "\n/disp - wyświetl dane"
                         "\n/end - zakończ program"
                         "\nPodaj polecenie: ")
                break
            except ValueError:
                print("Błąd, spróbuj ponownie")
        weather = weather_API()
        if choose_wisely == "/get":
            weather.get_data_from_API()
        elif choose_wisely == "/disp":  #musimy sprawdzić czy istnieje wogóle folder z danymi do wyświetlania oraz czy nie jest on pusty
            try:
                weather.plot_historical_temp()
            except FileNotFoundError:
                print("Brak danych do wyświetlania spróbuj pobrać jakieś dane za pomocą /get.")
        elif choose_wisely == "/end":
            print("Koniec")
            break
        else:
            print("Bład, podano nieprawidłowe polecenie")



