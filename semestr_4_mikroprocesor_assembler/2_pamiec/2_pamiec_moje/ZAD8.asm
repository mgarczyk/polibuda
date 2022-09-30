	LJMP	START
	ORG	100H
START:
	MOV R0,#18H ;domyslne R1 i R0 z banku 0
	MOV R1,#0
LOOP:
	MOV @R0,01H
	INC R1
	INC R0

	CJNE R0,#8,LOOP
	LCALL LCD_CLR
	SETB RS1
	SETB RS0
	MOV A,R2  ;odczytanie bitu z rejestru R2, bank 3
	LCALL WRITE_HEX
	



	LJMP	$ ;- pozosta� w p�tli
	NOP