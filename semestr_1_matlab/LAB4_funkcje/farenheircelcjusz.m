clear
function C = celTOfar(F)
  C = (F-32)/(1.8)
endfunction
F = input("Podaj temp w stopniach farenheita: ");
C = celTOfar(F);
fprintf("Temperatura w stopniach celcjusza wynosi %f:", C);
