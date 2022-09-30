	LJMP	START
	ORG	100H
START:
		MOV R0,#40H ;adres początkowy od którego zaczynamy zerować
		MOV R1, #10 ;odwrócona pętla zaczynamy od 10 i cofaamy się do 1, każdy skok zmniejsza licznik
LOOP:
			MOV @R0,#0 ;zerowanie
			INC R0

   	DJNZ R1,LOOP ;każde wykonanie skoku zmienia wartość argumentu

STOP:
	LJMP	STOP
	NOP
