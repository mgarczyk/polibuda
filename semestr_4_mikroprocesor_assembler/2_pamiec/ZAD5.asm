	LJMP	START
	ORG	100H
START:
	CLR RS1 ;z tabeli prawdy banków
	CLR RS0 ;za pomocą flag RS1 i RS0 wybieramy bank
	MOV R1,#0 ;przypisujemy coś do jednego z rejestrów banku itd.
	CLR RS1
	SETB RS0
	MOV R1,#1
	SETB RS1
	CLR RS0
	MOV R1,#2
	SETB RS1
	SETB RS0
	MOV R1,#3


	;WYSWIETLANIE (wyświetlą się numery poszczególnych banków)
	CLR RS1
	CLR RS0
	LCALL LCD_CLR
	MOV A,R1
	LCALL WRITE_HEX

	CLR RS1
	SETB RS0
	MOV A,R1
	LCALL WRITE_HEX

	SETB RS1
	CLR RS0
	MOV A,R1
	LCALL WRITE_HEX

	SETB RS1
	SETB RS0
	MOV A,R1
	LCALL WRITE_HEX




	LJMP	$ ;- pozosta� w p�tli
