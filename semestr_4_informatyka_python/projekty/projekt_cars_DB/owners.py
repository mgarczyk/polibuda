#import biblotek zewnętrznych
import mysql.connector
import pesel_utils
from mysql.connector import errorcode
#import naszych plików
import config



class Owner:
    def __init__(self):
        #wybór co checmy robić
        while True:
            try:
                choose = str(input("Czy chcesz pobrać dane z bazy czy stworzyć nowy obiekt? "
                                   "\n/select - pobierz z bazy"
                                   "\n/insert - stwórz i dodaj nowego właściciela do bazy lub podając pesel już istniejący w bazie zaaktualizuj dane właściciela"
                                   "\n"))
                break
            except ValueError:
                print("Błędne dane")
        #select i tworzenie obiektu z bazy na podstaiwe numeru rejestracyjnego
        if choose == "/select":
            self.select_single_owner()
        elif choose == "/insert":
            self.create_object_and_insert_to_DB()
        else:
            print("Błędne dane.")


    def select_single_owner(self):
        while True:
            try:
                self.pesel = str(input("Podaj PESEL właścicela: "))
                if not pesel_utils.is_valid(self.pesel): # funkcja sprawdzająca poprawność podanego peselu, https://github.com/queereen/pesel_utils
                    raise ValueError # jak nie poprawny to rozpoznajemy to jako wyjątek i obsługujemy
                else:
                    break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        query = """SELECT * FROM owners WHERE pesel = %s"""
        owners_config.cursor.execute(query, (self.pesel,))
        records = owners_config.cursor.fetchall()
        if records is []:
            print(f"Nie znaleziono pojazdów o numerze {self.pesel}")
        else:
            for row in records:
                self.owner_ID = row[0]
                self.pesel = row[1]
                self.first_name = row[2]
                self.last_name = row[3]

        self.delete_copy_after_update_or_select() #usuwanie kopii z listy, np. gdyby user dwa razy to samo pobrał z bazy na listę


    def create_object_and_insert_to_DB(self):
        while True:
            try:
                self.pesel = str(input("Podaj PESEL właścicela: "))
                if not pesel_utils.is_valid(self.pesel): # funkcja sprawdzająca poprawność podanego peselu, https://github.com/queereen/pesel_utils
                    raise ValueError # jak nie poprawny to rozpoznajemy to jako wyjątek i obsługujemy
                else:
                    break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")

        while True:
            try:
                self.first_name = str(input("Podaj imię właściciela: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                self.last_name = str(input("Podaj nazwisko właściciela: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        #wykonanie kwernedy
        query = "INSERT INTO owners (pesel, first_name, last_name) VALUES (%s, %s, %s)" # te procenty ozanczają zmienne i ich rodzej %s to string, a %d to intiger
        record = (self.pesel, self.first_name, self.last_name)
        try:
            owners_config.cursor.execute(query, record)
            print(owners_config.cursor.rowcount, f"Dane dotycząceosoby o takim numerze pesel {self.pesel} zostały dodane do tabeli.")
            owners_config.cnx.commit()
            #pobranie informacji o samym ID pojazdu
            query = """SELECT owner_ID FROM owners WHERE pesel = %s"""
            owners_config.cursor.execute(query, (self.pesel,))
            records = owners_config.cursor.fetchone()
            for row in records:
                self.owner_ID = row
        except mysql.connector.IntegrityError as err:  #jeżeli dany numer peseljest zajęty robimy update lub nie
            self.update_owner()



    def update_owner(self):
        while True:
            try:
                choose = str(input("Osoba takim numerze pesel już istnieje, czy chcesz zaaktualizować dane? Podaj Y jeżeli tak lub N jeżeli nie."))
                if choose not in ['Y', 'N']:
                    raise ValueError
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        if choose == "Y":
            query = "UPDATE owners SET  pesel = %s, first_name = %s, last_name = %s WHERE (pesel = %s)" #updateujemy wiersz zawierający podany numer pesel
            record = (self.pesel, self.first_name, self.last_name, self.pesel)
            try:
                owners_config.cursor.execute(query, record)
                print(owners_config.cursor.rowcount, f"Dane dotyczące osoby o numerze pesel {self.pesel} zostały zaaktualizowane.")
                owners_config.cnx.commit()
                #pobranie informacji o samym ID pojazdu
                query = """SELECT owner_ID FROM owners WHERE pesel = %s"""
                owners_config.cursor.execute(query, (self.pesel,))
                records = owners_config.cursor.fetchone()
                for row in records:
                    self.owner_ID = row
                self.delete_copy_after_update_or_select() #teraz usuwamy stary obiekt o numerze rejestracyjnym takim samym jak ten obiekt w którym jesteśmy, zadziała bo stary obiekt jest wcześniej na liście niż ten aktralny
            except mysql.connector.IntegrityError as err:  #jeżeli dany numer rejestracyjny jest zajęty robimy update lub nie
                print("Bład, być może podano złą nazwę tabeli, spróbuj ponownie.")
        else:
            print("Ok, przechodzimy dalej.")


    def print_owner(self):
        print("owner_ID = ", self.owner_ID)
        print("pesel = ", self.pesel)
        print("first_name = ", self.first_name)
        print("last_name  = ", self.last_name, "\n")

    # usunięcie obiektu o tym samym numerze (robimy update stary elemrnt należy usunąć)
    def delete_copy_after_update_or_select(self):
        for O in owners_list:
            if O.pesel == self.pesel:
                owners_list.remove(O)
                break




if __name__ == '__main__':

    owners_config = config.configuration()  #obiekt który jest jakby naszą bazą - z pliku cars_DB_handler.py, zaiera selecty i wyświetlanie + inserty
    #pusta tablica na obiekty cars
    owners_list = []
    while True:
        while True:
            try:
                choose = str(input("Czy chcesz utworzyć kolejny obiekt? Y/N: "))
                break
            except ValueError:
                print("Błędne dane")
        if choose == 'Y':
            owners_list.append(Owner())
            for O in owners_list:
                O.print_owner()
        elif choose == 'N':
            for O in owners_list:
                O.print_owner()
            quit()






