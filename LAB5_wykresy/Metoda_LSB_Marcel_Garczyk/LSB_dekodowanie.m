clear; 
clc; 
obrazek = imread('wynik/zakodowany.png'); %pobranie zakodowanego obrazka
%pobranie wymiar�w obrazka 
wysokosc = size(obrazek, 1); 
szerokosc = size(obrazek, 2); 
%Informacja ile znak�w zabiera ukryty tekst, je�li jej nie mamy i podamy warto�� wi�ksz� to wiadomo�� odkoduje si� lecz pojawi� si� niechcane
%znaki nie dotycz�ce naszej wiadomo�ci, je�eli podamy za ma�� warto�� cz�� wiadomo�� nie b�dzie widoczna.
znaki = 34;  %ustwione na stale do prawidlowego odszyfrowania mojej wiadomo��i 
%usu� znak komentwrza poni�ej by m�c wygodnie podawa� warto�� dla swojej wiadomo�ci.
%znaki = input('Podaj oczekiwan� d�ugo�� zakodoanej wiadomo��i. Wszelkie informacje w powy�szych komentarzu. ');
dlugosc_wiadomosci = znaki * 8;  %Ilo�� bit�w w wiadomo�ci
licznik = 1; %licznik zawiera informacj� o tym ile bit�w ju� odszfrowali�my
%P�tla przechodzi przez obarzek
for (i=1:wysokosc)
    for (j=1:szerokosc)
        if (licznik <= dlugosc_wiadomosci) 
            ostatnie_bity(licznik, 1) = mod(double(obrazek(i, j)), 2);  %Przechowujemy ka�dy ostatni bit w tablicy
            licznik = licznik + 1; 
        end
    end
end
wartosci_binarne = [ 128 64 32 16 8 4 2 1 ]; %maks 8 bit�w suma 255
%Przenosimy bity do 8 kolumnowej tablicy, w kt�rej ka�dy wiersz to bity reprezentuj�ce pojedynczy znak z ukrytej wiadomo�ci.
macierz_ostatnich_bitow = reshape(ostatnie_bity, 8, (dlugosc_wiadomosci/8)); %Przenosimy bity do 8 kolumnowej tablicy, w kt�rej ka�dy wiersz to bity reprezentuj�ce pojedynczy znak z ukrytej wiadomo�ci. 
%Konwersja ostatnich bit�w na tekst przez przemno�enie ich przez pot�gi dw�jki (zamiana na dziesi�tny i potem funkcja char odczytuje z warto�ci dziesi�tnej odpowiedni kod ascii danego znaku i ��cz�c poszczeg�lne znaki tworzy �r�d�ow� wiadomosc.
wiadomosc = char(wartosci_binarne*macierz_ostatnich_bitow);  
disp('Odkodwano');
fprintf('Oto odszyfrowana wiadomosc: %s', wiadomosc); 
