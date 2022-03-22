clear
wier = input("Podaj liczbe wierszy: ");
kol = input("Podaj liczbe kolumn: ");
x = zeros(wier,kol);
for(i=1:wier)
  for(j=1:kol)
    x(i,j) = input('Podaj liczbe');
  end
end
disp(x);