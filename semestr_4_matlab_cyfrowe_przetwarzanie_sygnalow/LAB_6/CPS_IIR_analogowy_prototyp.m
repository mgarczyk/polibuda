% Analogowy prototyp FDP (Filtru DolnoPrzepustowego Butterwortha (W-omega)
pkg load signal;
clear; clc;
zp=0.01;                         % zafalowanie w paśmie przepustowym
zs=0.1;                          % zafalowanie w paśmie zaporowym
fp=2000; Wp=2*pi*fp;             % pulsacja graniczna pasma przepustowego
fs=2500; Ws=2*pi*fs;             % pulsacja graniczna pasma zaporowego

                                 % zamiana zafalowań na wartości w [dB] 
eps=(2*sqrt(zp))/(1-zp);
A=(1+zp)/zs;
Ap=-10*log10(1/(eps^2+1));       % w dB
As=-10*log10(1/A^2);             % w dB
                            
[n,Wn]=buttord(Wp,Ws,Ap,As,'s');     % obliczanie rzędu filtru analogowego
printf("Rz�d: ")
disp(n)
printf("Pulsacja odci�cia: ")
disp(Wn)
[b,a]=butter(n,Wn,'s');     % filtr analogowy Butterwortha - transmitancja

%uzyskano    Ap=?    As=?    n=?    Wn=? [rad/s] odczytaj z workspace

% Charakterystyka częstotliwościowa filtru analogowego W[rad/s]             
wa = linspace(0,10^5,128);
HA=freqs(b,a,wa);                       

% Odpowiedź impilsowa filtru analogowego
[r,p,k]=residue(b,a);            % r,p są zespolone (i zespolone sprzężone)
t=0:0.00001:0.01;
ha=0;
for i=1:length(r)
    ha=ha+r(i)*exp(t.*p(i));
end

M=abs(HA);

subplot(3,1,1); plot(wa,abs(HA)); grid; title('Charakterystyka amplitudowa'); 
xlabel('\omega [rad/s]','FontSize',12);
subplot(3,1,2); plot(wa,unwrap(angle(HA))); grid; title('Charakterystyka fazowa'); 
xlabel('\omega [rad/s]','FontSize',12);
subplot(3,1,3); plot(t,ha); grid; title('Odpowiedź impulsowa');
xlabel('t [s]');

%uzyskano    Wp=? [rad/s]  Ws=? [rad/s] odczytaj z wykresu

%subplot(2,1,1); plot(t, real(ha));
%subplot(2,1,2); plot(t, imag(ha)); 
