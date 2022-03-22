import numpy as np
import sympy
from IPython.display import display
def determinant_E(M):
    len_M = len(M) #wielkość macierz zakładamy że jest kwadratowa
    copy_M = np.copy(M) #kopia macierzy z danymi
    for fd in range (len_M): #fd elemnt z głównej przekątnej
        for i in range(fd+1, len_M): #wierze poniżej fd w tej samej kolumnie
            if copy_M[fd][fd] == 0:
                copy_M[fd][fd] = 1.0e-18 #problem dzielenia przez 0
            scaler = copy_M[i][fd] / copy_M[fd][fd]
            for j in range(len_M):
                copy_M[i][j] = copy_M[i][j] - scaler*copy_M[fd][j]
    det = 1.0
    display("Macierz górnotrójkątna: \n ", copy_M)
    for i in range(len_M):
        det*=copy_M[i][i] #iloczyn diagonalnej przekątnej
    return det

M = np.array(([1,2,1], [1,1,31], [1,3,1]))
display("Macierz oryginalna: \n ", M)
det_np = np.linalg.det(M)
#jak będzie blisko 0 to wypisze 0, a nie coś dziwnego
if np.allclose(det_np, 0):
    print(0.0)
else:
    print("Wyznacznik policzony przy pomocy numpy: ", det_np)

det = determinant_E(M)
print ("Wyznacznik macierzy policzony bez użycia numpy: ", det)


# 1)Dla każdego wiersza poniżej wiersza zawierającego fd tworzymy przelicznik równy (element w wierszu, który jest w tej samej kolumnie co fd ) podzielony przez ( fd ).
# 2)Aktualizujemy każdy wiersz poniżej wiersza z fd za pomocą (bieżący wiersz) – skaler * (wiersz z fd w nim).
# 3)Spowoduje to przesunięcie elementów w każdym wierszu poniżej fd do 0.
# 4)Kiedy przechodzimy do następnego fd , musimy tylko powtórzyć te kroki dla wierszy poniżej wiersza z bieżącym fd .
#Gdy macierz jest w postaci górnego trójkąta, wyznacznikiem jest po prostu iloczyn wszystkich elementów na głównej przekątnej.

