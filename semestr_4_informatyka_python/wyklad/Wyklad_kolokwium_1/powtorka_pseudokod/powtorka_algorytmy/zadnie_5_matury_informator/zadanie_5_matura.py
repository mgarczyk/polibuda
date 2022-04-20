
import random

def sortowanie(n, A):
    for j in range(n-2, -1, -1):
        x = A[j]
        p = j
        k = n
        while k - p > 1:
            i = (p + k) // 2  #// - operator dzielenia całkowitego w pytonie
            if x <= A[i]:
                k = i
            else:
                p = i
        for i in range (j, p - 1, 1):
            A[i] = A[i+1]
        A[p] = x
    return A





# Press the green button in the gutter to run the script.
if __name__ == '__main__':
   n = 50
   A = []
   for i in range (n):
       A.append(random.randint(10, 99)) # python indeksuje od 0 do n-1, pseudokod 1 do n
   print("Przed sortowaiem: ", A)
   A = sortowanie(n, A)
   print("Po sortowaniu: ", A)







#n - ilość elemntów
#A[] - lista, która ma być posortowana niemalejąca

# Algorytm sortujący listę n-elemntową listę A i zwracjący ją.



