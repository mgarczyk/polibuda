clear
x = input('Podaj macierz:' ) %[1,2,3; 2,4,5] 
[wier, kol] = size(x);
suma = 0;
n = wier * kol;
for(i=1:wier)
  for(j=1:kol)
    suma = suma + x(i,j);
  end
end
fprintf('Srednia wynosi %f', suma/n);