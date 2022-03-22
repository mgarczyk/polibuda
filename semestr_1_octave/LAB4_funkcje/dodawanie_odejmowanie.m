clear
function [X,Y] = funkcja_dodaj_odejmij(A,B)
  %X - suma wejœcia, Y-ró¿nica wyjœcia
  X = A+B
  %return
  Y=A-B;
endfunction
A = input("Podaj A: ");
B = input("Podaj B: ");
[X,Y] = funkcja_dodaj_odejmij(A,B);
fprintf("Suma %f, ró¿nica %f:", X, Y);