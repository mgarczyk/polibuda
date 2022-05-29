#import biblotek zewnętrznych
import mysql.connector
import pdb
from mysql.connector import errorcode
#import naszych plików
import config



class Car:
    def __init__(self):
        #wybór co checmy robić
        while True:
            try:
                choose = str(input("Czy chcesz pobrać dane z bazy czy stworzyć nowy obiekt? "
                                   "\n/select - pobierz z bazy"
                                   "\n/insert - stwórz i dodaj nowy pojazd  do bazy lub podaj numer rejestracyjny już istniejącego pojazdu i zaakutalizuj jego dane"
                                   "\n"))
                break
            except ValueError:
                print("Błędne dane")
        #select i tworzenie obiektu z bazy na podstaiwe numeru rejestracyjnego
        if choose == "/select":
            self.select_single_car()
        elif choose == "/insert":
            self.create_object_and_insert_to_DB()
        else:
            print("Błędne dane.")


    def select_single_car(self):
        while True:
            try:
                self.register_number = str(input("Podaj numer rejestracyjny: "))
                break
            except ValueError:
                print("Błędne dane")
        query = """SELECT * FROM cars WHERE register_number = %s"""
        cars_config.cursor.execute(query, (self.register_number,))
        records = cars_config.cursor.fetchall()
        if records is []:
            print(f"Nie znaleziono pojazdów o numerze {self.register_number}")
        else:
            for row in records:
                self.car_ID = row[0]
                self.register_number = row[1]
                self.mark = row[2]
                self.model = row[3]
                self.horse_power = row[4]
                self.color = row[5]
                self.year_of_production = row[6]
                self.owner_ID = row[7]

        self.delete_copy_after_update_or_select()  #jeżeli user pobierze dane i powtórzy się ten sam numer co poprzednio to usuwamy jedną z kopii


    def create_object_and_insert_to_DB(self):
        #marka itd.
        while True:
            try:
                self.register_number = str(input("Podaj numer rejestracyjny: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.mark = str(input("Podaj markę: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")

        while True:
            try:
                self.model = str(input("Podaj model: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.horse_power = int(input("Podaj ilość koni mechanicznych: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.color = str(input("Podaj kolor: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.year_of_production = int(input("Podaj rok produkcji: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.owner_ID = int(input("Podaj ID właściciela pojazdu: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        #wykonanie kwernedy
        query = "INSERT INTO cars (register_number, mark, model, horse_power, color, year_of_production, owner_ID) VALUES (%s, %s, %s, %s, %s, %s, %s )" # te procenty ozanczają zmienne i ich rodzej %s to string, a %d to intiger
        record = (self.register_number, self.mark, self.model, self.horse_power, self.color, self.year_of_production, self.owner_ID)
        try:
            cars_config.cursor.execute(query, record)
            print(cars_config.cursor.rowcount, f"Dane dotyczące pojazdu o numerze rejestracyjnym {self.register_number} zostały dodane do tabeli.")
            cars_config.cnx.commit()
            #pobranie informacji o samym ID pojazdu
            query = """SELECT car_ID FROM cars WHERE register_number = %s"""
            cars_config.cursor.execute(query, (self.register_number,))
            records = cars_config.cursor.fetchone()
            for row in records:
                self.car_ID = row
        except mysql.connector.IntegrityError as err:  #jeżeli dany numer rejestracyjny jest zajęty robimy update lub nie
            self.update_car()



    def update_car(self):
        while True:
            try:
                choose = str(input("Pojazd o takim numerze rejestracyjnym już istnieje, czy chcesz zaaktualizować dane? Podaj Y jeżeli tak lub N jeżeli nie."))
                if choose not in ['Y', 'N']:
                    raise ValueError
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        if choose == "Y":
            query = "UPDATE cars SET  register_number = %s, mark = %s, model = %s,  horse_power = %s, color = %s, year_of_production = %s, owner_ID = %s WHERE (register_number = %s)" #updateujemy wiersz zawierający podany numer rejestracyjny
            record = (self.register_number, self.mark, self.model, self.horse_power, self.color, self.year_of_production, self.owner_ID, self.register_number)
            try:
                cars_config.cursor.execute(query, record)
                print(cars_config.cursor.rowcount, f"Dane dotyczące pojazdu o numerze rejestracyjnym {self.register_number} zostały zaaktualizowane.")
                cars_config.cnx.commit()
                #pobranie informacji o samym ID pojazdu
                query = """SELECT car_ID FROM cars WHERE register_number = %s"""
                cars_config.cursor.execute(query, (self.register_number,))
                records = cars_config.cursor.fetchone()
                for row in records:
                    self.car_ID = row
                self.delete_copy_after_update_or_select() #teraz usuwamy stary obiekt o numerze rejestracyjnym takim samym jak ten obiekt w którym jesteśmy, zadziała bo stary obiekt jest wcześniej na liście niż ten aktralny
            except mysql.connector.IntegrityError as err:  #jeżeli dany numer rejestracyjny jest zajęty robimy update lub nie
                print("Bład, być może podano złą nazwę tabeli, spróbuj ponownie.")
        else:
            print("Ok, przechodzimy dalej.")


    def print_car(self):
        print("car_ID = ", self.car_ID)
        print("register_number = ", self.register_number)
        print("mark = ", self.mark)
        print("model  = ", self.model)
        print("horse_power  = ", self.horse_power)
        print("color  = ", self.color)
        print("year_of_production  = ", self.year_of_production)
        print("owner_ID  = ", self.owner_ID , "\n")

    # usunięcie obiektu o tym samym numerze (robimy update stary elemrnt należy usunąć)
    def delete_copy_after_update_or_select(self):
        for C in cars_list:
            if C.register_number == self.register_number:
                cars_list.remove(C)
                break




if __name__ == '__main__':

    cars_config = config.configuration()  #obiekt który jest jakby naszą bazą - z pliku cars_DB_handler.py, zaiera selecty i wyświetlanie + inserty
    #pusta tablica na obiekty cars
    # pdb.set_trace() # - uruchamia debbuger pythona, linia po linii można sprawdzić czy wszystko git bo ten pycharmowy nie zawsze działa (żeby przejść dalej klikamy n->Enter)
    cars_list = []
    while True:
        while True:
            try:
                choose = str(input("Czy chcesz utworzyć kolejny obiekt? Y/N: "))
                break
            except ValueError:
                print("Błędne dane")
        if choose == 'Y':
            cars_list.append(Car())
            for C in cars_list:
                C.print_car()
            cars_list[0].mark = 'BMW'
            cars_list[0].update_car()
        elif choose == 'N':
            for C in cars_list:
                C.print_car()
            quit()






