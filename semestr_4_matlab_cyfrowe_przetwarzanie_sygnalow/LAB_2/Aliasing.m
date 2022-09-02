clear; 

 
t=0:0.01:5;
f=-10:0.001:10;
Ts=1/4;   fs=1/Ts;  % odstęp między próbkami;   częstotliwość próbkowania
 
E=1;                % parametr
x=exp(-t/E);                                                                                                              % sygnał analogowy
X=1./(1/E+1i*2*pi*f);  % Widmo sygnału analogowego

% Widmo sygnału spróbkowanego 
Xs=zeros(size(f));
for n=0:10*E/Ts
    Xs=Xs+exp(-n*Ts/E)*exp(-1i*2*pi*f*n*Ts);
end
 
subplot(3,1,1); plot(t,x);title('x(t)');grid;
subplot(3,1,2); plot(f,abs(X));xlabel('f(Hz)');title('Widmo modułu X(f)');grid;
subplot(3,1,3); plot(f,abs(Xs));xlabel('f(Hz)');title('Widmo modułu Xs(f)');grid;

 
%---------------------------------------------------------------------------------------------------------------------------------------
% Symulacje:

%	a) E=1		t=0:0.01:5		Ts =1/4,   Ts =1/2,   Ts =1

%	b) E=10	t=0:0.01:50		Ts =1/4,   Ts =1/2,   Ts =1

%---------------------------------------------------------------------------------------------------------------------------------------
% Zadania

% 1. Określić częstotliwości próbkowania jeżeli odstęp Ts między próbkami
%      równa się: 1/4, 1/2, 1 sekundy
% 2. Odczytać w każdym przypadku
%                      a) wartość Xs w punkcie fs/2
%                      b) maksymalną wartość Xs w pukcie f=0
 
% 3. Jaki jest wpływ częstotliwości próbkowania na wartość aliasingu?
% 4. Od czego zależy lokalizacja "repetycji" w widmie sygnału spróbkowanego?
 
% 5. Podać przyczynę zmiany wartości Xs (= w osi Y) gdy zmienia się Ts 
% 6. Jaka jest relacja między czasem trwania sygnału x(t) a szerokością jego widma?

% 7. Wyliczyć transformatę Fouriera sygnału analogowego x(t)

