	LJMP	START
	ORG	100H
START:
	
	
	
STOP:
	MOV P1, #01111111B;Uruchomienie diody pod��czonej do 8 bitu na porcie 1
	MOV A, #5;Przenosimy wartosc 2 do akumulatora
	LCALL DELAY_100MS;Uruchami program op�niaj�cy 25.6ms * A
	XRL P1, #10000000B ;Negujemy stan wy��czmy diod�
	MOV A, #1;Za ka�dym uruchomieniem programu op�niaj�cego trzeba poda� co� od nowa do akumulatora
	LCALL DELAY_100MS
			;nie wykonuj innych dzia�a�
	LJMP	STOP	;- pozosta� w p�tli STOP
	NOP

