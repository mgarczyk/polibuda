	LJMP	START
	ORG	100H
START:
	;zapisywanie
	CLR RS1 ;bank 0
	CLR RS0
	MOV R7, #0
	CLR RS1
	SETB RS0
	MOV R7, #1 ;bank 1
	SETB RS1
	CLR RS0
	MOV R7, #2 ;bank 2
	SETB RS1
	SETB RS0
	MOV R7, #3 ;bank 3
	;wyświetlanie bank 0
	CLR RS1 ;bank 0
	CLR RS0
	LCALL LCD_CLR ;wyczyść ekran
	MOV A, R7
	LCALL WRITE_HEX ;wypisz zawartość akumulatora na ekran
	;wyświetlanie bank 1
	CLR RS1
	SETB RS0 ;bank 1
	MOV A, R7
	LCALL WRITE_HEX 
	;wyświetlanie bank 2
	SETB RS1 ;bank 2
	CLR RS0
	MOV A, R7
	LCALL WRITE_HEX 
	;wyświetlanie bank 3
	SETB RS1
	SETB RS0 ;bank 3
	MOV A, R7
	LCALL WRITE_HEX 
	
	
	
	
	


	




	LJMP	$ ;- pozosta� w p�tli
