clear; 
clc; 
obrazek = imread('wynik/zakodowany.png'); %pobranie zakodowanego obrazka
%pobranie wymiarów obrazka 
wysokosc = size(obrazek, 1); 
szerokosc = size(obrazek, 2); 
%Informacja ile znaków zabiera ukryty tekst, jeœli jej nie mamy i podamy wartoœæ wiêksz¹ to wiadomoœæ odkoduje siê lecz pojawi¹ siê niechcane
%znaki nie dotycz¹ce naszej wiadomoœci, je¿eli podamy za ma³¹ wartoœæ czêœæ wiadomoœæ nie bêdzie widoczna.
znaki = 34;  %ustwione na stale do prawidlowego odszyfrowania mojej wiadomoœæi 
%usuñ znak komentwrza poni¿ej by móc wygodnie podawaæ wartoœæ dla swojej wiadomoœci.
%znaki = input('Podaj oczekiwan¹ d³ugoœæ zakodoanej wiadomoœæi. Wszelkie informacje w powy¿szych komentarzu. ');
dlugosc_wiadomosci = znaki * 8;  %Iloœæ bitów w wiadomoœci
licznik = 1; %licznik zawiera informacjê o tym ile bitów ju¿ odszfrowaliœmy
%Pêtla przechodzi przez obarzek
for (i=1:wysokosc)
    for (j=1:szerokosc)
        if (licznik <= dlugosc_wiadomosci) 
            ostatnie_bity(licznik, 1) = mod(double(obrazek(i, j)), 2);  %Przechowujemy ka¿dy ostatni bit w tablicy
            licznik = licznik + 1; 
        end
    end
end
wartosci_binarne = [ 128 64 32 16 8 4 2 1 ]; %maks 8 bitów suma 255
%Przenosimy bity do 8 kolumnowej tablicy, w której ka¿dy wiersz to bity reprezentuj¹ce pojedynczy znak z ukrytej wiadomoœci.
macierz_ostatnich_bitow = reshape(ostatnie_bity, 8, (dlugosc_wiadomosci/8)); %Przenosimy bity do 8 kolumnowej tablicy, w której ka¿dy wiersz to bity reprezentuj¹ce pojedynczy znak z ukrytej wiadomoœci. 
%Konwersja ostatnich bitów na tekst przez przemno¿enie ich przez potêgi dwójki (zamiana na dziesiêtny i potem funkcja char odczytuje z wartoœci dziesiêtnej odpowiedni kod ascii danego znaku i ³¹cz¹c poszczególne znaki tworzy Ÿród³ow¹ wiadomosc.
wiadomosc = char(wartosci_binarne*macierz_ostatnich_bitow);  
disp('Odkodwano');
fprintf('Oto odszyfrowana wiadomosc: %s', wiadomosc); 
