clear
x = input("Podaj liuczbe w systemie dziesetnym: ")
i = 1
C = 0 %wektro zawierajacy 0
while(x>0)
  C(i) = mod(x,2);
  x = floor(x/2);
  i = i + 1;
endwhile
disp(C) %z�a kolejno��
C = C(end:-1:1); %ma�a p�telka to odwr�cenia koljno�ci w tablicy
disp(C) %dobra koljno��