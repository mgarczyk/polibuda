LED EQU P1.7
;********* Ustawienie TIMERów *********
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

;50[ms] = 50 000[ŠS]*(11.0592[MHz]/12) =
; = 46 080 cykli = 180 * 256
TH0_SET EQU 256-180
TL0_SET EQU 0
;**************************************
	LJMP START
	ORG 100H
START:
	MOV TMOD,#TMOD_SET ;Timer 0 liczy czas
	MOV TH0,#TH0_SET ;Timer 0 na 50ms
	MOV TL0,#TL0_SET
	SETB TR0 ;start Timera
	       ; POBIERANIE GODZINY
	;godziny
	LCALL WPROWADZ
	MOV R2, A
	LCALL LCD_CLR
	MOV A, R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	;minuty
	LCALL WPROWADZ
	MOV R3, A
	LCALL LCD_CLR
	MOV A, R3
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	;sekundy
	LCALL WPROWADZ
	MOV R4, A
	LCALL LCD_CLR
	MOV A, R4
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	        ;wyswietlanie godziny startu 
	LCALL LCD_CLR
	MOV A, R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A, #':'
	LCALL WRITE_DATA
	MOV A, R3
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A, #':'
	LCALL WRITE_DATA
	MOV A, R4
	LCALL TO_BCD
	LCALL WRITE_HEX
	
	LCALL WAIT_ENTER_NW
	LCALL LCD_CLR
	;pobieranie godziny koncowej
	LCALL WPROWADZ
	MOV R5, A
	LCALL LCD_CLR
	MOV A, R5
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	;minuty
	LCALL WPROWADZ
	MOV R6, A
	LCALL LCD_CLR
	MOV A, R6
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	
	;wyswietlanie godziny koncowej
	LCALL LCD_CLR
	MOV A, R5
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A, #':'
	LCALL WRITE_DATA
	MOV A, R6
	LCALL TO_BCD
	LCALL WRITE_HEX
	
	
LOOP: ;Pętla mrugania diody TEST
	CPL LED
	MOV R7,#20 ;odczekaj czas 20*50ms=1s
TIME_N50:
	JNB TF0,$ ;czekaj, aż Timer 0
	;odliczy 50ms
	MOV TH0,#TH0_SET ;TH0 na 50ms
	CLR TF0 ;zerowanie flagi timera 0
	DJNZ R7,TIME_N50 ;odczekanie N*50ms
	SJMP LOOP
STOP:			;nie wykonuj innych dzia�a�
	LJMP	STOP	;- pozosta� w p�tli STOP
	NOP
	
WPROWADZ:
	LCALL LCD_CLR
	LCALL WAIT_KEY ; Wczytaj liczbę dziesiątek
	MOV B,#10 ; pomnóż
	MUL AB ; przez 10
	MOV R1,A ; zapisz liczbę w R1
	LCALL WAIT_KEY ;wczytaj liczbę jedności
	ADD A,R1 ; dodaj liczbę jedności do R1
	RET ; wyjdź z podprogramu. Wynik w A.
	
TO_BCD:
	;ZAMIANA NA BCD -POCZ�TEK
	MOV B,#10 ;DZIELNIK
	DIV AB ;WYDZIELAMY CYFRE DZIESIATEK
	SWAP A
	ORL A,B ;DODAJEMY CYFR� JEDNO�CI
	 ;ZAMIANA NA BCD -KONIEC
	RET
	NOP