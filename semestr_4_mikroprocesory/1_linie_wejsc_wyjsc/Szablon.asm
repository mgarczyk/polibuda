	LJMP	START
	ORG	100H
START:
	
	
	
STOP:
	MOV P1, #01111111B;Uruchomienie diody pod³¹czonej do 8 bitu na porcie 1
	MOV A, #5;Przenosimy wartosc 2 do akumulatora
	LCALL DELAY_100MS;Uruchami program opóŸniaj¹cy 25.6ms * A
	XRL P1, #10000000B ;Negujemy stan wy³¹czmy diodê
	MOV A, #1;Za ka¿dym uruchomieniem programu opóŸniaj¹cego trzeba podaæ coœ od nowa do akumulatora
	LCALL DELAY_100MS
			;nie wykonuj innych dzia³añ
	LJMP	STOP	;- pozostañ w pêtli STOP
	NOP

