clear
function [X,Y] = funkcja_dodaj_odejmij(A,B)
  %X - suma wej�cia, Y-r�nica wyj�cia
  X = A+B
  %return
  Y=A-B;
endfunction
A = input("Podaj A: ");
B = input("Podaj B: ");
[X,Y] = funkcja_dodaj_odejmij(A,B);
fprintf("Suma %f, r�nica %f:", X, Y);