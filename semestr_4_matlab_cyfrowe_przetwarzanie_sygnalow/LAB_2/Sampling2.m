clear;

tmax=1;
t=0:0.001:tmax;
xa=cos(20*pi*t);                                                                                               % sygnał analogowy
 
Ts=0.05; N=round(tmax/Ts);   fs=1/Ts;                                                         % Próbkowanie
 
n=0:N; 
%n=0.4:N;
%n=0.5:N;
 
xp=cos(20*pi*n*Ts);                                                                                        % sygnał spróbkowany
 
subplot(1,2,1); plot(t,xa,n*Ts,xp,'r.','MarkerSize',15); grid;
ylabel('xa(t), xp(t)'); 
title('Próbkowanie sygnału analogowego xa z odstępem Ts');
 
                                                                                                                             % Odtwarzanie
 
xo=xp*sinc(fs*(ones(length(n),1)*t-(n*Ts)'*ones(1,length(t))));
 
subplot(1,2,2); plot(t,xo); grid;
ylabel('xo(t)'); title('Sygnał xo odtworzony z próbek');
 
%---------------------------------------------------------------------------------------------------------------------------------------
% Symulacje:

% a) n=0:N;
% b) n=0.4:N;
% c) n=0.5:N;

%---------------------------------------------------------------------------------------------------------------------------------------
% Zadania

% 6. Zarejestrować sygnały: analogowy,(xa), analogowy spróbkowany (xp)  i sygnał odtworzony (xo)     
    % przy różnych wartościach momentu rozpoczęcia próbkowania, czyli:
    % n=0:N     n=0.4:N     n=0.5:N
 
% 7. Zinterpretować otrzymane rezultaty
