clear; clc;

N=100;                                 
fs=100;                                 
t=0:1/fs:(N-1)/fs;
f1=10; d1=3*sin(2*pi*f1*t);
f2=20; d2=2*sin(2*pi*f2*t);

                                         % Sprawdzanie liniowoœci DFT
f=fs*(0:length(d1)-1)/length(d1);

                                         % addytywnoœæ
D1=fft(d1);
D2=fft(d2);
WiSu=  fft(d1+d2);                       
SuWi= D1+D2;                             

subplot(6,1,1); stem(f,(2/N)*abs(D1));xlabel('f [Hz]');grid;
subplot(6,1,2); stem(f,(2/N)*abs(D2));grid;
subplot(6,1,3); stem(f,(2/N)*abs(WiSu));title('Widmo sumy sygna³ów');grid;
subplot(6,1,4); stem(f,(2/N)*abs(SuWi));title('Suma widm sygna³ów');xlabel('f [Hz]');grid;


% jednorodnoœæ - zrealizowaæ  samodzielnie
A=5
f3=30; 
d3 = sin(2*pi*f2*t);
WiIl = fft(A * d3);                      %transformata iloczynu
IlWi =  A * fft(d3);                     %iloczyn transformaty przez sta³¹  A
%rysunki jednorodnosc
subplot(6,1,5); stem(f,(2/N)*abs(WiIl));title('Widmo sygna³u mno¿onego przez A');axis([0,100,0,5]);
xlabel('f [Hz]');grid;
subplot(6,1,6); stem(f,(2/N)*abs(IlWi));title('Iloczyn widma i sta³ej A');axis([0,100,0,5]);
xlabel('f [Hz]');grid;

