clear
close all
function [y] = cosh_lepiej(x,n_maksymalne)
  ai = 1;
  ## a0 - musimy je podaÄ‡
  y = 0;
  ## a0;
  i = 1;
for(i=1:n_maksymalne)
    y = y + ai;
    ai = 1 * x^2 * 1/((2*i)*((2*i)-1)) * ai;
    ## a1, a2, a3
    i = i + 1;
endfor
  i = i - 1;
endfunction



x = linspace(-10,10,100); %podawanie wektora
n_maksymalne = 5;
max_error = 0.2;
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
blad = zeros(1,length(x));
for(i=1:length(x))
   [y_taylor(i)] = cosh_lepiej(x(i),n_maksymalne); 
   y_orginal(i) = cosh(x(i));
endfor
for(i=1:length(x))
    blad(i) = abs(y_taylor(i) - y_orginal(i));
endfor
disp(blad);
subplot(2,1,1)
plot(x, y_orginal);
hold on
plot(x, y_taylor,'k-');
ylim ([0 1000]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
subplot(2,1,2);
plot(x, cosh(x));
ylim ([0 1000]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
