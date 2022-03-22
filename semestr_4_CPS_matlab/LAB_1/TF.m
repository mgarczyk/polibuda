% Aproksymacja ci�gu impuls�w prostok�tnych trygonometrycznym szeregiem Fouriera o sko�czonej liczbie sk�adnik�w

clear; clc;
t = -3:6/100000:3;

%--------------------------------------------------------------------------------------------------------------------------------------------------
A = 3;                                         % A=...   A=...  
w0 = pi;                                     % w0=pi, w0=0.4*pi, w0=4*pi
N = 555;                                          % N liczba sk�adowych harmonicznych u�ytych do aproksymacji    N=X, N=X0, N=X00
%--------------------------------------------------------------------------------------------------------------------------------------------------

a0 = A/2;                                   % sk�adowa sta�a

xN = a0*ones(1,length(t));

for k=1:N
    xN = xN + A*2/k/pi*sin(k*pi/2)*cos(k*w0*t);
end

DELTA=max(xN)-A                  % maksymalna warto�� zafalowania
P=(DELTA/A)*100

plot(t,xN); grid;
title(['N=',num2str(N)])
xlabel('Time (sec)')
ylabel(['x',num2str(N),'(t)'])
