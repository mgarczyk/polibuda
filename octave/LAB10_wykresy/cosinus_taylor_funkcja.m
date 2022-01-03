function y = cosinus_simple(x, n_maksymalne)
  y = 0;
  for(n=0:n_maksymalne)
    y = y + ((((-1)^n)/factorial(2*n)) * (x ^ (2 * n)));
  endfor
endfunction