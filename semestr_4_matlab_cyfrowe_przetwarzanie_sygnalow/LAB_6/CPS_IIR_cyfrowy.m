% Tworzenie cyfrowego IIR-FDP na podstawie prototypu analogowego 
% Metoda niezmienności odpowiedzi impulsowej oraz przekszt. bilinearnego

clear; clc;
zp=0.01;                          % zafalowanie w paśmie przepustowym
zs=0.1;                           % zafalowanie w paśmie zaporowym
fp=2000; Wp=2*pi*fp;              % pulsacja graniczna pasma przepustowego
fs=2500; Ws=2*pi*fs;              % pulsacja graniczna pasma zaporowego 

                                  % zamiana zafalowań na wartości w [dB]
eps=(2*sqrt(zp))/(1-zp);
A=(1+zp)/zs;
Ap=-10*log10(1/(eps^2+1));        % w dB
As=-10*log10(1/A^2);              % w dB

[n,Wn]=buttord(Wp,Ws,Ap,As,'s');         % obliczanie rzędu f.a.                                             
[b,a]=butter(n,Wn,'s');                  % f.a. Butterwortha-transmitancja
%________________________________________________________________________ 

Fs=10000;                                 % częstotliwośc próbkowania
[bz,az]=impinvar(b,a,Fs);                % METODA 1  niezmienności odpowiedzi impulsowej
%[bz,az]=bilinear(b,a,Fs);               % METODA 2  przekszt. bilinearnego niestety poprawnie działa tylko w Matlabie

% Charakterystyka częstotliwościowa f.c. w Omega[cyfrowa];
[H,W]=freqz(bz,az,64);

M=abs(H);
subplot(3,1,1); plot(W,M); grid; title('Charakterystyka amplitudowa'); 
xlabel('\Omega','FontSize',14,'FontWeight','bold','Color','r');
subplot(3,1,2); plot(W,unwrap(angle(H))); grid; title('Charakterystyka fazowa'); 
xlabel('\Omega','FontSize',14,'FontWeight','bold','Color','r');
%uzyskano    Wp=? [rad/s]  Ws=? [rad/s] odczytaj z wykresu

% Odpowiedź impulsowa 
[h,t]=impz(bz,az,64);                  % 64 próbki odpowiedzi impulsowej

subplot(3,1,3); stem(t,h,'.'); grid; title('Odpowiedź impulsowa');
xlabel('numer próbki');


%DZIAŁANIE FILTRU Sprawdzenie
% f1=500; f2=2800;
% t=0:1/Fs:100/Fs;          % odstępy między próbkami wynikające z Fs
% x1=sin(2*pi*f1*t); x2=sin(2*pi*f2*t);
% x=x1+x2;                  % sygnał przed filtracja - spróbkowany z Fs 
% y=filter(bz,az,x);        % sygnał po filtracji cyfrowej
% 
% tt=0:0.00001:100/Fs;
% xx=sin(2*pi*f1*tt)+sin(2*pi*f2*tt);   % sygnał analogowy

% subplot(3,1,1); plot(tt,xx); title('Wejściowy sygnał analogowy'); grid;
% subplot(3,1,2); stem(t,x,'.'); title('Wejściowy sygnał dyskretny (po spróbkowaniu z Fs)'); grid;
% subplot(3,1,3);stem(t,y,'.'); title('Sygnał dyskretny po filtracji cyfrowej'); grid;


