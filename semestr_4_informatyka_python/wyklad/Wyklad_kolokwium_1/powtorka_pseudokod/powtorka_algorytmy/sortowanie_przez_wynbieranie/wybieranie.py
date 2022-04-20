
import random

def sortowanie_wybieranie(n, d):
    print(n)
    for j in range(0, n, 1): #podaje się od jakiej wartości ma zacząć liczyć i ILE RAZY POWTÓRZYC, i potem o ile zmienić
        print(j)
        p_min = j
        for i in range (j+1, n, 1):
            if d[i] < d[p_min]:
                p_min = i
        pom = d[j]
        d[j] = d[p_min]
        d[p_min] = pom
    return d





# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   n = 50
   d = []
   for i in range (n):
       d.append(random.randint(10, 99)) # python indeksuje od 0 do n-1, pseudokod 1 do n
   print("Przed sortowaiem: ", d)
   d = sortowanie_wybieranie(n, d)
   print("Po sortowaniu: ", d)






#n - ilość elemntów
#A[] - lista, która ma być posortowana niemalejąca

# Algorytm sortujący listę n-elemntową listę A, metodą wybierania.



