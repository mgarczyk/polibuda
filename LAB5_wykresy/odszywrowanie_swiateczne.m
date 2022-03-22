clear

function wynik = czarny_bialy(element_obrazu) %przelicznie, sprawdzenie iloœci jedynek i czy jest parzysta czy nie zapisanie do obrazka wynikowego
  element_binarnie = zeros(1, 8); %wektor przechwuj¹cy aktualn¹ wartoœæ binarn¹ 8 to maksymalna liczba bitów by zapisaæ ka¿d¹ liczbê z obrazka 255 to 8 jednyek
  element_binarnie = dec2bin(element_obrazu);
  licznik = 0; %iloœæ jedynek
  dl_binarnie = length(element_binarnie); %gdyby dlugosc by³a mniejsza ni¿ 8 bitów
  for(i=1:dl_binarnie)
    if(element_binarnie(i) == 49) %po u¿yciu fukcnji dec2bin wartoœæi w wektroze s¹ typu string, a w ASCII jedynce jest przypiany kod 49
      licznik=licznik+1;
    endif
  endfor
  if(mod(licznik,2) == 0)
    wynik = 255;
  else
    wynik = 0;
  endif
endfunction

obraz = imread("zakodowany.gif"); %wczytanie obrazka
[wier, kol] = size(obraz);
wynik = zeros(wier, kol);
for(w=1:wier)
  for(k=1:kol)
    wynik(w,k) = czarny_bialy(obraz(w,k));
  endfor
endfor
disp(wynik);
imshow(wynik); %wypisanie oprazka
imwrite(wynik,'odkodowany.jpg','jpg')