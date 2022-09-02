clear; clc;
pkg load signal;
% 1.Wyjaśnij jakim typem filtru jest MAV (FIR, czy IIR) i dlaczego?
%fil=fvtool(B,1); działa w Matlabie
M=19;
B=ones(1,M)/M;                         % macierz współczynników filtru MAV
                                                       
% 2. Zbadaj własności filtru: charakterystykę amplitudową, fazową,odpowiedź impulsową
%    dla trzech wartoości M (4<M<20)

[H,W]=freqz(B,1,256);
y=impz(B);

subplot(3,1,1);plot(W/pi,abs(H));grid;   ylabel('Magniutda');
xlabel('\Omega/\pi','FontSize',16);

subplot(3,1,2);plot(W/pi,angle(H)*180/pi);grid;   ylabel('Faza');
xlabel('\Omega/\pi','FontSize',16);

subplot(3,1,3); stem(y); grid;    ylabel('Odpowiedź  impulsowa');
xlabel('n','FontSize',16)