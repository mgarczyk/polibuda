


def sort_bubble(n, T):
    for i in T:
       for j in range(1, n, 1):
           if T[j] > T[j - 1]:
               pom = T[j]
               T[j] = T[j - 1]
               T[j - 1] = pom
    return T




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    T = []
    for i in range (2,51,1):
        T.append(i)
    n = len(T)
    print(T)
    T = sort_bubble(n, T)
    print(T)



# T - tablica liczb całkowitych od 2 do 50
# n - ilość elemntów w tablicy T

# Jest to algorytm sortowania metodą bąbelkową, zauważamy to po dwóch pętalch typu for (złożoność O(n) = n^2 - kwadratowa)
# oraz po porównywaniu ze sobą i zamienianiu dwóch sąsiednich wartości z tablicy, pierwsza pętla przechodzi po całej tablicy,
# każdym elemncie, a druga podobnie, ale pomija pierwszy.

