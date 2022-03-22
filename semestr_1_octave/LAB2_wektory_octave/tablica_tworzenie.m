clear
N = input('liczba elementow');
X = zeros(1,N); %stworzenie tablicy o danej ilosci elemntów
for (i=1:N) %pêtla do przechodzenia po tablicy
  X(i) = input('Podaj liczbe'); 
end
disp(X); 
   