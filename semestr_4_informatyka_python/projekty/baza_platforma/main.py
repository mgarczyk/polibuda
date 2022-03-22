
import datetime
from dateutil.relativedelta import relativedelta

class platform:
    def __init__(self):
        print("Platforma: ")
        self.name = input("Podaj nazwe: ")
        self.address = input("Podaj adres: ")

        #listy
        self.Teachers = []
        self.Courses = []
        self.Students  = []

                                                                                # dodawanie nauczycieli na liste
        #podawanie ilości -  zabezpieczamy try...expcect
        while True:
            try:
                number_of_teachers = int(input("Podaj liczbe nauczycieli: "))
                break
            except ValueError:
                print("Spróbuj ponownie, podaj liczbę całkowitą: ")
        #pętla dodająca nauczycieli do tablicy
        for i in range(number_of_teachers):
            self.Teachers.append(teacher())



                                                                               # dodawanie kursow  na liste
        while True:
            try:
                number_of_courses = int(input("Podaj liczbe kursów: "))
                break
            except ValueError:
                print("Spróbuj ponownie, podaj liczbę całkowitą: ")
        #pętla dodająca kursy do tablicy
        for i in range(number_of_courses):
            self.Courses.append(course(self.Teachers))



        while True:                                                           # dodawanie studentów  na liste
            try:
                number_of_students = int(input("Podaj liczbe studentów: "))
                break
            except ValueError:
                print("Spróbuj ponownie, podaj liczbę całkowitą: ")
        #dodawanie
        for i in range(number_of_students):
            self.Students.append(student(self.Courses))




    #wypisanie wszystkiego
    def get_data_platform(self):
        print("\nPlatforma:", "\nNazwa: ", self.name, "\nAdres: ", self.address)
        print("\nNauczyciele na platformie: \n")
        for T in self.Teachers:
            T.get_data_teacher()
        print("\nKursy na platformie: \n")
        for C in self.Courses:
            C.get_data_course()
        print("\nStudenci na platformie: \n")
        for S in self.Students:
            S.get_data_student()
            print('\n--------------------------------')

    def sort_Students_alphabetical_mail(self):                                      # sortujemy studentów po wieku
        print('\n++++++++++++++++++++++++++++++++++')
        sorted_Students = sorted(self.Students, key=lambda S: S.email)
        print("Studenci posrtowani alfabetycznie po mailu")
        for S in sorted_Students:
            S.get_data_student()
        print('\n++++++++++++++++++++++++++++++++++')


    def sort_Students_by_age(self):
        print('\n++++++++++++++++++++++++++++++++++')
        sorted_Students = sorted(self.Students, key=lambda S: S.age)              # to obiekt klasy student, a my sortujemy po mailu, obiekt należy do tablicy Studentts
        print("Studenci posrtowani po wieku: ")
        for S in sorted_Students:
            S.get_data_student()
        print('\n++++++++++++++++++++++++++++++++++')


    def sort_Teachers_alphabetical_mail(self):                                      # sortujemy nauczycieli albabeytycznie po mailu
        print('\n++++++++++++++++++++++++++++++++++')
        sorted_Teachers = sorted(self.Teachers, key=lambda T: T.email)              # T to obiekt klasy teacher, a my sortujemy po mailu, obiekt należy do tablicy Teachers
        print("Nauczyciele posrtowani alfabetycznie po mailu")
        for T in sorted_Teachers:
            T.get_data_teacher()
        print('\n++++++++++++++++++++++++++++++++++')


    def get_courses_by_semestr(self):
        print('\n++++++++++++++++++++++++++++++++++')
        requested_semestr = int(input("\nPodaj semestr kutrsów, które chcesz wyświetlić: "))
        for K in self.Courses:
            if K.semestr == requested_semestr:
                K.get_data_course()

        print('\n++++++++++++++++++++++++++++++++++')

    def add_marks_of_Students(self):                                                         # podawanie ocen studentów
        pesel_mark = input("Podaj pesel studenta, któremu chcesz wpisać ocenę: ")
        course_mark = input("Podaj kurs do którego ocenę chcesz podać: ")
        find = False
        for S in self.Students:
            if S.pesel == pesel_mark:
                find = True
                S.add_mark_of_student(course_mark)                                           # dodanie oceny po peselu
        if find == False:
            print("Nie ma takeigo studenta w bazie. Spróbuj ponownie")

        print('\n++++++++++++++++++++++++++++++++++')

    def get_avarage_grade_of_student(self):                                                  # funkcja wyświetlająca średnią jednego studenta podanego przez usera
        pesel = input("Podaj pesel studenta którego średnią chcesz sprawdzić: ")
        find = False
        for S in self.Students:
            if S.pesel == pesel:
                 find = True
                 S.count_avg_of_S()
                 print("Średnia studenta o peselu: ", pesel, " to ", S.avg)
        if find == False:
            print("\nBłąd, nie ma takiego studenta w bazie")
        print('\n++++++++++++++++++++++++++++++++++')

    def get_avarge_grade_of_Students(self):
        print("\nŚrednia osobnno dla każdego studenta")
        for S in self.Students:
            S.count_avg_of_S()
            print("\n", S.pesel, S.avg)
        print('\n++++++++++++++++++++++++++++++++++')

    def get_avarage_of_course(self):
        course_name = input("Podaj nazwę kursu którego średnia ma zostać policzona: ")
        sum_of_S_avg = 0.0   #suma średnich studentów w kursie
        find = False
        for C in self.Courses:
            if C.name == course_name:
                find = True
                for S in C.Students:
                    sum_of_S_avg += S.count_avg_of_S_in_C(course_name)                              #oblicznie średnich studentów  w kursie
                C.avarge_of_course = float(sum_of_S_avg / len(C.Students))                          #obliczamy sumę ocen podanego kursu dla wszytkich studentów i dzielimy przez ilość studentów w tym kursie
                print("Średnia w kursie ", course_name, " to ", C.avarge_of_course)
                break
        if find == False:
               print("Nie znaleziono takeigo kursu w bazie.")


    def get_avarge_grade_of_platofrm(self):                                                         #funkcja obliczająca i wyświetlająca średnią całej platormy (po studentach)
        self.sum_of_S_avg = 0.0
        for S in self.Students:
            S.count_avg_of_S()
            self.sum_of_S_avg += S.avg                                                              #suma średnich wszystkich studentów
        self.avg_of_P = float(self.sum_of_S_avg / len(self.Students))                               #sumujemy średnie studentów i dzelimy przez ich ilość na całej platofrmie
        print("Średnia całej platoformy to: ", self.avg_of_P)
        print('\n++++++++++++++++++++++++++++++++++')






