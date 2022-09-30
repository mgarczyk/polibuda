	LJMP	START
	ORG	100H
START:
	;KOD PROGRAMU
	SETB RS1   ;RS1 = 1
	SETB RS0	 ;RS0 = 1 żeby korzystać z 3 banku zgodnie z tabelką w pdf
	MOV R0,#0
	MOV R1,#1
	MOV R2,#2
	MOV R3,#3
	MOV R4,#4
	MOV R5,#5
	MOV R6,#6
	MOV R7,#7
	LCALL LCD_CLR
	MOV A, 1FH

	LCALL WRITE_HEX


	LJMP	$ ;- pozosta� w p�tli
