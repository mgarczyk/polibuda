clear
x = input('Podaj wektor: ');
n = length(x);
indeks_maks = 1; %maksimum = x(indeks_maks)
for(i=2:n)
  if (x(i) > x(indeks_maks))
    indeks_maks = i;
  end
end
fprintf('Maksimum wynosi x(%d) = %f', indeks_maks, x(indeks_maks))