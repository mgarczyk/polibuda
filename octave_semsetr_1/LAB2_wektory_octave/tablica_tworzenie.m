clear
N = input('liczba elementow');
X = zeros(1,N); %stworzenie tablicy o danej ilosci elemnt�w
for (i=1:N) %p�tla do przechodzenia po tablicy
  X(i) = input('Podaj liczbe'); 
end
disp(X); 
   