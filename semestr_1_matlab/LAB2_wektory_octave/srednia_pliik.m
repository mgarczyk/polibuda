clear
n = input("Podaj liczbe elemntow: ")
x = zeros(1,n);
suma = 0;
for(i=1:n)
  x(i) = input("Podaj liczbe: ");
  suma = suma + x(i);
end
srednia = suma/n;
fprintf("Srednia wynosi %.3f", srednia);