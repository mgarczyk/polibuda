clear; #program uruchamia siê od nowa za ka¿dym razem jak w c++, kasuje zawartoœæ zmiennych w workspace, przydatne
a = input('a:' );
b = input('b:' );
c = input('c:' );
if(a == 0)
  if(b == 0)
    if(c == 0)
      fprintf('Uk³ad nieoznaczony'); #a=0, b=0, c=0 - nieoznaczony
    else
      fprintf('Uk³ad sprzeczny');    #a=0, b=0, c=x - sprzeczny
    endif
  else #linowy
    x0 = -b / c;
    fprintf('Rozwiazanie rownania liniowego wynosi %5.2f', x0);
  endif
else #kwadratowe
  delta = (b * b) - (4 * a * c);
  if(delta > 0) #dwa rozwi¹zania rzeczywiste
    x1 = (-b + sqrt(delta))/(2*a); #uwa¿aæ na nawiasy (kolejnoœæ dzia³añ)
    x2 = (-b - sqrt(delta))/(2*a);
    fprintf('Pierwiastki rownania kwadratowego o wspoczynnikach %5.2f, %5.2f, %5.2f to %f oraz %f',a,b,c,x1,x2);
  else 
    if(delta < 0)
      fprintf('sprzeczne'); #delta < 0 - sprzeczne
    else
      x0 = -b/(2 * a) #delta = 0
      fprintf('Pierwiastek rownania kwadratowego o wspoczynnikach %5.2f, %5.2f, %5.2f to %f',a,b,c,x0);
    endif
  endif
endif
