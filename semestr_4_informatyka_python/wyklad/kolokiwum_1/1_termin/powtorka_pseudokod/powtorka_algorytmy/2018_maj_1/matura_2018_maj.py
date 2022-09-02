

def matura_maj_2018(n):
    p = 1
    q = n
    while p < q:
        s = (p+q) // 2
        if s**3 < n:
            p = s + 1
        else:
            q = s
    return p



if __name__ == '__main__':
    while True:

        choose = input("Zadamia:"
                   "\n1 - matura maj 2018"
                   "\nPodaj zadanie: ")
        if choose == "1":
            while True:
                try:
                    n = int(input("Podaj parametr n: "))
                    break
                except ValueError:
                    print("Spróbij ponownie")
            p = matura_maj_2018(n)
            print('P wynosi: ', p)
        else:
            print("Błąd spróbuj ponownie")


# n - stała wartość liczbowa całkowita (startowy parametr algorytmu)
# p - wartość liczbowa wykorzystywana przy porównywaniu w pętli while oraz przy ustalaniu wartości zmiennej s
# q - kopia zmiennej n, zmieniana w czasie wykonwyania algorytmu (zmienna n steruje warunkiem wewnątrz pętli while nie może być zmieniana, potrzebujemy jej kopię)
# s - zmienna wykorzystywana w warunku wewnątrz pętli while, bezpośrednio od jej wartości zależą wartości zmiennych p i q w kolejnych krokach algorytmu

# Algorytm służy do wyznaczenia waretości zmiennej p, na podstawie podanego parametru n. (Nie robi chyba nic konkretnego, typu sprawdzanie parzystości, pierwszości liczby itp.)