import pesel_utils
import mysql.connector
from mysql.connector import errorcode
from mysql.connector.errors import Error




class cars_DB_handling:
    def __init__(self):
        #tu otwieramy połączenie z naszą bazą danych
        config = {
            'user': 'root',
            'password': 'Kamera97',
            'host': '127.0.0.1',
            'database': 'cars_db',
            'raise_on_warnings': True
        }
        try:
            self.cnx = mysql.connector.connect(**config)
        except mysql.connector.Error:
            print("Błąd podczas łączenia się z bazą danych, spróbuj poprawić hasło lub nazwę użytkownika.")
        self.cursor = self.cnx.cursor()

    def choose_table(self):
        while True:
            try:
                table_name = str(input("Podaj nazwę tabeli: "
                                       "\ncars - tabela z informacjami o pojazdach"
                                       "\nowners - tabela z informacjami o ich właścicielach"
                                       "\n"))
                if table_name not in ["cars", "owners"]:
                    raise ValueError
                else:
                    break
            except ValueError:
                print("Podano błędną nazwę tabeli, spróbuj ponownie.")
        return table_name

    def check_query(self, query):
        try:
            self.cursor.execute(query)  #wykonanie zapytania do bazy
        except mysql.connector.ProgrammingError as err:
            if err.errno == errorcode.ER_SYNTAX_ERROR:
                print("Wystąpił błąd, prawdopodbnie taka tabela nie istnieje")
            else:
                print("Error: {}".format(err))
            print("Spróbuj ponownie")

    def insert_data(self):
        # wybór tabeli
        table_name = self.choose_table()
        # pobieranie danych
        if table_name == "cars":
            self.insert_cars()
        elif table_name == "owners":
            self.insert_owners()
        else:
            print("Błędne dane, spróbuj ponownie.")


    def insert_cars(self):
        #marka itd.
        while True:
            try:
                mark = str(input("Podaj markę: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")

        while True:
            try:
                model = str(input("Podaj model: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                horse_power = int(input("Podaj ilość koni mechanicznych: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                color = str(input("Podaj kolor: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                year_of_production = int(input("Podaj rok produkcji: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                owner_ID = int(input("Podaj ID właściciela pojazdu produkcji: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        #wykonanie kwernedy
        query = "INSERT INTO cars (mark, model, horse_power, color, year_of_production, owner_ID) VALUES (%s, %s, %s, %s, %s, %s )" # te procenty ozanczają zmienne i ich rodzej %s to string, a %d to intiger
        record = (mark, model, horse_power, color, year_of_production, owner_ID)
        try:
            self.cursor.execute(query, record)
            print(self.cursor.rowcount, "Rekord został dodany do tabeli")
            self.cnx.commit()
        except mysql.connector.ProgrammingError as err:
            if err.errno == errorcode.ER_SYNTAX_ERROR:
                print("Prawdopodbnie podana tabela nie istnieje")
            else:
                 print("Error: {}".format(err))
            print("Spróbuj ponownie.")


    def insert_owners(self):
        while True:
            try:
                pesel = str(input("Podaj PESEL właścicela: "))
                if not pesel_utils.is_valid(pesel): # funkcja sprawdzająca poprawność podanego peselu, https://github.com/queereen/pesel_utils
                    raise ValueError #jak nie poprawny to rozpoznajemy to jako wyjątek i obsługujemy
                else:
                    break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")

        while True:
            try:
                first_name = str(input("Podaj imię właściciela: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        while True:
            try:
                last_name = str(input("Podaj nazwisko właściciela: "))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")

        #wykonanie kwernedy
        query = "INSERT INTO owners (pesel, first_name, last_name) VALUES (%s, %s, %s)" # te procenty ozanczają zmienne i ich rodzej %s to string, a %d to intiger
        record = (pesel, first_name, last_name)
        try:
            self.cursor.execute(query, record)
            print(self.cursor.rowcount, "Rekord został dodany do tabeli")
            self.cnx.commit()
        except mysql.connector.errors.IntegrityError as err:
            print("Osoba o takim PESELU jest już w bazie danych, spróbuj ponownie.")
            return 0

    def select_data(self):
        # pobieranie skąd chcemy wyświetlić
        table_name = self.choose_table()
        # obsługa wyświetlania z tabel
        query = (f"SELECT * FROM {table_name}")
        self.check_query(query)  # sprawdzamy, czy kwerencda nie generuje błędu, jeśli tak to jaki
        records = self.cursor.fetchall()  # konwertuje nasze dane, tak że dana kulmna z bazy, zajmuje jeden wiersz, np. car_ID wiersz 0 itd.
        if table_name == "cars":
            self.print_cars(records)
        elif table_name == "owners":
            self.print_owners(records)
        else:
            print("Błędna nazwa.")


    def print_cars(self, records):
        # wyśiwtlanie aut
        for row in records:
            print("car_ID = ", row[0])
            print("mark = ", row[1])
            print("model  = ", row[2])
            print("horse_power  = ", row[3])
            print("color  = ", row[4])
            print("year_of_production  = ", row[5])
            print("owner_ID  = ", row[6], "\n")

    def print_owners(self, records):
        for row in records:
            print("owner_ID = ", row[0])
            print("pesel = ", row[1])
            print("first_name  = ", row[2])
            print("last_name  = ", row[3], "\n")

    def select_cars_by_mark(self):
        while True:
            try:
                mark = str(input("Podaj markę pojazdu"
                                 "\n"))
                break
            except ValueError:
                print("Podano błędne dane, spróbuj ponownie")
        query = """SELECT * FROM cars INNER JOIN owners ON cars.owner_ID = owners.owner_ID WHERE mark = %s"""
        self.cursor.execute(query, (mark, ))
        records = self.cursor.fetchall()
        if records is []:
            print(f"Nie znaleziono pojazdów marki {mark}")
        else:
            self.print_cars_by_mark(records)


    def print_cars_by_mark(self, records):
        for row in records:
            print("Samochód: ")
            print("car_ID = ", row[0])
            print("mark = ", row[1])
            print("model  = ", row[2])
            print("horse_power  = ", row[3])
            print("color  = ", row[4])
            print("year_of_production  = ", row[5])
            print("owner_ID  = ", row[6], "\n")
            print("Właściciel: ")
            print("owner_ID  = ", row[7])
            print("pesel = ", row[8])
            print("first_name  = ", row[9])
            print("last_name  = ", row[10], "\n")




if __name__ == '__main__':
    while True:
        while True:
            cars_DB_handle = cars_DB_handling() # obiekt "uchwyt", w pewnym sensie ilustrujący naszą bazę danych i co chcemy z nią robić
            try:
                choose = str(input("Podaj polecenie:"
                                   "\n/insert - wstaw dane"
                                   "\n/select - wyświetl dane"
                                   "\n/select_mark - zwraca pojazdy danej marki wraz z ich właścicielami"
                                   "\n/end - zakończ"
                                   "\n"))
                if choose not in ["/insert", "/select", "/select_mark", "/end"]:
                    print("Podano polecenie które nie istnieje.")
                    raise ValueError
                else:
                    break
            except ValueError:
                print("Spróbuj ponownie")

        if choose == "/insert":
            cars_DB_handle.insert_data()
        elif choose == "/select":
            cars_DB_handle.select_data()
        elif choose == "/select_mark":
            cars_DB_handle.select_cars_by_mark()
        elif choose == "/end":
            cars_DB_handle.cursor.close()
            cars_DB_handle.cnx.close()
            quit()
        else:
            print("Błąd, spróbuj ponownie")


