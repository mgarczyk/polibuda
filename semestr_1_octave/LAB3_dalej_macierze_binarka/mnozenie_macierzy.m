A = input("Podaj macierz A: ");
[wierA, kolA] = size(A);
B = input("Podaj macierz B: ");  
[wierB, kolB] = size(B);
if(kolA == wierB)
 C = (zeros(wierA, kolB));
 for(w=1:wierA)
  for(k=1:kolB)
    for(n=1:kolA)
     C(w,k) = C(w,k) + (A(w, n) + B(n,k));
    endfor
  endfor
 endfor
else
  printf("Nie zosta³ spe³niony warunek ¿e liczba kolumn macierzy A musi byæ równa liczbie wierszy z macierzy B")
endif