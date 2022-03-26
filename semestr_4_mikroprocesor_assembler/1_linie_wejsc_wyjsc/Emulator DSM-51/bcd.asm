	LJMP	START
	ORG	100H
START:
	LCALL 	LCD_CLR
	MOV	A,#24H
	LCALL 	WRITE_HEX
	MOV	A,#'='
	LCALL 	WRITE_DATA
	MOV	A,#24H
	LCALL 	TO_BCD
	LCALL 	WRITE_HEX

	LJMP	$ ;- pozosta� w tym miejscu

TO_BCD:
	;ZAMIANA NA BCD -POCZ�TEK
	MOV B,#10; DZIELNIK
	DIV AB; WYDZIELAMY CYFRE DZIESIATEK
	SWAP A; PRZESUWAMY CYFR� DZIESI�TEK NA WY�SZY 4 BITY
	ORL A,B; DODAJEMY CYFR� JEDNO�CI
	;ZAMIANA NA BCD -KONIEC
	RET
	NOP