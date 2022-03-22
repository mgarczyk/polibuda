clear
close all
function [y,i] = cosinus_lepiej(x, n_maksymalne,max_error)
  ai = 1;
  ## a0 - musimy je podaÄ‡
  y = ai;
  ## a0;
  for i = 1:n_maksymalne
    ## y = y + ((((-1)^n)/factorial(2*n)) * (x ^ (2 * n)));
    ai = -1 * x^2 * 1/((2*i)*((2*i)-1)) * ai;
    ## a1, a2, a3
    y = y + ai;
    if abs(abs(ai))<max_error
      break
    endif  
  endfor
endfunction



x = linspace(-10,10,1000); %podawanie wektora
n_maksymalne = 100;
max_error = 0.2;
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
iterations = zeros(1,length(x));
for(i=1:length(x))
   [y_taylor(i), iterations(i)] = cosinus_lepiej(x(i), n_maksymalne, max_error); 
   y_orginal(i) = cos(x(i));
endfor
subplot(2,1,1)
plot(x, y_orginal);
hold on
plot(x, y_taylor,'k-');
ylim ([-2 2]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
subplot(2,1,2);
plot(x, iterations);
