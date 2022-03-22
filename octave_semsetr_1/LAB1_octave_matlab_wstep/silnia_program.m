clear
n = input('Podaj n: ' );
if (n < 0 || n - floor(n) > 0)
  fprintf('Liczba n powinna byc liczba naturalna lub 0', n);
elseif (n == 0)
  fprintf('Wartosc silnii dla n = %d wynosi z definicji 1', n);
elseif (n >= 1)
  silnia = 1;
  for (i=1:1:n)
    silnia = silnia * i;
  end
  fprintf('Silnia dla n = %d wynosi %d', n, silnia);
endif
