clear
clc %czyszczenie okna polece�
obrazek = imread('jablka.png'); %odczyt obrazka
obrazek = rgb2gray(obrazek); %konwersja na skal� szaro�ci
wiadomosc = 'Wa�na i niezwykle tajna wiadomosc'; %TU PODAJ WIADOMO�� DO ZASZYFROWANIA
dl_wiadomosc = length(wiadomosc) * 8; %ka�da litera z wiadomo�ci zajmie 8 bit�w 0-255
wiadomosc_ascii = double(wiadomosc); %konwersja na kod ascii
wiadomosc_binarnie = transpose(dec2bin(wiadomosc_ascii,8)); %konwersja na tablc� zawieraj�c� liczby kodu ascii przeliczone na system binarny
wiadomosc_binarnie = wiadomosc_binarnie(:); %umieszczenie ka�dej warto�ci binarnej w osobnym wierszu
dl_binarnie = length(wiadomosc_binarnie);
wiadmosc_binarna_liczbowo = str2num(wiadomosc_binarnie); %konwersja wiadomo�ci z wersci tekstowej na liczbow�
obrazek_zakodowany = obrazek; %najpierw oba obrazki s� takie same
%pobranie wymiar�w obrazka 
wysokosc = size(obrazek,1);
szerokosc = size(obrazek,2);
licznik = 1; %licznik liczy ile bit�w wiadomo�ci ju� umie�cili�my w obrazku
%P�tla przejdzie przez cza�y obrazek wej�ciowy
for (i=1:wysokosc)
  for(j=1:szerokosc)
    if(licznik<=dl_wiadomosc)
       najmniej_znaczacy_bit = mod(double(obrazek(i,j)),2); %znalezienie bitu kt�ry nas interesuje
       if(najmniej_znaczacy_bit == double(wiadmosc_binarna_liczbowo(licznik))) %jezeli ostatni bit i aktualny bit wiadomosci s� takie same zostawiamy 0
          dodaj = 0;
        else
          dodaj = 1; %je�eli nie to 1
       endif
     endif
     obrazek_zakodowany(i,j) = obrazek_zakodowany(i,j) + dodaj; %zmiana ostatnich bit�w w pikselach obrazka wy�ciowego
     licznik = licznik + 1; %zwi�kszenie licznnika
  endfor
endfor
%lokalizacje zakodowanego i niezakodowanego pliku
imwrite(obrazek, 'wynik/niezakodowany.png');
imwrite(obrazek_zakodowany, 'wynik/zakodowany.png');
disp("zakodowano");
