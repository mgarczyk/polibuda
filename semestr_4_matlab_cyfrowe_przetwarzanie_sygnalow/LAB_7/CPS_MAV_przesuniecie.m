clear; clc;
M=19;
B=ones(1,M)/M;

% 4.Badanie przesunięcia fazowego (dla trzech wartości M i 4<M<20)

A=1; f=0.1; 
Fs=4; 
t=0:1/Fs:30;
x0=A*sin(2*pi*f*t);                    % sygnał

y0=filter(B,1,x0);
stem(t,x0,'.b','MarkerSize',15); hold on; 
stem(t,y0,'.r','MarkerSize',15); hold off; grid;


% Kompensacja
%x0p=A*sin(2*pi*f*(t-(M-1)/(2*Fs)));          % odniesienie "skorygowane" pomocne do wyznaczenia przesunięcia fazowego
%subplot(311);stem(t,x0p,'.b'); grid;
%subplot(312);stem(t,y0,'.r'); grid;
%subplot(313);stem(t,y0-x0p,'.'); grid;