# This is a sample Python script.
import random
import sys

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def zadanie_4_podstawy_podstaw():
    width = 17
    height = 12.0
    print("Type width: ", type(width))
    print("Type height: ", type(height))
    print("1: ", type(width//2)) # dzielenie całkowite
    print("2: ", type(width/2.0)) # dzielenie zmiennoprzecinkowe
    print("3: ", type(height/3)) # dzielenie zmiennoprzecinkowe
    print("4: ", type(1 + 2 * 5)) # dzielenie zmiennoprzecinkowe


def zadanie_5_podstawy_podstaw():
    celcius = float(input("Podaj temperaturę w °C: "))
    farenheit  = ((celcius * 9)/5) + 32
    print("Temeperatura w stopniach Farenheita wynosi: ", farenheit, " °F")


def zadanie_1_warunki():
    print("Warunki: ZADANIE 1")
    rate = float(input("Podaj stawkę: "))
    number_of_hours = int(input("Podaj liczbę godzin: "))
    if number_of_hours<=40:
        salary = number_of_hours * rate
    else:
        overtime = number_of_hours - 40
        salary = 40*rate + overtime * rate * 1.5
    print(salary)


def zadanie_2_warunki_6_funkcje(number_of_hours, rate):
    if number_of_hours <= 40:
        salary = number_of_hours * rate
    else:
        overtime = number_of_hours - 40
        salary = 40*rate + overtime * rate * 1.5
    return salary


def zadanie_3_warunki_7_funkcje(value):
    if value >= 0.9:
        mark = 5.0
    elif value >= 0.8:
        mark = 4.5
    elif value >= 0.7:
        mark = 4.0
    elif value >= 0.6:
        mark = 3.5
    elif value >= 0.5:
        mark = 3.0
    else:
        mark = 2.0
    return mark


def zadanie_1_funkcje():
    # generowanie liczb pseudolosowych z zakresu od 0.0 do 1.0 (bez 1)
    print("\nZmiennoprzecinkowe: ")
    for i in range (10):
        x = random.random()
        print(x)

    print("\nCałkowite: ")
    # generowanie liczb pseudolosowych z zakresu od 1 do 5 (bez 1)
    for i in range (10):
        x = random.randint(1, 5)
        print(x)

    print("Funkcja jest jakby zmienną typu funkcja, ciekawe: ", type(zadanie_1_funkcje))


def zadanie_1_petle():
    print("Pętle: ZADANIE 1")
    sum = 0
    counter = 0
    print("\nPodawaj liczby całkowite, jeśli chcesz kontynuować to w odopowiednim momencie podaj polecenie gotowe")
    while True:
        number = input("Podaj liczbę: ")
        try:
            if number == "gotowe":  # jeśli podano gotowe kończymy
                break
            else:
                number = float(number)  # w innym wypadku próbujemy konwertować, jak się nie uda wyskakuje błąd ValueError i powtórka
                sum += number
                counter += 1

        except ValueError:
            print("Błąd spróbuj ponownie")
    print(sum, " ", counter, " ", sum/counter)


def zadanie_2_petle():
    print("Pętle: ZADANIE 2")
    largest = None
    smallest = None
    print("\nPodawaj liczby całkowite, jeśli chcesz kontynuować to w odopowiednim momencie podaj polecenie gotowe")
    while True:
        number = input("Podaj liczbę: ")
        try:
            if number == "gotowe":  # jeśli podano gotowe kończymy
                break
            else:
                number = float(number) # w innym wypadku próbujemy konwertować, jak się nie uda wyskakuje błąd ValueError i powtórka
                if largest is None or largest < number:
                    largest = number
                if smallest is None or smallest > number:
                    smallest = number
        except ValueError:
            print("Błąd spróbuj ponownie")
    print("Najwieksza: ", largest, " ", "Najmniejsza: ", smallest)


def zadanie_1_znaki():
    text = str(input("Podaj tekst: "))
    length = len(text)
    i = length - 1
    while i >= 0:
        print(text[i])
        i -= 1

def zadanie_2_znaki():
    text = 'fruit'
    print(text[:])

def zadanie_3_znaki(word, letter):
    count = 0
    for L in word:
        if L == letter:
            count += 1
    return count


def zadanie_5_znaki():
    text = 'X_DSPAM_Confidence: 0.8475'  # tekst do parsowania
    colon = text.find(':')  # znajdujemy pozycję dwukropka
    value = float(text[colon+1::])  # konwertujemy na float tekst dalej o jeden znak od tego co po dwukropku (nie bezpośrednio, bo po samym dwukropku jest spacja, której nie da się skonwertować)
    print(value)


def fred():
    print("Zap")

def jane():
    print("ABC")




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    while True:
        print("Podaj numer zadania:"
              "\n1 - zadanie_4_podstawy_podstaw"
              "\n2 - zadanie_5_podstawy_podstaw"
              "\n3 - zadanie_1_warunki"
              "\n4 - zadanie 2 warunki i 6 funkcje"
              "\n5 - zadanie 3 warunki i 7 petle w jednym"
              "\n6 - zadanie_1_funkcje"
              "\n7 - zadanie_ 5_funkcje"
              "\n8 - zadanie_1_petle"
              "\n9 - zadanie_2_petle"
              "\n10 - zadanie_1_znaki"
              "\n11 - zadanie_2_znaki"
              "\n12 - zadanie_3_znaki"
              "\n13 - zadanie_4_znaki"
              "\n14 - zadanie_5_znaki"
              "\n-1 - zakończ"
              "\nPodaj numer polecenia: ")
        while True:
            try:
                value = int(input("Wybierz polecenie: "))
                break
            except ValueError:
                print("Bład przy wyborze")


        if value == 1:
            zadanie_4_podstawy_podstaw()
        elif value == 2:
            zadanie_5_podstawy_podstaw()
        elif value == 3:
            zadanie_1_warunki()
        elif value == 4:
        #zadanie 2 warunki i 6 funkcje
            print("Warunki: ZADANIE 2")
            while True:
                try:
                    rate = float(input("Podaj stawkę: "))
                    break
                except ValueError:
                    print("Podano dane nienumeryczne, podaj ponownie")
            while True:
                try:
                    number_of_hours = int(input("Podaj liczbę godzin: "))
                    break
                except ValueError:
                    print("Podano dane nienumeryczne, podaj ponownie")
            salary = zadanie_2_warunki_6_funkcje(number_of_hours, rate)
            print(salary)
        elif value == 5:
        #zadanie 3 warunki i 7 petle w jednym
            while True:
                try:
                    value = float(input("Podaj wartość wyniku: "))
                    if value<0 or value>1:
                        raise ValueError
                    else:
                        break
                except ValueError:
                    print("Podano nieprawidłowe dane, spróbuj ponownie.")
            mark = zadanie_3_warunki_7_funkcje(value)
            print(mark)
        elif value == 6:
            zadanie_1_funkcje()
        elif value == 7:
        #zadanie_ 5_funkcje
            jane()
            fred()
            jane()
        elif value == 8:
            zadanie_1_petle()
        elif value == 9:
            zadanie_2_petle()
        elif value == 10:
            zadanie_1_znaki()
        elif value == 11:
            zadanie_2_znaki()
        elif value == 12:
            word = str(input("Podaj słowo: "))
            letter = str(input("Podaj znak: "))
            count = zadanie_3_znaki(word, letter)
            print(f"Znak {letter} wystąpił w słowie {word} {count} razy")
        elif value == 13:
            word = str(input("Podaj słowo: "))
            letter = str(input("Podaj znak: "))
            count = word.count(letter)
            print(f"Znak {letter} wystąpił w słowie {word} {count} razy")
        elif value == 14:
            zadanie_5_znaki()
        elif value==-1:
            print("Koniec.")
            sys.exit()
        else:
            print("Blad")


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
