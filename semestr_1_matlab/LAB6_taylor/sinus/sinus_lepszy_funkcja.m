function [y,i] = sinus_lepiej(x, n_maksymalne, max_error)
  ai = x;
  ## a0 - musimy je podac
  y = ai;
  ## a0;
  for i = 1:n_maksymalne
    ## y = y + ((((-1)^n)/factorial(2*n)) * (x ^ (2 * n)));
    ai =  -1 * x^2 * 1/(((2*i) + 1)*(2*i)) * ai;
    ## a1, a2, a3
    y = y + ai;
    if abs(abs(ai))<max_error
      break
    endif  
  endfor
endfunction