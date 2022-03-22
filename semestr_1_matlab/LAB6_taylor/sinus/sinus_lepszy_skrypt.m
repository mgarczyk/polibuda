clear
close all
function [y,i] = sinus_lepiej(x, n_maksymalne)
  ai = x;
  y = ai;
  for i = 1:n_maksymalne
    ai =  -1 * x^2 * 1/(((2*i) + 1)*(2*i)) * ai;
    y = y + ai;
  endfor
endfunction

x = linspace(-10,10,1000); %podawanie wektora
n_maksymalne = 5;
max_error = 0.2;
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
iterations = zeros(1,length(x));
for(i=1:length(x));
  [y_taylor(i), iterations(i)] = sinus_lepiej(x(i), n_maksymalne, max_error); %pierwsza wartosc z funkcji do jenej tablicy, druga do drugiej
  y_orginal(i) = sin(x(i));
endfor
subplot(2,1,1)
plot(x, y_orginal);
hold on
plot(x, y_taylor,'k-');
ylim ([-2 2]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
subplot(2,1,2);
plot(x, iterations);
