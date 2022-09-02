% B. Zastosowanie okien (dla N z max przecieku)
pkg load signal;
clear; clc;
fs=30; fx=3;  
N=100;                           % wycięcie z max przeciekiem
t=0:1/fs:(N-1)/fs;
y=sin(2*pi*t*fx);
f=fs*(0:length(y)-1)/length(y);
Y=fft(y);

w=(window(@kaiser,N))'; %podtaw @gaussian, @hann, @kaiser albo inne z https://octave.sourceforge.io/signal/overview.html
yw=y.*w;
YW=fft(yw);

subplot(4,1,1); stem(y,'.');xlabel('n');ylabel('y(n)');grid;
subplot(4,1,2); stem(w,'.');xlabel('n');ylabel('w(n)');grid;
subplot(4,1,3); stem(f,(2/N)*abs(Y),'.');xlabel('f [Hz]');ylabel('Y');grid;
subplot(4,1,4); stem(f,(2/N)*abs(YW),'.');xlabel('f [Hz]');ylabel('YW');grid;

% B1. Zrealizować synulację dla 3 okien
% B2. Określić częstotliwość dwóch największych prążków w widmie YW
% B3. Porównać widma Y i YW

%_____________________________________________________________________ 
subplot(4,1,3); stem(f,(2/N)*abs(Y),'.');hold on; stem(f0,(2/N0)*abs(Y0),'r','.');hold off;
subplot(4,1,4); stem(f,(2/N)*abs(YW),'.');hold on; stem(f0,(2/N0)*abs(Y0),'r','.');hold off;