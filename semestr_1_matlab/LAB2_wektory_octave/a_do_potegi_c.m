clear
a = input("Podaj a: ");
calkowita = true;
do
  c = input("Podaj c: ");
  if(c - floor(c) <= 0)
    calkowita = true;
  else
    printf("Podana liczba powinna byc calkowita. Podaj liczbe ponownie\n");
    calkowita = false;
  endif
until(calkowita == true);
if(a != 0)
  wynik = 1;
  if(c == 0)
    printf("a^c = %f", 1);
  elseif(c > 0)
    for(i=1:c)
      wynik = wynik*a;
    endfor
  printf("a^c = %f", wynik);
  elseif(c < 0)
    c = -c;
    disp(c)
    for(i=1:c)
      wynik = wynik*a;
    endfor
    wynik = 1/wynik;
    printf("a^c = %f", wynik);
  endif
elseif(a == 0 && c==0)
  printf("a^c = niezdefiniowany");
else
  printf("a^c = niezdefiniowany");
endif