class teacher:
    def __init__(self, pesel=""):
        if pesel == "":                                                                             #sytułacja gdy tworzymy nauczyciela w konstruktowrze kursu (czyli znamy PESEL i nie trzeba go podawć jescze raz)
            self.pesel = input("Podaj pesel: ")
        else:
            self.pesel = pesel
        self.email = input("Podaj email: ")
        self.degree = input("Podaj stopien: ")
        self.Courses = []

    def get_data_teacher(self): #drukowanie z klasy
        print ("\nPESEL: ", self.pesel, "\nEmail: ", self.email, "\nStopien: ", self.degree)
        print('\n--------------------------------')


class course:
    def __init__(self, Teachers): #tworzenie kursu
        self.name = input("Nazwa: ")
        self.semestr = int(input("Semestr: "))
        self.teacher = None                                                                 #Tworzymy pusty obiekt typu nauczyciel
        self.Students = []                                                                  #studenci przypisani do tego kursu
        pesel = input("Podaj pesel nauczyciela: ")
        #walidacja (sprawdzenie czy nauczyciela o takim peselu już nie ma w bazie)
        for T in Teachers:                                                                  #T to jest jeden z obiektów klasy nauczyciel (cały z peselem, emailem, i co tam jeszcze ma z tych co już stworzyliśmy wyżej)
            if pesel == T.pesel:
                self.teacher = T                                                            #T staje się nauczycielem danego kursu
                T.Courses.append(self)                                                      #Referencja T-> uczy w tym kursie-> ten kurs zsotaje przypisany do T
                break

        #jezeli nie znaleziono takiego PESELU
        if  self.teacher is None:                                                           #jeśli nie znaleizono takeigo peselu to tworzymy nowego nauczyciela
            self.teacher = teacher(pesel)                                                   #stwórz nowego nauczyciela, ale jego pesel ustaw taki sam jak user już wpisał
            self.teacher.Courses.append(self)
            Teachers.append(self.teacher)                                                   #dodaj tego nauczyciela na listę naucztcieli


    def get_data_course(self):
        print("\nNazwa: ", self.name, "\nSemestr:  ", self.semestr)
        print("\nPESEL nauczyciela w kursie: ", self.teacher.pesel)
        print('\n--------------------------------')

    def get_data_course_student(self):                                                      #wypisuje nazwy i semsetru kursów do których należy dany student
        print("\nNazwa: ", self.name)





