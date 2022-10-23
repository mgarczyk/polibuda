	LJMP	START
	ORG	100H
START:
	CPL  P1.7
STOP:			;nie wykonuj innych dzia³añ
	LJMP	STOP	;- pozostañ w pêtli STOP
	NOP

