;************************************************
; PRZERWANIA
;************************************************

LED	EQU	P1.7

;********* Ustawienie TIMERÓW *********
;TIMER 0
T0_G	EQU	0	;GATE
T0_C	EQU	0	;COUNTER/-TIMER
T0_M	EQU	1	;MODE (0..3)
TIM0	EQU	T0_M+T0_C*4+T0_G*8
;TIMER 1
T1_G	EQU	0	;GATE
T1_C	EQU	0	;COUNTER/-TIMER
T1_M	EQU	0	;MODE (0..3)
TIM1	EQU	T1_M+T1_C*4+T1_G*8

TMOD_SET	EQU	TIM0+TIM1*16

;50[ms] = 50 000[ms]*(11.0592[MHz]/12) =
;	= 46 080 cykli = 180 * 256
TH0_SET		EQU	256-180
TL0_SET		EQU	0
;**************************************

	LJMP	START

;********* Przerwanie Timer 0 *********
	ORG	0BH
	MOV	TH0,#TH0_SET		;TH0 na 50ms
	DJNZ	R7,NO_1SEK		;czy minê³a 1 sek(sprawdzane co 50ms)
	LCALL	ZMIEN_LED		;wykonywane co 1 sek
NO_1SEK:
	RETI

;**************************************
	ORG	100H
START:
	LCALL	LCD_CLR
	MOV	TMOD,#TMOD_SET	;Timer 0 liczy czas
	MOV	TH0,#TH0_SET		;Timer 0 na 50ms
	MOV	TL0,#TL0_SET
	
	SETB	EA		;w³¹cz zezwolenie ogólne
				;na przerwania
	SETB	ET0		;w³¹cz zezwolenie na
				;przerwanie od Timera 0
	
	MOV	R7,#20		;zainicjuj R7: 20*50ms=1s
	SETB	TR0		;start Timera 0
	
DISP_LOOP:
	LCALL 	WAIT_KEY	;czekaj na klawisz
	LCALL 	WRITE_HEX	;wyœwietl wartoœæ na LCD
	SJMP 	DISP_LOOP
	SJMP	$		;koniec pracy
				;programu g³ównego

ZMIEN_LED:
	MOV	R7,#20 		;ustaw ponownie R7:20*50ms=1s
	CPL	LED 		;mruganie diody TEST
	RET			;powrót z podprogramu
	NOP
	