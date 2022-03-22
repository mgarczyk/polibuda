clear
A = input("Podaj macierz: ");
[wier, kol] = size(A);
B = zeros(kol, wier); %tworzymy macierz wype³nion¹ zerami o wymairach macierzy odwrotnej do A
for(w=1:wier) %pêtla dotyczy wymiarów pierwszej maicerzy któr¹ chcemy transponowaæ
  for(k=1:kol)
    B(k,w) = A(w,k); %korzystamy z wymiarów pierwszej wiêc przypisujemy kolumnie i wierszowi w B wartosæ wiersza i kolumny z B
  endfor
endfor
disp(A);
disp(" ");
disp(B);