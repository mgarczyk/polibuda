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
blad = zeros(1, dl_XWEK); %przechwujemy warto�� bledu w przeliczniu
for(i=1:dl_XWEK) %zamieniamy z dziesetnego na binarke (wektor) i potem z powrotem na dziesi�tny
  XWEK2(i) = bin2frac(frac2bin(XWEK(i),dokladnosc)); %z dziesetnego na binarke funkcj� w funkcji i potem zewn�trzn� funkcj� z porotem na dziesi�tny i to wektora XWEK2
  blad(i) = abs(XWEK2(i) - XWEK(i)); %warto�� b��du bezwzgl�dnego do ka�dego przlicznia
  endfor
disp(XWEK2); %w wektorze s� warto�ci dziesi�tne. Dziesi�tne->Binarka->Dziesi�tne
plot(XWEK, XWEK2, 'ro:'); %tworzy wykres i kolorowanie na czerwono oraz pogrubienie
xlabel('Os X'); %tytu� osi X
ylabel('Os Y'); %tytu� osi Y
title('Tytul') %tytu� wykresu
grid on %widok siatki wykresy
hold on %u�ywamy, gdy chcemy by wykres wy�witla� si� wraz z innymi wykresami i nie zostal usuni�ty
plot(XWEK,XWEK, 'k') %inny wykres (taki idealny), gdyby dok�adno�� by�a idealna
legend('przyblizenie', 'ideal') %opis legenda co to robi
subplot(2,1,1) %podziel okno z wykresami (dwa wiersze, jedna kolumna i jako pierwszy wy�wietla poni� szy wykres
plot(XWEK, blad); %wykres poakzu�cy warto�� b��du w przeliczaniu
subplot(2,1,2) %poni�szy wykres umie�cimy w drugim wierszu w pierwszej kolumnie
semilogy(XWEK, blad) %ten sam wykres co wy�ej tylko w skali logarytmicznej

