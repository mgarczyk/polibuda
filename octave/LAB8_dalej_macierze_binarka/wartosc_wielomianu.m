clear
disp("Dla danych [3,2,1,1] powtanie wilomian f(x) = 3x^3 + 2x^2 + x + 1 itp.");
wspolczynniki = input("Podaj wspolczynniki stoj¹ce przy kolejnych potêgach x: " );
x = input("Podaj argument dla którego szukana jest wartoœæ wielomianu: ");
wspolczynniki = wspolczynniki(end:-1:1); %odwracam ¿eby dla wygody wyraz wolny by³ na pierszym miejscu
dl_wspolczynniki = length(wspolczynniki);
if(wspolczynniki(1) > 0)
  wielomian = strcat("+",num2str(wspolczynniki(1))); %zapisujemy wielomian by byl w czytelny sposób widoczny dla u¿ytkownika
else
   wielomian = num2str(wspolczynniki(1));
endif
for(i=2:dl_wspolczynniki)
  if(wspolczynniki(i) > 0 && i~=dl_wspolczynniki)
    wielomian = strcat("+", int2str(wspolczynniki(i)),"x^",int2str(i-1),wielomian); %dla dodatnich dodajemy znak "+" pomiêdzy wyrazami oprócz pierwszego wyrazu
  elseif(wspolczynniki <=0 || i==dl_wspolczynniki)
    wielomian = strcat(int2str(wspolczynniki(i)),"x^",int2str(i-1),wielomian); %dla ujemnych "-" jest dodany z "automatu"
  endif
endfor
wielomian = strcat("w(x) =", wielomian);
wartosc = wspolczynniki(1); %wyraz wolny jest wartoœci¹ pocz¹tkow¹ szulkanej sumy (wartosci wielomianu) jest on na 1 pozycji odwróconej tablicy
for(i=2:dl_wspolczynniki) %zaczysnamy od 2 elemntu odwroconego wektora bo wyraz wolny zostal juz uzyty
  wartosc = wartosc + (wspolczynniki(i) * (x^(i-1)));
endfor
fprintf("Wartosc podanego wielomianu %s dla x=%f wynosi %f", wielomian, x, wartosc);

