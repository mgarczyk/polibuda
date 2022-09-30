	LJMP	START
	ORG	100H
START:
	MOV R0, #40H
	MOV R1, #10
LOOP:
		MOV @R0, #0
		MOV A, R0
		LCALL WRITE_HEX ;wyświelamy koljne adresy pamięci
		INC R0
	DJNZ R1, LOOP ;pętla od 10 do 1, licznik zmniejsza się z każdym wykonaniem
	
	
	


	




	LJMP	$ ;- pozosta� w p�tli
	NOP