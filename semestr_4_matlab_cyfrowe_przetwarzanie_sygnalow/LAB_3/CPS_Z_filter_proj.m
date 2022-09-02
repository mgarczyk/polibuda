clear;
pkg load signal;

fz=100; Rz=0.9;                         %częstotliwość w Hz i promień zera
fp=30;  Rp=0.95 %ZWI�KSZ tu na 1.05 i b�dzie niestabilny promie� wi�kszy od 1 %częstotliwość w Hz i promień bieguna

fs=1000;                             %częstotliwość próbkowania w Hz

Omega_z=2*pi*(fz/fs);                %kąt zera
Omega_p=2*pi*(fp/fs);                %kąt bieguna

z=Rz*exp(1i*Omega_z);                %zero
p=Rp*exp(1i*Omega_p);                %biegun
z=[z conj(z)]                       %dwa zera
p=[p conj(p)]                       %dwa bieguny

[B,A]=zp2tf(z',p',1)            %oblicza współczynniki transmitancji {B,A}
                                 %na podstawie {z,p}

[H,w]=freqz(B,A,1024,fs);   %charakterystyka częstotliwościowa

x=[1 zeros(1,512)];        %dyskretny impuls jednostkowy (delta Kroneckera)
y=filter(B,A,x);           %odpowied impulsowa

subplot(2,1,1); plot(w,abs(H)); title('Charakterystyka amplitudowa'); 
xlabel('f [Hz]'); ylabel('/ H /','FontSize',12); grid;
subplot(2,1,2); plot(y); title('Odpowiedź impulsowa'); 
xlabel('numer probki'); ylabel('h(n)','FontSize',12); grid;

% A. Projektowanie filtru transmitancja z
% 
% A1. Zaprojektuj filtr dolnoprzepustowy tłumiący częstotliwość 100 Hz i 
%     przepuszczający częstotliwość 30 Hz przy częstotliwości próbkowania 1 kHz,
%     a zafalowania odpowiedzi impulsowej kończą się przed 100 próbką
% A2. Zbadaj charakterystyką czstotliwościową układu i odpowiedzi impulsowej
% A3. Zmodyfikuj transmitancję układu tak by układ był niestabliny
% A4. Zbadaj odpowiedź impulsową i charakterystykę częstotliwościową układu
%     Porównaj je z tymi, które uzyskano w układzie stabilnym
% 

