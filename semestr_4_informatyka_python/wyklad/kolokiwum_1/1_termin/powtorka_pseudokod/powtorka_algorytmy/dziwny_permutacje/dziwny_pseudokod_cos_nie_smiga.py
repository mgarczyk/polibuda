
import random

def permutacja(C, P, PR, n):
    i = 0
    while i < n - 1: # indeksujemy od 0 do n-1, nie jak w pseudokodzie od 1 do n
        i = 0
        x = 0
        while C[i] == n - i:
            PR[i] = not PR[i]
            C[i] = 1
            if PR[i]:
                x = x + 1
            i = i + 1
        if i < x + 1:
            if PR[i]:
                k = C[i] + x
            else:
                k = n - i - C[i] + x
            P[k] = P[k+1]
            print(P)
            C[i] = C[i] + 1




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   C  = []
   P = []
   PR = []
   n = 10
   for i in range (n):
       P.append(i)
       C.append(1)
       PR.append(True)
   C[n-1] = 0
   print(P)
   print(C)
   print(PR)
   permutacja(C, P, PR, n)




#n - ilość elemntów
#P - kolejne permutacje emelentów

# Jest to algorytm generujący kolejne permutacje wartośći z tablicy P, z użyciem minimalnej liczby transpozycji, ale coś
# nie działa pewnie pseudokod źle przepisałem.


