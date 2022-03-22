clear
do
  n = input("Podaj dlugosc ciagu. Powinna byc liczba calkowita nieujemna: ");
until(n>=0 && n - floor(n) == 0)
tab = zeros(1,n);
if(n == 0)
  tab(1) = 0;
elseif(n == 1)
  tab(1) = 0;
  tab(2) = 1;
else
  tab(1) = 0;
  tab(2) = 1;
  for(i=3:n)
    tab(i) = tab(i-2) + tab(i-1);
  endfor
endif
printf("Poniszy wektor zawiera kolejne elemnty ciagu Fibonacciego dla podanego n \n");
disp(tab);
