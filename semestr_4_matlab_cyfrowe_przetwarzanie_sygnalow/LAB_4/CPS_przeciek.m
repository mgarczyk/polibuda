

% A. Wp³yw obciêcia na rozmiar przecieku 

 clear; clc;
 fs=30; fx=3;                                                        
 
 N0=100;                         % bez przecieku
 t0=0:1/fs:(N0-1)/fs;
 y0=sin(2*pi*t0*fx);
 f0=fs*(0:length(y0)-1)/length(y0);
 Y0=fft(y0);
 
 N=95;                           % z przeciekiem
 t=0:1/fs:(N-1)/fs;
 y=sin(2*pi*t*fx);
 f=fs*(0:length(y)-1)/length(y);
 Y=fft(y);
 
 subplot(2,1,1); stem(f0,(2/N0)*abs(fft(y0)),'.');grid; legend('N_0=100','Location','north');
 xlabel('f[Hz]');ylabel('Y0');
 subplot(2,1,2); stem(f,(2/N)*abs(fft(y)),'.');grid;legend('N=?','Location','north');
 xlabel('f[Hz]');ylabel('Y')


% A1. ZnaleŸæ wartoœæ N przy której dochodzi do maksymalnego przecieku; 
%     N z przedzia³u [91,99]
% A2. Okreœliæ czêstotliwoœæ pr¹¿ka w widmie Y0, czyli dla N0=100
% A3. Okreœliæ czêstotliwoœæ dwóch najwiêkszych pr¹¿ków w widmie Y 
%     dla przypadku widma z maksymalnym przeciekiem
%_____________________________________________________________________ 




 
