clear
close all %zamyka wykresy

function ulamek_binarny = frac2bin(ulamek_dziesietny, liczba_bit) %przelicznie na binarny
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
endfunction

function ulamek_dziesietny = bin2frac(ulamek_binarny) %przelicznie na dziesitny
  liczba_bit = length(ulamek_binarny);
  ulamek_dziesietny = 0;
  for(i=1:liczba_bit)
    ulamek_dziesietny = ulamek_dziesietny + ulamek_binarny(i)*(2^(-i)); %bit*(1/2) bit*(1/4) itp 1 * 1^(-2) = 1/2, 2^(-2) = 1/2^2 = 1/4 itd
  endfor
endfunction


%XWEK
XWEK = [0.01:0.001:0.99];
dokladnosc = input("Podaj dokladnosc:");
dl_XWEK = length(XWEK);
XWEK2 = zeros(1, dl_XWEK);
blad = zeros(1, dl_XWEK); %przechwujemy wartoœæ bledu w przeliczniu
for(i=1:dl_XWEK) %zamieniamy z dziesetnego na binarke (wektor) i potem z powrotem na dziesiêtny
  XWEK2(i) = bin2frac(frac2bin(XWEK(i),dokladnosc)); %z dziesetnego na binarke funkcj¹ w funkcji i potem zewnêtrzn¹ funkcj¹ z porotem na dziesiêtny i to wektora XWEK2
  blad(i) = abs(XWEK2(i) - XWEK(i)); %wartoœæ b³êdu bezwzglêdnego do ka¿dego przlicznia
  endfor
disp(XWEK2); %w wektorze s¹ wartoœci dziesiêtne. Dziesiêtne->Binarka->Dziesiêtne
plot(XWEK, XWEK2, 'ro:'); %tworzy wykres i kolorowanie na czerwono oraz pogrubienie
xlabel('Os X'); %tytu³ osi X
ylabel('Os Y'); %tytu³ osi Y
title('Tytul') %tytu³ wykresu
grid on %widok siatki wykresy
hold on %u¿ywamy, gdy chcemy by wykres wyœwitla³ siê wraz z innymi wykresami i nie zostal usuniêty
plot(XWEK,XWEK, 'k') %inny wykres (taki idealny), gdyby dok³adnoœæ by³a idealna
legend('przyblizenie', 'ideal') %opis legenda co to robi
subplot(2,1,1) %podziel okno z wykresami (dwa wiersze, jedna kolumna i jako pierwszy wyœwietla poni¿ szy wykres
plot(XWEK, blad); %wykres poakzu¹cy wartoœæ b³êdu w przeliczaniu
subplot(2,1,2) %poni¿szy wykres umieœcimy w drugim wierszu w pierwszej kolumnie
semilogy(XWEK, blad) %ten sam wykres co wy¿ej tylko w skali logarytmicznej

