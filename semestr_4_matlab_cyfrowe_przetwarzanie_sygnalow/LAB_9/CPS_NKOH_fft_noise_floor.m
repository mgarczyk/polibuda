% Uśrednianie FFT - niekoherentne

clear; clc;
f=0.5; Fs=4;
N=256;
t=0:1/Fs:(N-1)/Fs;
x=0.2*sin(2*pi*f*t);

L=length(t);
F=Fs*(0:L-1)/L;

vvar=2.5;
R=40000;                                  % R:   kilkaset, kilka tysięcy, kilkadziesiąt tysięcy
suma=0;
for i=1:R
    g=randn(1,L);
    szum0=sqrt(vvar)*g;
    szum1=szum0-mean(szum0);
    y=x+szum1;
    suma=suma+(2/L)*abs(fft(y,L));
end
srednia=suma/R;

%Rysunki ze znacznikami
X=fft(x,L);
stem(F,(2/L)*abs(X),'r','LineWidth',1.5); hold on;
stem(F,abs(srednia)); hold off; grid;
