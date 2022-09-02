


def licz(x):
    print("x: ", x)
    if x == 1:
        return 1
    else:
        w = licz(x // 2)  # rekurencja nowym x staje się x // 2 (// - dzielenie całkowite)
        print("w: ", w)
        if x % 2 == 1:    # jeżeli x jest nieparzyste zwróci w + 1
            return w + 1
        else:
            return w - 1   # jeżeli parzyste w - 1






# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    x = int(input("Podaj x: "))
    wynik = licz(x)
    print("Wynik to:", wynik)



# x - zmienna sterująca funkcją licz
# w - wynik działania funkcji licz

# Algorytm pozwala na wyznaczenie liczby całkowitej w, na podstawie podanej przez usera liczby całkowitej x.
# Działa on rekurencyjnie, aż kolejna z rzędu rekurencja nie zwróci wartości 1 co spowoduje 'zwinięcie się' drzewa
# rekurencji i zwrócenie wyniku. Kolejne nowe wartości zmiennej x, zależą od wyniku działania nowe_x = x // 2, gdzie //
# to operator dzielenia całkowitego
# Np. dla wartości x = 11:
# 1) Pierwsza rekurencja x = 5
# 2) Druga rekurencja x = 2
# 3) Trzecia rekurencja x = 1 -> zwraca w = 1,
# 2)Zatem w drugiej rekurencji w = 1, x = 2, zatem w = w - 1, w = 0
# 1)W pierwszej rekurencji w = 0, x = 5, zatem w = w + 1, w = 1
# Zatem ostetecznie w = 1, x = 11, zatem w = w + 1, w = 2, co zwraca funkcja.


