clear
x = input("Podaj liuczbe w systemie dziesetnym: ")
i = 1
C = 0 %wektro zawierajacy 0
while(x>0)
  C(i) = mod(x,2);
  x = floor(x/2);
  i = i + 1;
endwhile
disp(C) %z³a kolejnoœæ
C = C(end:-1:1); %ma³a pêtelka to odwrócenia koljnoœci w tablicy
disp(C) %dobra koljnoœæ