% Filtr CAV, szum gaussowski
% o tych samych uprzednio dopasowanych wariancjach
clear; clc;

Fs=1000; t=0:0.1/Fs:0.2;
f=20;
x=sin(2*pi*f*t);

L=length(t);
vvar=1.7;                        % inne niż 0.0625  (rzędu: 0.0X, 0.X, 1.X)
%_________________________________________________________________________
                                                       % szum gaussowski
g=randn(1,L);
szum1=sqrt(vvar)*g;    ss1=mean(szum1);
szum11=szum1-ss1;
xn1=x+szum11;
subplot(3,1,1); plot(t,xn1); title('przykładowy sygnał zaszumiony xn'); grid;
%_________________________________________________________________________

% 4. Zbadać skuteczność redukcji szumu gaussowskiego w zależności od jego wariancji oraz
%    liczby uśrednianych sekwencji sygnału, jeśli występuje błąd fazy pomiędzy repetycjami:
%           a)liczba sekwencji - kilka n
%           b)liczba sekwencji - kilkadziesiąt n


z=0;
for n=1:50
    g=randn(1,L);
    szum1=sqrt(vvar)*g; ss1=mean(szum1);
    szum11=szum1-ss1;
	  x=sin(2*pi*f*t + 1.5*randn);	%bład fazy
    z=z+x+szum11;
   if n==5, a6=z/5;
    end
end
a60=z/60;

subplot(3,1,2); plot(t,a6);title('sygnał zaszumiony po uśrednieniu'); grid;
subplot(3,1,3); plot(t,a60);title('sygnał zaszumiony po znacznym uśrednieniu'); grid;

% Gdelta=x-a60; plot(t,Gdelta);

