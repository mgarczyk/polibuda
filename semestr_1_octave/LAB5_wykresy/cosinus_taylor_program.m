clear
close all

function y = cosinus_simple(x, n_maksymalne)
  y = 0;
  for(n=0:n_maksymalne)
    y = y + ((((-1)^n)/factorial(2*n)) * (x ^ (2 * n)));
  endfor
endfunction


x = linspace(-5,5,200);
n_maksymalne = input("Podaj n:");
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
for(i=1:length(x));
  y_taylor(i) = cosinus_simple(x(i), n_maksymalne); 
  y_orginal(i) = cos(x(i));
endfor
plot(x, y_orginal);
hold on
plot(x, y_taylor);
ylim ([-2 2.5]);
xlim([-10 10]);
xlabel('Os x');
ylabel('Os y');
legend("Przyli¿enie funkcji y = cos(x) przy pomocy szeregu Taylora.");
