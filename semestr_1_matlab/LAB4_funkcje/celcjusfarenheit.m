clear
function F = celTOfar(C)
  F = 9/5*C+32;
endfunction
C = input("Podaj temp w stopniach celcjusza: ");
F = celTOfar(C);
fprintf("Temperatura w stopniach farenheita wynosi %f:", F);
