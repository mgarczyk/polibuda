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
TH0_SET EQU 256-180
TL0_SET EQU 0
;**************************************
	LJMP START
	ORG 100H
START:
	LCALL LCD_INIT
	;godzina
	LCALL WAIT_KEY
	MOV R1, A
	LCALL WRITE_HEX 
	LCALL WAIT_KEY 
	MOV R2, A
	LCALL LCD_CLR
	MOV A, R1
	SWAP A   
	ADD A,R2 
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW 
	LCALL LCD_CLR
	MOV A, R1
	MOV B,#10
	MUL AB
	ADD A, R2
	MOV R1, A
	;minuta
	LCALL WAIT_KEY
	MOV R2, A
	LCALL WRITE_HEX 
	LCALL WAIT_KEY 
	MOV R3, A
	LCALL LCD_CLR
	MOV A, R2
	SWAP A   
	ADD A,R3 
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW 
	LCALL LCD_CLR
	MOV A, R2
	MOV B,#10
	MUL AB
	ADD A, R3
	MOV R2, A
	;sekunda
	LCALL WAIT_KEY
	MOV R3, A
	LCALL WRITE_HEX 
	LCALL WAIT_KEY 
	MOV R4, A
	LCALL LCD_CLR
	MOV A, R3
	SWAP A   
	ADD A,R4 
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW 
	LCALL LCD_CLR
	MOV A, R3
	MOV B,#10
	MUL AB
	ADD A, R4
	MOV R3, A
	;godzina alarmu 
	MOV A, #'A'
	LCALL WRITE_DATA
	MOV A, #' '
	LCALL WRITE_DATA
	LCALL WAIT_KEY
	MOV R4, A
	LCALL WRITE_HEX 
	LCALL WAIT_KEY 
	MOV R5, A
	LCALL LCD_CLR
	MOV A, #'A'
	LCALL WRITE_DATA
	MOV A, #' '
	LCALL WRITE_DATA
	MOV A, R4
	SWAP A   
	ADD A,R5 
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW 
	LCALL LCD_CLR
	MOV A, R4
	MOV B,#10
	MUL AB
	ADD A, R5
	MOV R4, A
	;minuta alarmu 
	MOV A, #'A'
	LCALL WRITE_DATA
	MOV A, #' '
	LCALL WRITE_DATA
	LCALL WAIT_KEY
	MOV R5, A
	LCALL WRITE_HEX 
	LCALL WAIT_KEY 
	MOV R6, A
	LCALL LCD_CLR
	MOV A, #'A'
	LCALL WRITE_DATA
	MOV A, #' '
	LCALL WRITE_DATA
	MOV A, R5
	SWAP A   
	ADD A,R6 
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW 
	LCALL LCD_CLR
	MOV A, R5
	MOV B,#10
	MUL AB
	ADD A, R6
	MOV R5, A
	
	MOV R6,#0 ;licznik dzwonienia 
; R1 - godziny, R2 - minuty, R3 - sekundy, R4 - godzina alarmu, R5 - minuta alarmu 

	MOV TMOD,#TMOD_SET 
	MOV TH0,#TH0_SET 
	MOV TL0,#TL0_SET
	SETB TR0 
LOP: 
	MOV R7,#20
TIME_N50:
	JNB TF0,$
	MOV TH0,#TH0_SET 
	CLR TF0
	DJNZ R7,TIME_N50 
	INC R3
	CJNE R3, #60, NEXT_MINUTE
	INC R2
	MOV R3,#0
NEXT_MINUTE: 
	CJNE R2, #60, NEXT_HOUR
	INC R1
	MOV R2, #0
NEXT_HOUR:
	CJNE R1, #24, NEXT_DAY
	MOV R1,#0
	MOV R2,#0
	MOV R3,#0
NEXT_DAY:
	CJNE R6, #0, ALARM_PLAYING
	LCALL CHECK_ALARM
	LCALL WRITE_TIME
	SJMP LOP
ALARM_PLAYING:
	LCALL PLAY_ALARM
	LCALL WRITE_TIME
	SJMP LOP

STOP:		
	LJMP	STOP
	NOP


;wyświetlanie aktualnego czasu
WRITE_TIME:
	LCALL LCD_CLR
	MOV A, R1
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#':'
	LCALL WRITE_DATA
	MOV A, R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#':'
	LCALL WRITE_DATA
	MOV A, R3
	LCALL TO_BCD
	LCALL WRITE_HEX
	RET
	NOP
	
;sprawdzenie czy juz czas na alarm
CHECK_ALARM:
	MOV A, R1
	MOV B, R4
	CLR C
	SUBB A,B
	CJNE A, #0, CONTINUE_IF_NOT_EQUAL 
	CJNE R3, #0, CONTINUE_IF_NOT_EQUAL 
	MOV A, R2
	MOV B, R5
	CLR C
	SUBB A,B
	CJNE A, #0, CONTINUE_IF_NOT_EQUAL 
	;trzeba zagrac alarm
	CLR P1.7
	MOV R6,#1
CONTINUE_IF_NOT_EQUAL:
	RET 
	NOP
;granie alarmu 
PLAY_ALARM: 
	CJNE R6, #3, INC_SEC ;czas alarmu
	MOV R6, #0
	SETB P1.7
	RET
	NOP

INC_SEC:
	INC R6 
	RET 
	NOP
;wypisywanie bcd 
TO_BCD:
	MOV B,#10
	DIV AB
	SWAP A
	ORL A,B
	RET
	NOP