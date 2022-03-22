clear
x = input('podaj wektor: ');
n = length(x);
s = 0;
for i=1:n
  s = s + x(i);
endfor
disp(x)
fprintf('Srednia arytmetyczna wynosi %f', s/n);