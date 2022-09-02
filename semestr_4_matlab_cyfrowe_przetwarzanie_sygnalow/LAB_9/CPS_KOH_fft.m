% Uśrednianie FFT - koherentne

clear; clc;
f=0.5; Fs=4;
N=256;
t=0:1/Fs:(N-1)/Fs;
x=0.2*sin(2*pi*f*t);                       % sygnał

L=length(t);
F=Fs*(0:L-1)/L;

vvar=2.5;
R=500;                                % R: kilka, kilkadziesiąt, kilkaset np. R: 4, 40, 400
suma1=0; suma2=0;
for i=1:R
    g=randn(1,L);
    s0=sqrt(vvar)*g;
    s1=s0-mean(s0);
    y=x+s1;
    suma1=suma1+real((2/L)*fft(y,L));     % suma czci rzeczywistych widm
    suma2=suma2+imag((2/L)*fft(y,L));     % suma części urojonych widm
end
sredniaRE=suma1/R;                     % średnia z R części rzeczywistych
sredniaIM=suma2/R;                     % średnia z R części urojonych

KOH=sqrt((sredniaRE).^2+(sredniaIM).^2);      % moduł
%KOH=abs(sredniaRE+1i*sredniaIM);             % inne możliwosci
%KOH=abs(suma1+1i*suma2)/R;

stem(F,KOH,'.'); title('widmo sygnału po uśrednianiu koherentnym'); grid; % widmo sygnału po uśrednianiu koherentnym




