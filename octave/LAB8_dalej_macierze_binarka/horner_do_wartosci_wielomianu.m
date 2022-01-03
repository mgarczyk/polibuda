clear
disp("Dla danych [3,2,1,1] powtanie wilomian f(x) = 3x^3 + 2x^2 + x + 1 itp.");
wspolczynniki = input("Podaj wspolczynniki stoj�ce przy kolejnych pot�gach x: " );
x = input("Podaj argument dla kt�rego szukana jest warto�� wielomianu: ");
wspolczynniki = wspolczynniki(end:-1:1); %odwracam �eby dla wygody wyraz wolny by� na pierszym miejscu
dl_wspolczynniki = length(wspolczynniki);
if(wspolczynniki(1) > 0)
  wielomian = strcat("+",num2str(wspolczynniki(1))); %zapisujemy wielomian by byl w czytelny spos�b widoczny dla u�ytkownika
else
   wielomian = num2str(wspolczynniki(1));
endif
for(i=2:dl_wspolczynniki)
  if(wspolczynniki(i) > 0 && i~=dl_wspolczynniki)
    wielomian = strcat("+", int2str(wspolczynniki(i)),"x^",int2str(i-1),wielomian); %dla dodatnich dodajemy znak "+" pomi�dzy wyrazami opr�cz pierwszego wyrazu
  elseif(wspolczynniki <=0 || i==dl_wspolczynniki)
    wielomian = strcat(int2str(wspolczynniki(i)),"x^",int2str(i-1),wielomian); %dla ujemnych "-" jest dodany z "automatu"
  endif
endfor
wielomian = strcat("f(x) =", wielomian);
wartosc_wielomianu = wspolczynniki(dl_wspolczynniki);
for(i=dl_wspolczynniki-1:-1:1) %w(x) = 3x^4+3x^3+x^2+x+5 <=> w(x) = x(x(x(3x+3)+1)+1)+55
  wartosc_wielomianu = wartosc_wielomianu * x + wspolczynniki(i); %najbardziej wewn�trzny nawias
endfor
wartosc_wielomianu = wartosc_wielomianu(1) %najpierw przypisujemy jako warto�� pocz�tkow� warto�� wyrazu wolnego
fprintf("Wartosc podanego wielomianu %s dla x=%f wynosi %f", wielomian, x, wartosc_wielomianu);