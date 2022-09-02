clear; clc;
pkg load signal;
pkg load image;


function y = my_medfilt1(x, n)  %implementacja

y = zeros(1, length(x)); %wektor przechowuj�cy wyniki, na pocz�tku same zera

x = padarray(x, [0, floor(n/2)], 0, 'both');

%przesuwanie okna wzd�u� pr�bek
for i = 1:length(y)
    y(i) = median(x(i:i+n-1));  %obliczanie wyniku, mediany kolejnych okien
end

end

 
t=0:0.01:2;
x=sin(2*pi*t);                                    % sygnał bez zakłóceń
                                                  % zakłócenia 
xz=zeros(1, length(t));   
xz(15)=-2; 
xz(37)=0.8; 
xz(90)=1.5; xz(91)=1.5; xz(92)=1.5; 
xz(115)=-2; xz(114)=-2.5; 
xz(137)=0.8; 
xz(190)=1.5;                                         

xxz=x+xz;                  % xxz sygnał wejściowy z zakłóceniami impulsowymi 
N=2;                       % długość filtru, nieparzysta (N=3,...,N<10) 
                           % długość filtru, parzysta (N=2,...,N<10) 
 
y=medfilt1(xxz,N);                    % filtr medianowy MED 


b=ones(1,N)/N;                        % filtr typu "ruchoma średnia" - MAV
mav=filter(b,1,xxz); 
y_my=my_medfilt1(xxz,N);                    % filtr medianowy MED 
 
subplot(4,1,1);  plot(t,xxz); axis ([0 2 -2 2]); title('Sygnał wejściowy'); grid;
subplot(4,1,2);  plot(t,y); axis ([0 2 -2 2]); title('Sygnał po filtracji MED za pomoc� funkcji z octave'); grid;
subplot(4,1,3);  plot(t,y_my); axis ([0 2 -2 2]); title('Sygnał po filtracji MED, w�asna funkcja'); grid;
subplot(4,1,4);  plot(t,mav); axis ([0 2 -2 2]); title('Sygnał po filtracji MAV'); grid;







%2. Jaki jest wpływ długości filtru N na efektywność filtracji medianowej
%   N nieparzysta (trzy wartości), N parzysta (trzy wartości)
%   wartości parzysta/nieparzysta - wybierane sąsiednio możliwe kombinacje 2/3 4/5 6/7 8/9
%3. Porównaj efektywność redukcji zakłóceń impulsowych w wyniku 
%   filtracji MED i MAV 


%xz=zeros(1, length(t)); xz(9)=-2; xz(37)=1; xz(109)=-2; xz(137)=1; xz(194)=-2; xz(195)=1;
