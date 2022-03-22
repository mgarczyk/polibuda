


class platforma:
    def __init__(self):
        print("Platforma: ")
        self.nazwa = input("Podaj nazwe: ")
        self.adres = input("Podaj adres: ")

        #listy
        self.nauczyciele = []
        self.kursy = []
        self.studenci  = []

        #dodawanie nauczycieli na liste
        ile_nauczycieli = int(input("Podaj ile nauczycieli: "))
        for i in range(ile_nauczycieli):               #tu sie dodadzą nauczyciele do listy nauczycieli na platofrmie
            self.nauczyciele.append(nauczyciel())

        #dodawanie kursow  na liste
        ile_kursow = int(input("Podaj ile kursow: "))

        for i in range(ile_kursow):
            self.kursy.append(kurs(self.nauczyciele))  #tu sie stworzą kursy i wraz z przypisanymi im nauczycielami

        #dodawanie studentów na listy
        ile_studentow = int(input("Podaj liczbe studentow: "))
        for i in range(ile_studentow):
            self.studenci.append(student(self.kursy)) #dodawanie stuenta na listę studentów

    #wypisanie wszystkiego
    def get_data_platforma(self):
        print("\nPlatforma:", "\nNazwa: ", self.nazwa, "\nAdres: ", self.adres)
        print("\nNauczyciele na platformie: \n")
        for nauczyciel in self.nauczyciele:
            nauczyciel.get_data_nauczyciel()
        print("\nKursy na platformie: \n")
        for kurs in self.kursy:
            kurs.get_data_kurs()
        print("\nStudenci na platformie: \n")
        for student in self.studenci:
            student.get_data_student()


class nauczyciel:
    def __init__(self, pesel=""):
        if pesel == "":                                 #sytułacja gdy tworzymy nauczyciela w konstruktowrze kursu (czyli znamy PESEL i nie trzeba go podawć jescze raz)
            self.pesel = input("Podaj pesel: ")
        else:
            self.pesel = pesel
        self.email = input("Podaj email: ")
        self.stopien = input("Podaj stopien: ")
        self.kursy = []

    def get_data_nauczyciel(self): #drukowanie z klasy
        print ("\nPESEL: ", self.pesel, "\nEmail: ", self.email, "\nStopien: ", self.stopien)



class kurs:
    def __init__(self, nauczyciele): #tworzenie kursu
        self.nazwa = input("Nazwa: ")
        self.semestr = input("Semestr: ")
        self.nauczyciel = None                                   #Tworzymy pusty obiekt typu nauczyciel
        self.studenci = []                                       #studenci przypisani do tego kursu
        pesel = input("Podaj pesel nauczyciela: ")
        #walidacja (sprawdzenie czy nauczyciela o takim peselu już nie ma w bazie)
        for N in nauczyciele:                                    #N to jest jeden z obiektów klasy nauczyciel (cały z peselem, emailem, i co tam jeszcze ma z tych co już stworzyliśmy wyżej)
            if pesel == N.pesel:
                self.nauczyciel = N                              #N staje się nauczycielem danego kursu
                N.kursy.append(self)                             #Referencja N-> uczy w tym kursie-> ten kurs zsotaje przypisany do N
                break

        #jezeli nie znaleziono takiego PESELU
        if  self.nauczyciel is None:                            #jeśli nie znaleizono takeigo peselu to tworzymy nowego nauczyciela
            self.nauczyciel = nauczyciel(pesel)                 #stwórz nowego nauczyciela, ale jego pesel ustaw taki sam jak user już wpisał
            self.nauczyciel.kursy.append(self)
            nauczyciele.append(self.nauczyciel)                 #dodaj tego nauczyciela na listę naucztcieli


    def get_data_kurs(self):
        print("\nNazwa: ", self.nazwa, "\nSemestr:  ", self.semestr)
        print("\nNauczyciel w kursie: ", self.nazwa)
        self.nauczyciel.get_data_nauczyciel()

    def get_data_kurs_student(self):
        print("\nNazwa: ", self.nazwa, "\nSemestr:  ", self.semestr)



class student:
    def __init__(self, kursy):                                                          #tu są kursy ogólne (wszytkie)
        self.pesel = input("Podaj pesel: ")
        self.email = input("Podaj email: ")
        self.semestr = input("Podaj semsetr: ")
        self.kursy = []                                                                 #to są kursy tego studenta
        ile_kursow = int(input("Podaj liczbe kursów: "))
        i = 1
        while(i <= ile_kursow):                                                         #"zapisywanie" studenta na kursy w których powinien uczestniczyć
            find = False
            nazwa_kursu = input("Podaj nazwe kursu: ")                                  #podajemy nazwe
            for K in kursy:                                                             #przeszukujemy dostępne kursy, tak jak wcześniej nauczycieli
                if nazwa_kursu == K.nazwa and K.semestr == self.semestr:                #K to obiekt klasy kurs
                    self.kursy.append(K)                                                #dodajemy znaleziony kurs do tablicy zawierającej kursy danego sudenta
                    K.studenci.append(self)                                             #dodajemy tego studenta do tablicy studentów uczestniczących w danym kursie
                    find = True
                    ile_kursow -= 1                                                        #jeżeli jest ok, to mamy prawidłowo dodany kurs zatem zmienną find ustaiwamy jako True oraz zwiększamy i
                    break
            if find == False:                                                            #jeżeli nie znaleziono to find jest False
                print("Błąd: albo taki kure nie istnieje, albo semestr kursu i studenta nie zgadza się. Spróbuj ponownie") #komuniakt
                if (i > 1): i -= 1                                               #zminiejszamy ilość wykonanń o jedno, dajemy kolejną szansę userowi - zmniejszając i "cofamy pętlę"



    def get_data_student(self):
        print("\nPESEL ", self.pesel, "\nEmail:  ", self.email, "\nSemestr:  ", self.semestr)
        print("\nKursy studenta: ")
        for kurs in self.kursy: #wypisujemy inofrmację o kursach danego studenta
            kurs.get_data_kurs_student()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   platforma_1 = platforma()
   platforma_1.get_data_platforma()