class student:
    def __init__(self, Courses):                                                          #tu są kursy ogólne (wszytkie)
        self.pesel = input("Podaj pesel: ")
        self.email = input("Podaj email: ")
        self.semestr = int(input("Podaj semsetr: "))
        self.Courses = []                                                                 #to są kursy tego studenta
        self.Marks = {}                                                                   #słownik z ocenami studenta (żeby można rozpoznać kurs) np. polski: [3,4,5], angielski:[5,2,1] itd.
        #dodawanie kursów studenta                                                        #poniższa instrukacja sprawdzi czy user podał wartość int, a jak nie to pozowli spróbować ponownie zamiast zepsuć program
        while True:
            try:
                number_of_courses = int(input("Podaj liczbe kursów: "))
                break
            except ValueError:
                print("Spróbuj ponownie, podaj liczbę całkowitą: ")
        #"zapisywanie" studenta na kursy w których powinien uczestniczyć
        i = 1
        while i <= number_of_courses:
            find = False
            course_name = input("Podaj nazwe kursu: ")                                    #podajemy nazwe
            for K in Courses:                                                             #przeszukujemy dostępne kursy, tak jak wcześniej nauczycieli
                if course_name == K.name and K.semestr == self.semestr:                   #K to obiekt klasy kurs
                    self.Courses.append(K)                                                #dodajemy znaleziony kurs do tablicy zawierającej kursy danego sudenta
                    K.Students.append(self)                                               #dodajemy tego studenta do tablicy studentów uczestniczących w danym kursie
                    find = True
                    number_of_courses -= 1                                                #jeżeli jest ok, to mamy prawidłowo dodany kurs zatem zmienną find ustaiwamy jako True oraz zwiększamy i
                    break
            if find == False:                                                             #jeżeli nie znaleziono to find jest False
                print("\nBłąd: albo taki kure nie istnieje, albo semestr kursu i studenta nie zgadza się. Spróbuj ponownie") #komuniakt
                if (i > 1): i -= 1                                                        #zminiejszamy ilość wykonanń o jedno, dajemy kolejną szansę userowi - zmniejszając i "cofamy pętlę"

        #pusty słownik kluczowany nazwami kursów - trzeba go utworzyć
        for C in self.Courses:
            self.Marks[C.name] = []
        #wyznacznie wieku i daty urodzenia studenta na podstawie peselu
        self.count_stuent_age()                                                         #funkcja ta wyznaczy za pomocą peselu datę urzodzenia i wiek stuednta


    def get_data_student(self):
        print("\nPESEL ", self.pesel, "\nEmail:  ", self.email, "\nSemestr:  ", self.semestr, "\nData narodzin:  ", self.date_of_S_bday, "\nWiek:  ", self.age)
        print("\nKursy studenta: ")
        for K in self.Courses: #wypisujemy inofrmację o kursach danego studenta
            K.get_data_course_student()
        print("\nOceny studenta:")
        print(self.Marks)
        print('\n--------------------------------')


    def add_mark_of_student(self, course_mark):
        # dodawanie ocen kluczami są nazwy kursów
        accepted_marks = [2.0, 3.0, 3.5, 4.0, 4.5, 5.0]                                          # oceny akceptowne
        find = False
        for C in self.Courses:                                                                  # nasze klucze to nazyw kursów czyli C.name
            if(C.name == course_mark):
                find = True
                print("\nDodaj oceny do kursu ", course_mark, " studentowi o peselu ", self.pesel)

                while True:
                    try:
                        number_of_marks = int(input("Podaj liczbe ocen do wpisania "))                 #zabezpieczenie przed wpisaniem wartości innej niż liczba całkowita
                        break
                    except ValueError:
                        print("Spróbuj ponownie, podaj liczbę całkowitą: ")

                for i in range(number_of_marks):
                    while (True):                                                               # pętla while powtórzy się tyle razy ile user pomyli się z podaniem oceny
                        mark = float(input("Podaj ocenę - skala 2.0-5.0: "))
                        if mark in (accepted_marks):                                            # prawdzenie czy ocena jest prawidołowa
                            self.Marks[C.name].append(mark)                                     # dodanie do tablicy ocen dla danego kursu nowej oceny
                            break
                        else:
                            print("\nPodano ocenę spoza skali")
        if find == False:
            print("Nie ma kursu o tej nazwie w bazie. Spróbuj ponownie")



    def count_avg_of_S(self):
            sum_of_marks = 0.0
            number_of_marks = 0
            #wyznacznie sumy ocen - przechodzimy po kluczach słownika
            for K in self.Marks:
                sum_of_marks += sum(self.Marks[K])                                          #wyznaczy sumę ocen po kluczu - klucze to nazwy przedmitów (to doda wszytkie oceny np. z polskiego
                number_of_marks += len(self.Marks[K])                                       #wyznczy ilość ocen po kluczu
            self.avg = (sum_of_marks / number_of_marks)




    def count_avg_of_S_in_C(self, course_name):                                    #liczymy sumę ocen z danego kursu o danego studenta
        sum_of_marks = 0.0
        number_of_marks = 0
        #wyznacznie sumy ocen dla danego kursu u danego studenta - przechodzimy po kluczach słownika
        for K in self.Marks:
            sum_of_marks += sum(self.Marks[course_name])                                #wyznaczy sumę ocen dla konkretnego przedmiotu
            number_of_marks += len(self.Marks[course_name])                             #wyznczy ilość ocen klucz
            break
        avg_of_S_in_C = float(sum_of_marks/number_of_marks)                             #średnia tego studenta w podanym przez usera kursie (powtarzamy dla każdego innego studenta i dzielimy przez ich ilość)
        return avg_of_S_in_C                                                            #zwracamy


    def count_stuent_age(self):
        year = int(self.pesel[0:2])                                                     #rok w peselu pierwsze dwie cyfry
        month = int(self.pesel[2:4])                                                    #miesiąc w peselu kolejen dwie
        day = int(self.pesel[4:6])                                                      #potem dzień
        if(year < 99 and year > 10):
            pre =  1900                                                                 #pesel przed 2000 w postaci np. 72xxxxxxx, 99xxxxxxx rok urodzenia 1972 czy 1999, później nieco innaczej, dlatego przedrostek to 1900

        else:
            pre = 2000                                                                  #żeby nie doszło do powtórek peseli po 2000 roku do miesiąca urodzenia dodaje się 20, dlatego my musimy pamiętać o odjęciu tej wartości
            month -= 20

        year = pre + year                                                              #ostateczny rok to suma przedrostka i daty wyciągniętej z numeru pesel np. 72xxxxx -> 1900 + 72 = 1972
        #print("Data urodzenia to:", day, ".", month, ".", year)
        self.date_of_S_bday = datetime.datetime(year, month, day,0,0,0,0)              #tworzymy obiekt klasy datetime (dzień urodzin student) (moment w czasie, lata, miesiące, dni, godziny, sekundy, milisekundy)
        now = datetime.datetime.now()                                                  #tworzymy obiekt tej samej klasy (aktualny czas)
        diff = relativedelta(now, self.date_of_S_bday)                                 #różnicę realizujemy za pomocą funkcji relativedelta z klasy dateuil (diff też jest obiektem)
        self.age = int(diff.years)                                                          #używając .years, 'wyciągamy' różnicę w latach z obiektu relativedelta






# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    platform_1 = platform()
    again = "Y"
    #sterowanie
    print('\n\n\n#############################################################')
    while(again == "Y"):
        choose_wisely = input("Co chcesz zrobić: polecenie "
                              "\nWyświetl wszystko: /all "
                              "\nWyświetl studentów alfabetycznie po mailu: /sort_S_mail"
                              "\nWyświetl studentów po wieku: /sort_S_age"
                              "\nWyświetl nauczycieli alfabetycznie po mailu: /sort_T_mail"
                              "\nWyświetl kursy dla semestru, który poda użytkownik: /get_C_sem"
                              "\nDodaj oceny studentom: /add_S_marks"
                              "\nDodaj nowy kurs: /add_C"
                              "\nDodaj nowego studenta : /add_S"
                              "\nDodaj nowego nauczyciela : /add_T"
                              "\nPoclicz i wyświetl średnią całej platofrmy (po stuedntach) : /avg_P"
                              "\nPoclicz i wyświetl średnią wysztkich studentów z osobna :/avg_all_S"
                              "\nPoclicz i wyświetl średnią jednego studenta (po PESELU) : /avg_S"
                              "\nPoclicz i wyświetl średnią jednego kursu (po nazwie) : /avg_C"
                              "\nPodaj polecenie:\n")

        if choose_wisely == "/all":
            platform_1.get_data_platform()
        elif choose_wisely == "/add_T":
            platform_1.Teachers.append(teacher)
        elif choose_wisely == "/add_C":
            platform_1.Courses.append(course)
        elif choose_wisely == "/add_S":
            platform_1.Students.append(student)
        elif choose_wisely == "/sort_S_mail":
            platform_1.sort_Students_alphabetical_mail()
        elif choose_wisely == "/sort_S_age":
            platform_1.sort_Students_by_age()
        elif choose_wisely == "/sort_T_mail":
            platform_1.sort_Teachers_alphabetical_mail()
        elif choose_wisely == "/get_C_sem":
            platform_1.get_courses_by_semestr()
        elif choose_wisely == "/add_S_marks":
            platform_1.add_marks_of_Students()
        elif choose_wisely == "/avg_P":
            platform_1.get_avarge_grade_of_platofrm()
        elif choose_wisely == "/avg_all_S":
            platform_1.get_avarge_grade_of_Students()
        elif choose_wisely == "/avg_S":
            platform_1.get_avarage_grade_of_student()
        elif choose_wisely == "/avg_C":
            platform_1.get_avarage_of_course()
        else:
            print("Błąd")
        again = input("Jeśli chcesz kontynuować, podaj Y, jeśli nie coś innego\n")
    print('\n\n\n#############################################################')




#LEGENDA
#tablice obiektów nazywam dużą literą np. Students
#pojedyncze obiekty np. w pętlach nazywam jedną dużą literą (pierwszą z nazwy tablicy tych obiektów) np. S dla Students
#symbole --------------- oddzielają dwa obiekty od siebie
#symbole +++++++++++++++ oznaczają początek i  zakońćzenie działania funkcji
#sybole ################ początek i koniec programu


 #dodawanie ocen konstruktor
