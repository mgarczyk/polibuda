function [y,i] = sinus_lepiej_blad(x,max_error)
  ai = x;
  ## a0 - musimy je podać
  y = 0;
  ## a0;
  i = 1;
  while abs(ai) > max_error
    y = y + ai;
    ai =  -1 * x^2 * 1/(((2*i) + 1)*(2*i)) * ai;
    ## a1, a2, a3
    i = i + 1;
  endwhile
  i=i-1;
endfunction
