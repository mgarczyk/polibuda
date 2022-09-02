% Metoda aproksymacji równomiernie falistej  FIR
pkg load signal;
%clear; clc;
Fs=8192;
%[n,f0,m0,w]=firpmord([2000 2100],[1 0],[0.1 0.1],Fs);  %dla osób korzystających z Matlaba
%w Octavie funkcja teoretycznie istnieje w pakiecie signal, ale jest niezaimplementowana
%firpmord([2000 2100],[1 0],[0.01 0.1],Fs)
n=58; f0=[0;0.488281250000000;0.512695312500000;1]; m0=[1;1;0;0]; w=[1;1]; 
b=remez(n,f0,m0,w);          %alternatywnie firpm                                                

[H,f]=freqz(b,1,512,Fs);

subplot(3,1,1); plot(f,abs(H)); grid; title('Charakterystyka amplitudowa'); 
xlabel('f [Hz]');

subplot(3,1,2); plot(f,unwrap(angle(H))); grid; title('Charakterystyka fazowa'); 
xlabel('f [Hz]');

subplot(3,1,3); stem(impz(b),'.'); grid; title('Odpowiedź impulsowa');
xlabel('Numer próbki');


% fvtool(b,1);

%______________________________________________________________________ 
%1. Odczytaj (z Matlab-Workspace) wymiar macierzy b oraz rząd filtru n

%2. Sprawdź parametry zaprojektowanego filtru:
%pasmo przenoszenia, pasmo zaporowe, 
%zafalowanie w paśmie przenoszenia, zafalowannie w paśmie zapoprwym,
%liczbę próbek odpowiedzi impulsowej





