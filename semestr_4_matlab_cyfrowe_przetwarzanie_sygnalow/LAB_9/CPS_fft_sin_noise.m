% FFT 
clear; clc;
f=0.5; Fs=4;
N=256;
t=0:1/Fs:(N-1)/Fs;
x=0.2*sin(2*pi*f*t);                       % sygnał

L=length(t);
F=Fs*(0:L-1)/L;

X=fft(x,L);
%stem(F,(2/N)*abs(X));                % sprawdzenie wycięcia bez przecieku

vvar=2.5;

g=randn(1,L);
s0=sqrt(vvar)*g;
s1=s0-mean(s0);
y=x+s1;
Y=fft(y,L);

subplot(2,1,1); plot(t,x,'r'); title('sygnał ukryty w szumie'); hold on;
plot(t,y,'b'); hold off; grid;
subplot(2,1,2); stem(F,(2/L)*abs(X),'r','LineWidth',1.5); title('widmo sygnału ukrytego w szumie'); hold on;
stem(F,(2/L)*abs(Y)); hold off; grid;



