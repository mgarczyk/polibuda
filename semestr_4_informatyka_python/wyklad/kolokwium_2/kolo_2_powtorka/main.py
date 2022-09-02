# This is a sample Python script.
import math
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def spam_confidence():
    filename = str(input("Podaj nazwe pliku: "))
    suma = 0
    licznik = 0
    with open(filename, "r") as plik:
       for line in plik:
          if "X-DSPAM-Confidence" in line:
             print(line)
             print(float(line[-7:-1]))
             suma += float(line[-7:-1])
             licznik += 1
       print("Średni poziom pewności spamu: ", suma/licznik)
       plik.close()

def romeo_words():
    words = []
    with open('romeo.txt', "r") as romeo:
        for line in romeo:
            for word in line.split():
                if not word in words:
                    words.append(word)
        romeo.close()
    words.sort()
    print(words)

def min_max():
    list = []
    while True:
        try:
            data = str(input("Wprowadź liczbę: "))
            if data == 'gotowe':
                break
            elif not data.isnumeric():
                raise ValueError
            list.append(int(data))
        except ValueError:
            print("Podaneo nieprawidłowe dane.")
    print(f"Wartość największa to {max(list)}")
    print(f"Wartość najmniejsza to {min(list)}")


def who_send_the_mail():
     emails = []
     with open('mbox-short.txt') as data:  # otwieramy plik
         for line in data:   # przechodzimy go linia po linii
             if line.startswith("From:"):  # szukamy linii zaczynających się na From:
                 words = line.split()  # dzielimy linię na słowa
                 emails.append(words[1]) # indeksujemy od 0, zatem drugie słowo to nasz szulkany email, który dodajemy do listy
         data.close()
         print(emails)


def python_sets():
    # zbiór towrzymy za pomocą set(element_iterowalny),czyli np. [l, i, s, t, a], string, {'slow', 'nik'} lub krotka, elementy zbioru nie mogą się powtarzać

    x = set() # zbiór pusty
    x  = set('siema')
    x = {1,2,3}
    print("x: ", x)
    y = {3,4,5}
    print("y: ", y)
    # suma zbiorow
    print("Suma: ", x.union(y))  # suma czyliu wszystko
    # roznica zbiorow
    print("Różnica: ", x.difference(y)) # róznica, czyli to co jest w pierwszym bez tego co w drugim
    print("Iloczyn: ", x.intersection(y))  # to co jest w tym i w tym
    print("Symetryczna różnica: ", x.symmetric_difference(y))  # to czego nie ma w tym i w tym (jak w obu jest 3, to tutaj nie wypisze tej trójki)
    mroz = frozenset([1, 2, 3])
    print("Frozenset: ", mroz)
    set_1 = {3, 4, 5}
    mroz &= set_1  # w teorii nie możemy zmienić naszego zamrożonego zbioru, ale... tu pod tą samą nazwą powstanie inny zbiór, czyli ten sam zostaje jakby nadpisany
    print(mroz)

def emails_days_of_week():
    days = {}
    with open('mbox-short.txt', "r") as data:
        for line in data:
            words = line.split()  # dzielimy na słowa
            if len(words)  > 0 and words[0] == 'From': # jeżeli tablica nie jest pusta i zaczyna się do From, bez dwukropka to liczymy
                if words[2] not in days: # jeżeli dany dzień (jego nazwa to trzecie słowo w każdej linii) nie jest zapisany w słowniku
                    days[words[2]] = 1  # to ustaw jego wartość na 1, wystąpił pierwszy raz
                else:
                    days[words[2]] += 1 # w innym przypadku po prostu dodaj jeden (nazwa dnia tyogodnia to klucz słownika)
        data.close()
    print(days)

