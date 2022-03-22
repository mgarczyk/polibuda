clear
ulamek_dziesietny = input("Podaj ulamek w systemie dziesietnym: ");
liczba_bit = input("Podaj na ilu bitahc checesz zapisaæ u³amek: ");
ulamek_dziesietny_kopia = ulamek_dziesietny;
ulamek_binarny = zeros(liczba_bit);  %wektor mo¿e przydaæ siê do dalszych obliczeñ
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
ulamek_bianrny_tekst = "0."; %dla wygody wyswietlnia zapisuje wektor jako ³añcuch znaków
for(j=1:liczba_bit)
  ulamek_bianrny_tekst = strcat(ulamek_bianrny_tekst,num2str(ulamek_binarny(j)));
endfor
fprintf("Z dok³adnoœci¹ do %d bitów wartoœæ u³amka %f w systemie binarnym wynosi %s", liczba_bit, ulamek_dziesietny_kopia, ulamek_bianrny_tekst);
%przy wyœwietlaniu widaæ niepotrzebne zera(je¿eli liczba bitów potrzebna do zapisuje
%liczby binarnie jest mniejsza ni¿ podana przez u¿ytkownika liczba bitów), 
%jest to spowodowne u¿yciem statycznej, a nie dynamicznie tworzonej tablicy
%co jednak mo¿e mieæ wp³yw na stabilnoœæ dzia³ania programu
%Zera te nie wp³ywaj¹ na wynik wiêc postanowi³em je zostawiæ.

