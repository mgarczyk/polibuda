clear
close all
function y = sinus_simple(x, n_maksymalne)
  y = 0;
  for(n=0:n_maksymalne)
    y = y + ((((-1)^n)/factorial((2*n) + 1)) * (x ^ ((2 * n) + 1)));
  endfor
endfunction

x = linspace(-10,10,200); %podawanie wektora
n_maksymalne = input("Podaj n:");
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
for(i=1:length(x));
  y_taylor(i) = sinus_simple(x(i), n_maksymalne);
  y_orginal(i) = sin(x(i));
endfor
plot(x, y_orginal);
hold on
plot(x, y_taylor);
ylim ([-2 2.5]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim