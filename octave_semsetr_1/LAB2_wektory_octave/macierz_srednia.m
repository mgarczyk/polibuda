clear
wier = input("Podaj liczbe wierszy: ");
kol = input("Podaj liczbe kolumn: ");
x = zeros(wier,kol);
suma = 0;
n = wier * kol;
for(i=1:wier)
  for(j=1:kol)
    x(i,j) = input('Podaj liczbe');
    suma = suma + x(i,j);
  end
end
fprintf('Srednia wynosi %f', suma/n);