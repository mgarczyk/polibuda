	LJMP	START
	ORG	100H
START:
	SETB RS1
	SETB RS0
	MOV R0,#0
	MOV R1,#1
	MOV R2,#2
	MOV R3,#3
	MOV R4,#4
	MOV R5,#5
	MOV R6,#6
	MOV R7,#7

	LCALL LCD_CLR
	MOV A,19H ;przenosi do akumulatora wartosc rejestru R3, a nastepnie wyswietla
	LCALL WRITE_HEX
	



	LJMP	$ ;- pozosta� w p�tli
	NOP