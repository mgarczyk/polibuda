


def nwd_f(a,b):
    if a > b:
        k = b
    else:
        k = a
    while not (a % k == 0 and b % k == 0):
        k = k - 1
    return k






# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    a = int(input("Podaj perwszą liczbę: "))
    b = int(input("Podaj drugą liczbę: "))
    nwd = nwd_f(a, b)
    print("Nwd to: ", nwd)



# a - pierwsza liczba całkowita za pomocą któej wyznaczamy nwd
# b - druga liczba całkowita za pomocą któej wyznaczamy nwd
# k - zmienna przechowująca wynik działanai funkcji, czyli nwd liczb a i b

# Jest to algorytm pozwalający wyznaczyć NWD, dwóch liczb całkowitych a i b.


