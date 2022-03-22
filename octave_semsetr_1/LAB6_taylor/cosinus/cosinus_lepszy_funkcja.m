function [y,i] = cosinus_lepiej(x, n_maksymalne,max_error)
  ai = 1;
  ## a0 - musimy je podać
  y = ai;
  ## a0;
  for i = 1:n_maksymalne
    ## y = y + ((((-1)^n)/factorial(2*n)) * (x ^ (2 * n)));
    ai = -1 * x^2 * 1/((2*i)*((2*i)-1)) * ai;
    ## a1, a2, a3
    y = y + ai;
    if abs(abs(ai))<max_error
      break
    endif  
  endfor
endfunction