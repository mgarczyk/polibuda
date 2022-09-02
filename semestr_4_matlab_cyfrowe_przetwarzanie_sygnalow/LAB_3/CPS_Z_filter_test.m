clear; 
pkg load signal;

fz=100; Rz=1;                        %częstotliwość w Hz i promień zera
fp=30; Rp=0.1                      %częstotliwość w Hz i promień bieguna

fs=1000;                             %częstotliwość próbkowania w Hz

Omega_z=2*pi*(fz/fs);                %kąt zera
Omega_p=2*pi*(fp/fs);                %kąt bieguna

z=Rz*exp(1i*Omega_z);                %zero
p=Rp*exp(1i*Omega_p);                %biegun
z=[z conj(z)];                       %dwa zera
p=[p conj(p)];                       %dwa bieguny

[B,A]=zp2tf(z',p',1);            %oblicza współczynniki transmitancji {B,A}
                                 %na podstawie {z,p}
                             
x=0:1/fs:0.5;
yp = sin(2*pi*50*x);
yz = sin(2*pi*fz*x);
ys= yp + yz; %suma sygnalow
y= filter(B,A,ys);%filtracja

subplot(4,1,1); plot(yp); title('Sygnal o czestotliwosci w pasmie przepustowym'); 
ylabel('yp(n)','FontSize',12); grid;
subplot(4,1,2); plot(yz); title('Sygnal o czestotliwosci w pasmie zaporowym');
ylabel('yz(n)','FontSize',12); grid;
subplot(4,1,3); plot(ys); title('Suma sygnalow');
ylabel('ys(n)','FontSize',12); grid;
subplot(4,1,4); plot(y); title('Suma sygnalow po filtracji'); 
xlabel('numer probki'); ylabel('y(n)','FontSize',12); grid;

% A. Projektowanie filtru transmitancja z
% A1. Zaprojektuj filtr dolnoprzepustowy tłumiący częstotliwość 100 Hz i 
%     przepuszczający częstotliwość 30 Hz przy częstotliwości próbkowania 1 kHz,
%     a zafalowania odpowiedzi impulsowej kończą się przed 100 próbką

% Należy użyć parametrów z części A 
% B. Testowanie filtru transmitancja z 
% B1. W sprawozdaniu zapisz wzór transmitancji H(z), na podstawie wartości macierzy A i B
% B2. Podłącz sygnał (suma dwóch sinusoid) do wejścia filtra (funkcja filter(,,))
% B3. Porównaj sygnał wejsciowy i wyjściowy, jak wpływają na filtrację prametry projektowe (proszę zwrócić uwagę na promienie)