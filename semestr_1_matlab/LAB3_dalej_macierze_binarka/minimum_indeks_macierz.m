clear
x = input("Podaj macierz: ");
[wier,kol] = size(x);
%wersja ze zmienn¹ do minimum
mini = x(1,1);
mini_indeks = [1,1];
for(w=1:wier)
  for(k=1:kol)
    if(mini > x(w,k))
      mini = x(w,k);
      mini_indeks = [w,k];
    endif
  endfor
endfor
printf("Minimum tej macierzy wynosi %f", mini);
disp(mini_indeks);

%wersja bez zmiennej z samymi indeksami
min_w = 1;
min_k = 1;
for(w=1:wier)
  for(k=1:kol)
    if(x(w,k) < x(min_w, min_k))
      min_w = w;
      min_k = k;
    endif
  endfor
endfor
printf("Minimum tej macierzy wynosi %f", x(min_w, min_k));
printf("Indeks minimum to %d %d", min_w, min_k);
