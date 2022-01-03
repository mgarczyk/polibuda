cclear
cclose all
x = [-10:0.01:10];
x_dl = length(x);
y = zeros(1, x_dl);
for(i=1:x_dl);
  y(i) = x(i) * sin(x(i));
endfor
%y = x.*sin(x)  %./ .^ szybkie mno¿enie lepsze do ³atwych funckji (ale nie ma go w innych jêzykach)
plot(x,y) %tworzy wykres podanej funkcji f(x) = x * sin(x) dla x od <-10,10>;
title('f(x) = x * sin(x)');
xlabel ('os x');
ylabel ('os y');
legend('Wykres funkcji f(x) = x*sin(x) dla x nale¿¹cych do przedzialu <-10,10>')