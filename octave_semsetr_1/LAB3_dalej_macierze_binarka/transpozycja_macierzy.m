clear
A = input("Podaj macierz: ");
[wier, kol] = size(A);
B = zeros(kol, wier); %tworzymy macierz wype�nion� zerami o wymairach macierzy odwrotnej do A
for(w=1:wier) %p�tla dotyczy wymiar�w pierwszej maicerzy kt�r� chcemy transponowa�
  for(k=1:kol)
    B(k,w) = A(w,k); %korzystamy z wymiar�w pierwszej wi�c przypisujemy kolumnie i wierszowi w B wartos� wiersza i kolumny z B
  endfor
endfor
disp(A);
disp(" ");
disp(B);