clear

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
XWEK = input("Podaj wektor XWEK:");
dokladnosc = input("Podaj dokladnosc:");
dl_XWEK = length(XWEK);
XWEK2 = zeros(1, dl_XWEK);
for(i=1:dl_XWEK) %zamieniamy z dziesetnego na binarke (wektor) i potem z powrotem na dziesiêtny
  XWEK2(i) = bin2frac(frac2bin(XWEK(i),dokladnosc)); %z dziesetnego na binarke funkcj¹ w funkcji i potem zewnêtrzn¹ funkcj¹ z porotem na dziesiêtny i to wektora XWEK2
endfor
disp(XWEK2); %w wektorze s¹ wartoœci dziesiêtne. Dziesiêtne->Binarka->Dziesiêtne
plot(XWEK, XWEK2);