def number_of_emails_by_names():
    names = {}
    with open ('mbox-short.txt', "r") as data:
        for line in data:
            if line.startswith('From:'): # zauważamy że jeżeli linia zaczyna się od From:  to jest tam informacja od kogo mail przyszedł
                words = line.split()  # dzielimy na słowa
                email_name = words[1] # jako drugie słowo w linii jest email
                names[email_name] = names.get(email_name, 0) + 1  # ciekawa konstrukcja z książk, działa tak samo jak if w not in days w funkcji wyżej, jeżeli danego maila nie ma w słowniku to zostanie dodany jako klucz i przypisana mu będzie wartość 1
        data.close()
    print(names)
    print(f"Najwięcej maili otrzymano od, {max(names, key=names.get)}")


def number_of_emails_by_domain():
    domains = {}
    with open ('mbox-short.txt', "r") as data:
        for line in data:
            if line.startswith('From:'): # zauważamy że jeżeli linia zaczyna się od From:  to jest tam informacja od kogo mail przyszedł
                words = line.split()  # dzielimy na słowa
                email_name = words[1] # jako drugie słowo w linii jest email
                domain_name = email_name[email_name.find("@")+1:] # a tu jaka sztuczka, bierzemy część słowa, za indeksem na którym jest @, czyli nazwę domeny
                if domain_name not in domains:
                    domains[domain_name] = 1
                else:
                    domains[domain_name] += 1

              # ciekawa konstrukcja z książk, działa tak samo jak if w not in days w funkcji wyżej, jeżeli danego maila nie ma w słowniku to zostanie dodany jako klucz i przypisana mu będzie wartość 1
        data.close()
    print(domains)


def number_of_emails_krotki():
    slownik_emaili = {}
    with open("mbox-short.txt", "r") as data:
        for line in data:
            words = line.split()
            if len(words) > 0 and words[0] == 'From':
               email = words[1]
               if not email in slownik_emaili:
                   slownik_emaili[email] = 1
               else:
                   slownik_emaili[email] += 1
        data.close()
    # krotki
    lista_krotek = []
    for key, value in slownik_emaili.items():  # czytamy klucz - wartość
        lista_krotek.append((value, key)) # na listę dodajemy w postaci [(wartosc, klucz)], sortujemy po pierwszym elemncie krotki
    print(slownik_emaili)
    print()
    print(lista_krotek)
    lista_krotek.sort(reverse=True)
    print(f"Osoba która wysłała najwięcej emaili: {lista_krotek[0]}")


def emails_hours():
    slownik_godzin = {}
    with open("mbox-short.txt", "r") as data:
        for line in data:
            words = line.split()
            if len(words) > 0 and words[0] == 'From':
                timestamp = words[5]
                hour = timestamp[0:timestamp.find(':')]  # wyciągamy godzinę, cała informacja o czasie to 5 słowo w naszej linii my szukamy od początku do pierwszego :
                # print(hour)
                if not hour in slownik_godzin:  # ZAPSIUEMY W SŁOWNIk, kluczem jest godzina, a my zliczamy ilość wystąpień
                    slownik_godzin[hour] = 1
                else:
                    slownik_godzin[hour] += 1
        data.close()
    lista_krotek = []  # tworzymy liste krtotek
    for key, value in slownik_godzin.items():
        lista_krotek.append((key, value))
    lista_krotek.sort() # sortujemy
    for K in lista_krotek:
        print(K[0], " ", K[1]) # wypsiujemy


x=[-1,4,9,14,19]
wo=0
p=[0.977,0.008,0.008,0.006,0.001]
for i in range(len(x)):
    wo=wo+(p[i] * x[i])
var=0
for i in range(len(x)):
    var=var+(((x[i]-wo)**2) * p[i])
od=math.sqrt(var)

print(var)
print(od)
print(wo)



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   # spam_confidence()
   # romeo_words()
   # min_max()
   # who_send_the_mail()
   # python_sets()
   # emails_days_of_week()
   # number_of_emails_by_names()
   # number_of_emails_by_domain()
   # number_of_emails_krotki()
   check()


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
