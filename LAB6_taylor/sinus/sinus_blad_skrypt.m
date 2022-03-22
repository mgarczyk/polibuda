clear
close all
function [y,i] = sinus_lepiej_blad(x,max_error)
  x = atan(x) - x;
  ai = x;
  y = 0;
  i = 1;
  while abs(ai) > max_error
    y = y + ai;
    ai =  (((-1)^i)/((2*i) + 1)*x^((2*i) + 1)) * ai
    i = i + 1;
  endwhile
  i=i-1;
endfunction

x = linspace(-10,10,1000); %podawanie wektora
n_maksymalne = 100;
max_error = 0.2;
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
iterations = zeros(1,length(x));
for(i=1:length(x));
  [y_taylor(i), iterations(i)] = sinus_lepiej_blad(x(i), max_error); %pierwsza wartosc z funkcji do jenej tablicy, druga do drugiej
  y_orginal(i) = sinh(x(i));
endfor
subplot(2,1,1)
plot(x, y_orginal);
hold on
plot(x, y_taylor,'k-');
ylim ([-2 2]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
subplot(2,1,2);
plot(x, iterations);
