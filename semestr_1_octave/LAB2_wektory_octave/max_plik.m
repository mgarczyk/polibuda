clear
x = input('Podaj wektor: ');
n = length(x);
max = x(1); %wektor numerujemy od 1
indeks = 1;
for(i=2:n)
  if (x(i) > max)
     max = x(i);
     indeks = i;
  end
end
fprintf("Maksimum wynosi %f i jest na pozycji %d", max, i)