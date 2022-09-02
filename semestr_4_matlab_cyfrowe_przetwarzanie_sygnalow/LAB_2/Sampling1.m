clear;

tmax=1;
t=0:0.001:tmax;
xa=cos(20*pi*t);     % sygnał analogowy
 
 Ts=0.01;                                                                                                                  % odstęp między próbkami  
% Ts=0.05; 
% Ts=0.1; 
 
fs=1/Ts;                                                                                                                  % częstotliwość próbkowania
N=round(tmax/Ts); n=0:N;
 
xp=cos(20*pi*n*Ts); % sygnał spróbkowany
 
subplot(1,2,1); plot(t,xa,n*Ts,xp,'r.','MarkerSize',15); grid;
ylabel('xa(t), xp(t)'); title('Próbkowanie sygnału analogowego xa z odstępem Ts');

 
                                                                                                                               % sygnał odtworzony z próbek
                                                              
xo=xp*sinc(fs*(ones(length(n),1)*t-(n*Ts)'*ones(1,length(t))));
 
subplot(1,2,2); plot(t,xo);
ylabel('xo(t)'); title('Sygnał odtworzony z próbek');grid;

%---------------------------------------------------------------------------------------------------------------------------------------
% Symulacje:

% a) Ts=0.01;                                     % odstęp między próbkami  
% b) Ts=0.05; 
% c) Ts=0.1; 

%---------------------------------------------------------------------------------------------------------------------------------------
% Zadania

% 1. Obliczyć częstotliwość f i okres T sygnału analogowego xa 
% 2. Ustalić relacje między odstępem między próbkami Ts a okresem sygnału analogowego T, 
     % w każdym przypadku
% 3. Ustalić relacje między częstotliwością próbkowania fs a częstotliwością sygnału analogowego f, 
     % w każdym przypadku 
 
% 4. Zarejestrować sygnały spróbkowane oraz odtworzone i zinterpretować otrzymane rezultaty
% 5. Wyznaczyć częstotliwość i amplitudę sygnału analogowego odtworzonego z próbek 
     % (na podstawie centralnej części rys)
 
   % Sygnał jest w przybliżeniu poprawnie odtworzony z próbek, jeżeli jego amplituda i częstotliwość 
   % są takie jak w pierwotnym sygnale analogowym

