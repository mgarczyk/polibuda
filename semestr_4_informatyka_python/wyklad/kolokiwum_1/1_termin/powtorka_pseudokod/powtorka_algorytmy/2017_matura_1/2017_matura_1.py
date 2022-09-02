


def sitko(n):
    Czyjest = []
    for i in range(0, n, 1):
        Czyjest.append(False)
    j = 1
    while j*j < n:
        j = j+1
    for i in range (2, j, 1):
        kw = i*i
        poz = kw
        while poz <= n:
            Czyjest[poz] = True
            poz = poz + kw
    return Czyjest





# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   n = int(input("Podaj liczbę całkowitą: "))
   Czyjest = sitko(n)
   print(Czyjest[9])



# T - tablica liczb całkowitych od 2 do 50
# n - ilość elemntów w tablicy T
# i - licznik pozwalający przejść przez wszytkie elementy
# poz - zmienna pozwalająca wyznaczyć pozycję liczb w tablicy i przypisać wartość True

# Jest to algorytm pozwalający sprawdzić które liczby z przedziału od 1 do n są pierwsze,
# w wyniku otrzymujemy tablicę, gdzie dla indeksów od 0 do n-1 sa przypisane koljene liczby całkowite od 1 do n
# np. indeks 0 oznacza wartość liczbową 1, do każdego indeksu są przypisane wartośći True lub False oznaczające czy
# dana liczba jest pierwsza czy nie, jak jest to False, jak nie to True, np. wartość liczbowa 10 jest 'przypisana' indeksowi 9,
# czyli do niego jest przypisana wartość True, bo 10 nie jest liczbą pierwszą.

