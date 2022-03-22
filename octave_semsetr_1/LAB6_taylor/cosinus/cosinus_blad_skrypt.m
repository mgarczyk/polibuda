clear
close all
function [y] = cosinus_lepiej(x,n_maksymalne)
  error = 0;
  ai = 1;
  ## a0 - musimy je podaÄ‡
  y = ai;
  i = 1;
  for(i=1:n_maksymalne)
    ai = 1 * x^2 * 1/((2*i)*((2*i)-1)) * ai;
    y = y + ai;
    ## a1, a2, a3
    i = i + 1;
  endfor
  i = i - 1;
endfunction



x = linspace(-10,10,50); %podawanie wektora
n_maksymalne = 100;
y_taylor = zeros(1, length(x));
y_orginal = zeros(1, length(x));
for(i=1:length(x))
   [y_taylor(i)] = cosinus_lepiej(x(i),n_maksymalne); 
   y_orginal(i) = cosh(x(i));
endfor
subplot(2,1,1)
plot(x, y_orginal);
hold on
plot(x, y_taylor,'k-');
ylim ([0 5]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
subplot(2,1,2);
plot(x, y_orginal);
ylim ([0 5]); %limtuje oœ Y mo¿na zrobiæ podbnie dla osi x xlim
xlim([-10 10])
wektor_bezwzgledny = zeros(1, length(x));
for(i=1:length(x))
  wektor_bezwzgledny(i) = abs(y_taylor(i) - y_orginal(i))            #wektor bezwzgledny
endfor
disp(wektor_bezwzgledny);

