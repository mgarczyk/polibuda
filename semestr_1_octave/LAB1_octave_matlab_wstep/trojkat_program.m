clear
a = input('Podaj dlugosc boku a:' );
b = input('Podaj dlugosc boku b:' );
c = input('Podaj dlugosc boku c:' ); #za³o¿enie - c to d³ugoœæ najd³u¿szego boku
if (a < c && b < c)
  if(a > 0 && b > 0 && c > 0)
    if(a + b > c)
     if((a^2) + (b^2) == c^2)
        fprintf('Jest to trojkat PROSTOKATNY');
      elseif((a^2) + (b^2) < c^2)
        fprintf('Jest to trojkat ROZWARTOKATNY');
      else
       fprintf('Jest to trojkat OSTRAKATNY');
    endif
    else
      fprintf('Nie spelniono warunku, ze suma dlugosci dwoch krotszych bokow powinna byc wieksza od dlugosci najdluzego boku');
    endif
  else
    fprintf('Dlugosca kazdego boku musi byc liczba nieujemna, wieksza od 0');  
  endif
else
  printf('Dane nie spelniaja zalozenia')
endif