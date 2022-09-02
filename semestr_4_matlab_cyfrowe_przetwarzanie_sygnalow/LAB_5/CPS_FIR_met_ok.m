% Metoda okien FIR
pkg load signal;
clear; clc;
Fs=8192;
[n,Wn,beta,ftype]=kaiserord([2000 2100],[1 0],[0.1 0.1],Fs); %cz�stotliwo�i zaporwe, maksymalne oscylacje, z lewej przepustowe, z prawej przepustowe
b=fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale'); %zmienna b zawiera ilo�c pr�bek

[H,f]=freqz(b,1,512,Fs);    

subplot(3,1,1); plot(f,abs(H)); grid; title('Charakterystyka amplitudowa'); 
xlabel('f [Hz]');

subplot(3,1,2); plot(f,unwrap(angle(H))); grid; title('Charakterystyka fazowa'); 
xlabel('f [Hz]');

subplot(3,1,3); stem(impz(b),'.'); grid; title('Odpowiedź impulsowa'); 
xlabel('Numer próbki');

%_______________________________________________________________________ 
%1. Odczytaj (z Matlab-Workspace) wymiar macierzy b oraz rząd filtru n

%2. Sprawdź parametry zaprojektowanego filtru:
%pasmo przenoszenia, pasmo zaporowe, 
%zafalowanie w paśmie przenoszenia, zafalowannie w paśmie zapoprwym,
%liczbę próbek odpowiedzi impulsowej.

%3. Sprawdź zależność rzędu filtru od zafalowań wypełniając tabelę

% 3.1. Zafalowania w paśmie przenoszenia                 Rząd filtru (n)
%      (zafalowanie w paśmie zaporowyn = 0.1)
%      _________________________________________________________________ 
%                               0.00001	
%                               0.0001	
%                               0.001	
%                               0.01                     183	
%                               0.1	
%                               0.3	
%                               0.5	
%_______________________________________________________________________

% 3.2. Zafalowania w paśmie zaporpwym                    Rząd filtru (n)
%      (zafalowania w paśmie przenoszenia = 0.01)
%      _________________________________________________________________
%                               0.0001	
%                               0.001	
%                               0.01	
%                               0.1                      183	
%                               0.3	
%                               0.5	
%                               0.6	

%_______________________________________________________________________

