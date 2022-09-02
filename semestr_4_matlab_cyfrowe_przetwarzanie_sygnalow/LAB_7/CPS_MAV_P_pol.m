% FILTR TYPU RUCHOMA ŚREDNIA = MAV (MOVING-AVERAGE FILTER)
                    
clear; clc;
M=19;
B=ones(1,M)/M;                         % macierz współzynników filtru MAV

% 3b.Badanie skuteczności filtru dla trzech wartości M (4<M<20),
%    szumu o rozkładzie równomiernym i dla dopasowanych uprzenio trzech wariancji

A=1; f=0.1; 
Fs=4; 
t=0:1/Fs:30;
x0=A*sin(2*pi*f*t);                    % sygnał

L=length(t);
vvar=1.5;                               % 0.3   inne: 0.coś, 1.coś

rand('state',0);
p=rand(1,L);
szum=sqrt(14*vvar)*(p-0.5);            % szum "prostokątny"
s=mean(szum);                          % wartość średnia szumu (różnana od 0)

szum0=szum-s;               % szum prostokątny o zerowej wartości średniej
s0=mean(szum-s);            % wartość średnia szumu (=0)           

vp22=var(szum0);            % wariancja szumu   (SPRAWDZIĆ)

hist(szum0,20);
                 
x=x0+szum0;                            % sygnał sinusoidalny, zaszumiony

y=filter(B,1,x);
subplot(2,1,1); plot(t,x0); hold on; plot(t,x,'r'); hold off; grid; 
subplot(2,1,2); plot(t,x0); hold on; plot(t,y,'r'); hold off; grid;
