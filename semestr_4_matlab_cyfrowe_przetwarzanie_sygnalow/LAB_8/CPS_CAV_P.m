% Filtr CAV, szum gaussowski i o rozkładzie równomiernym
% o tych samych uprzednio dopasowanych wariancjach

clear; clc;

Fs=1000; t=0:0.1/Fs:0.2;
f=20;
x=sin(2*pi*f*t);

L=length(t);
vvar=0.07;                        % inne niż 0.0625  (rzędu: 0.0X, 0.X, 1.X)

%_________________________________________________________________________
                                                        % szum prostokątny
 p=rand(1,L);
 szum2=sqrt(12*vvar)*(p-0.5);    ss2=mean(szum2);
 szum22=szum2-ss2;
 xn2=x+szum22;
 subplot(3,1,1); plot(t,xn2); title('przykładowy sygnał zaszumiony xn'); grid;
%_________________________________________________________________________

% 3. Zbadać skuteczność redukcji szumu prostokątnego (rozkład równomierny) w zależności od jego wariancji oraz
%    liczby uśrednianych sekwencji sygnału
%           a)liczba sekwencji - kilka n
%           b)liczba sekwencji - kilkadziesiąt n


z=0;
for n=1:5
     p=rand(1,L);
     szum2=sqrt(12*vvar)*(p-0.5);   ss2=mean(szum2);
     szum22=szum2-ss2;
     z=z+x+szum22;
   if n==5, a6=z/5;
    end
end
a60=z/60;

subplot(3,1,2); plot(t,a6);title('sygnał zaszumiony po uśrednieniu'); grid;
subplot(3,1,3); plot(t,a60);title('sygnał zaszumiony po znacznym uśrednieniu'); grid;

% Gdelta=x-a60; plot(t,Gdelta);

