	LJMP	START
	ORG	100H
START:
	CPL  P1.7
STOP:			;nie wykonuj innych dzia�a�
	LJMP	STOP	;- pozosta� w p�tli STOP
	NOP

