clear
clc %czyszczenie okna poleceñ
obrazek = imread('jablka.png'); %odczyt obrazka
obrazek = rgb2gray(obrazek); %konwersja na skalê szaroœci
wiadomosc = 'Wa¿na i niezwykle tajna wiadomosc'; %TU PODAJ WIADOMOŒÆ DO ZASZYFROWANIA
dl_wiadomosc = length(wiadomosc) * 8; %ka¿da litera z wiadomoœci zajmie 8 bitów 0-255
wiadomosc_ascii = double(wiadomosc); %konwersja na kod ascii
wiadomosc_binarnie = transpose(dec2bin(wiadomosc_ascii,8)); %konwersja na tablcê zawieraj¹c¹ liczby kodu ascii przeliczone na system binarny
wiadomosc_binarnie = wiadomosc_binarnie(:); %umieszczenie ka¿dej wartoœci binarnej w osobnym wierszu
dl_binarnie = length(wiadomosc_binarnie);
wiadmosc_binarna_liczbowo = str2num(wiadomosc_binarnie); %konwersja wiadomoœci z wersci tekstowej na liczbow¹
obrazek_zakodowany = obrazek; %najpierw oba obrazki s¹ takie same
%pobranie wymiarów obrazka 
wysokosc = size(obrazek,1);
szerokosc = size(obrazek,2);
licznik = 1; %licznik liczy ile bitów wiadomoœci ju¿ umieœciliœmy w obrazku
%Pêtla przejdzie przez cza³y obrazek wejœciowy
for (i=1:wysokosc)
  for(j=1:szerokosc)
    if(licznik<=dl_wiadomosc)
       najmniej_znaczacy_bit = mod(double(obrazek(i,j)),2); %znalezienie bitu który nas interesuje
       if(najmniej_znaczacy_bit == double(wiadmosc_binarna_liczbowo(licznik))) %jezeli ostatni bit i aktualny bit wiadomosci s¹ takie same zostawiamy 0
          dodaj = 0;
        else
          dodaj = 1; %je¿eli nie to 1
       endif
     endif
     obrazek_zakodowany(i,j) = obrazek_zakodowany(i,j) + dodaj; %zmiana ostatnich bitów w pikselach obrazka wyœciowego
     licznik = licznik + 1; %zwiêkszenie licznnika
  endfor
endfor
%lokalizacje zakodowanego i niezakodowanego pliku
imwrite(obrazek, 'wynik/niezakodowany.png');
imwrite(obrazek_zakodowany, 'wynik/zakodowany.png');
disp("zakodowano");
