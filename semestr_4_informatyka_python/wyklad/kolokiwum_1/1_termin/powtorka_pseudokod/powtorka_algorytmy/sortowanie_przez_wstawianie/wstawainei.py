
import random

def sort_instert(d, n):
    for j in range(n-2, -1, -1):  #UWAGA !!!! n - 1 to jest ostatni w python, bo indeksujemy od 0 do n - 1, a w pseudokodzie od 1 do n, zatem wszędzie gdzie zmienna n występuje, trzeba odjąć od niej 1 (w funkcji)
        x = d[j]
        i = j + 1
        while i <= n - 1 and x > d[i]:
            d[i-1] = d[i]
            i = i + 1
        d[i - 1] = x
    return d





# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    n = 50
    d = []
    for i in range(0, n, 1):
        d.append(random.randint(1, 100))
    print("Przed sortowaniem: ", d)
    d = sort_instert(d, n)
    print("Po sortowaniu: ", d)




# d[] - lista którą sortujemy
# n - ilość elemntów na sortowanej liście
# j - licznik pętli zewnętrznej for pozwalającej na wybór elemntu do wstawienia
# i - licznik pętli wewnętrznej while odpowiedzalnej za wybór miejsca na wstawienie j-tego elemntu

# Jest to algorytm sortowania przez wstawianie, pętla zewnętrzna przchodzi po liście od przedostatniego elemntu do początku,
# pętla wewnętrzna, wybiera miejsce w które należy wstawić j-ty element.


