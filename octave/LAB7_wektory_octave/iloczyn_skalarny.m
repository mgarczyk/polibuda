clear
tab1 = input('Podaj wektor 1:' );
dl_1 = length(tab1);
tab2 = input('Podaj wektor 2:' );
dl_2 = length(tab2);
iloczyn = 0;
if(dl_1 != dl_2)
  fprintf("Ilosc elemntow w wektorze musi byc taka sama");
else
  for(i=1:dl_2)
    iloczyn = iloczyn + (tab1(i) * tab2(i));
  end
  fprintf('Iloczyn skalarny tych wektorow wynosi %f', iloczyn);
endif
