clear
ulamek_dziesietny = input("Podaj ulamek w systemie dziesietnym: ");
liczba_bit = input("Podaj na ilu bitahc checesz zapisa� u�amek: ");
ulamek_dziesietny_kopia = ulamek_dziesietny;
ulamek_binarny = zeros(liczba_bit);  %wektor mo�e przyda� si� do dalszych oblicze�
i = 1;
while(i<=liczba_bit)
  ulamek_dziesietny = ulamek_dziesietny * 2;
  if(ulamek_dziesietny>1)
    ulamek_binarny(i) = 1;
    ulamek_dziesietny = ulamek_dziesietny - 1;
  elseif(ulamek_dziesietny<1)
    ulamek_binarny(i) = 0;
  else 
    ulamek_binarny(i) = 1;
    break;
  endif
  i=i+1;
endwhile
ulamek_bianrny_tekst = "0."; %dla wygody wyswietlnia zapisuje wektor jako �a�cuch znak�w
for(j=1:liczba_bit)
  ulamek_bianrny_tekst = strcat(ulamek_bianrny_tekst,num2str(ulamek_binarny(j)));
endfor
fprintf("Z dok�adno�ci� do %d bit�w warto�� u�amka %f w systemie binarnym wynosi %s", liczba_bit, ulamek_dziesietny_kopia, ulamek_bianrny_tekst);
%przy wy�wietlaniu wida� niepotrzebne zera(je�eli liczba bit�w potrzebna do zapisuje
%liczby binarnie jest mniejsza ni� podana przez u�ytkownika liczba bit�w), 
%jest to spowodowne u�yciem statycznej, a nie dynamicznie tworzonej tablicy
%co jednak mo�e mie� wp�yw na stabilno�� dzia�ania programu
%Zera te nie wp�ywaj� na wynik wi�c postanowi�em je zostawi�.

