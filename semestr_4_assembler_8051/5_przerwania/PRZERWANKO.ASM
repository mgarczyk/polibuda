;************************************************
; PRZERWANIA
;************************************************
LED EQU P1.7
;********* Ustawienie TIMERÓW *********
;TIMER 0
T0_G EQU 0 ;GATE
T0_C EQU 0 ;COUNTER/-TIMER
T0_M EQU 1 ;MODE (0..3)
TIM0 EQU T0_M+T0_C*4+T0_G*8
;TIMER 1
T1_G EQU 0 ;GATE
T1_C EQU 0 ;COUNTER/-TIMER
T1_M EQU 0 ;MODE (0..3)
TIM1 EQU T1_M+T1_C*4+T1_G*8
TMOD_SET EQU TIM0+TIM1*16
;50[ms] = 50 000[ms]*(11.0592[MHz]/12) =
; = 46 080 cykli = 180 * 256
TH0_SET EQU 256-36
TL0_SET EQU 0
;**************************************
	LJMP START
;********* Przerwanie Timer 0 *********
	ORG 0BH
	MOV TH0,#TH0_SET ;TH0 na 10ms
	LCALL RETI_FUNCTION
	RETI
;**************************************
	ORG 100H
START:
	LCALL LCD_CLR
	MOV TMOD,#TMOD_SET ;Timer 0 liczy czas
	MOV TH0,#TH0_SET ;Timer 0 na 10ms
	MOV TL0,#TL0_SET
	SETB EA ;wlacz zezwolenie ogólne
	;na przerwania
	SETB ET0 ;wlacz zezwolenie na
	;przerwanie od Timera 0
	MOV R2,#0
	MOV A,R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#':'
	LCALL WRITE_DATA
	MOV R1,#0
	MOV A,R1
	LCALL TO_BCD
	LCALL WRITE_HEX
	
STOPER_START:
	LCALL WAIT_KEY
	CJNE A,#15,STOPER_START
	SETB TR0 ;start Timera 0

STOPER_START_STOP:
	LCALL WAIT_KEY ;czekaj na klawisz
	CJNE A,#15,DALEJ
	CLR TR0
	LCALL WAIT_KEY ;czekaj na klawisz
	CJNE A,#15,DALEJ
	LJMP START
	
DALEJ:
	SJMP STOPER_START_STOP
	SJMP $ ;koniec pracy
	;programu glównego

RETI_FUNCTION:
	LCALL LCD_CLR
	CJNE R1,#100, DISP_TIME
	INC R2
	MOV R1,#0
	LCALL DISP_TIME
	


DISP_TIME:
	MOV A,R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#':'
	LCALL WRITE_DATA
	INC R1
	MOV A,R1
	LCALL TO_BCD
	LCALL WRITE_HEX
	RET ;powrót z podprogramu
	NOP


	
TO_BCD:
	;ZAMIANA NA BCD -POCZ¥TEK
	MOV B,#10; DZIELNIK
	DIV AB; WYDZIELAMY CYFRE DZIESIATEK
	SWAP A; PRZESUWAMY CYFRÊ DZIESI¥TEK NA WY¯SZY 4 BITY
	ORL A,B; DODAJEMY CYFRÊ JEDNOŒCI
	;ZAMIANA NA BCD -KONIEC
	RET
	NOP