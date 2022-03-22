clear

function ulamek_binarny = frac2bin(ulamek_dziesietny, liczba_bit)
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

function ulamek_dziesietny = bin2frac(ulamek_binarny)
   liczba_bit = length(ulamek_binarny);
  for(i=1:liczba_bit)
    ulamek_dziesietny = ulamek_dziesietny + ulamek_binarny(i)*(2^(-i)); %bit*(1/2) bit*(1/4) itp 1 * 1^(-2) = 1/2, 2^(-2) = 1/2^2 = 1/4 itd
  endfor
endfunction



%dane
ulamek_dziesietny = input("Podaj ulamek w systemie dziesietnym: ");
liczba_bit = input("Podaj na ilu bitahc checesz zapisaæ u³amek: ");
ulamek_dziesietny_kopia = ulamek_dziesietny;
%ulamek binarny
ulamek_binarny = zeros(1, liczba_bit); 
ulamek_binarny = frac2bin(ulamek_dziesietny, liczba_bit);
fprintf("Z dok³adnoœci¹ do %d bitów wartoœæ u³amka %f w systemie binarnym wynosi 0.wektor ulamek_binarny\n", liczba_bit, ulamek_dziesietny_kopia);
disp(ulamek_binarny);
%ulamek z powrotem dziesietny
ulamek_dziesietny = bin2frac(ulamek_binarny);
fprintf("Wartosc ulamka z wektora ulamek_binarny dziesietnie to %f ", ulamek_dziesietny);


