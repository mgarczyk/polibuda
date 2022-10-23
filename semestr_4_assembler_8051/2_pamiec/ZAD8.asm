        LJMP	START
              ORG	   100H
START:
  MOV R0,#18H
	MOV R1,#0  ;start pętli R1=0
LOOP:
	MOV @R0,01H
	INC R0
	INC R1     ;zwiększamy R1
	CJNE R1,#8,LOOP ;każdy skok zwiększa R1 o 1 i dopóki R1<8 to skacz

        LCALL LCD_CLR
        MOV A,1DH
        LCALL WRITE_HEX
STOP:			;nie wykonuj innych dzia�a�
	      LJMP	STOP	;- pozosta� w p�tli STOP
