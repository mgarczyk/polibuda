tab = input("Podaj macierz: ");
[wier, kol] = size(tab);
suma = 0;
wielkosc = wier*kol;
for (i=1:wier)
  for (j=1:kol)
    suma+=tab(i,j); 
  endfor
endfor
srednia = suma/wielkosc;
suma_wariancja = 0;
for (i=1:wier)
  for (j=1:kol)
    suma_wariancja+=power((tab(i)-srednia),2);
  endfor
endfor
wariancja = suma_wariancja/wielkosc;
printf("Wariancaj macierzy wynosi %f",wariancja);