	LJMP START
	ORG	100H
START:
	;zapisanie danych
	LCALL LCD_CLR
	LCALL WAIT_KEY
	PUSH ACC
	MOV R1,A ;pobranie pierwszej liczby
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	LCALL LCD_CLR
	LCALL WAIT_KEY
	PUSH ACC
	MOV R2,A  ;pobranie drugiej liczby
	LCALL WRITE_HEX
	LCALL WAIT_ENTER_NW
	LCALL LCD_CLR
	;pobranie ze stosu

	;sprawdzenie operacji
	LCALL WAIT_KEY
	CJNE A,#10,ODEJM ;SPRAWDZ CZY DODAWANIE if akumulator=='A' dodaj, elese sprawdzaj dalej
	LCALL LCD_CLR
	MOV A, R1             ;wyświetlanie liczb i znaku operacji oraz znaku =, znaki za pomocą LCALL WRITE_DATA
	LCALL WRITE_HEX
	MOV A, #'+'
	LCALL WRITE_DATA
	MOV A,R2
	LCALL WRITE_HEX
	MOV A, #'='
	LCALL WRITE_DATA
	POP 32H
	POP 31H
	MOV A, 31H  ;przeniesienie pierwszej liczby do akumulatra
	ADD A, 32H  ;dodanie drugiej
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_KEY
	LJMP START

ODEJM:
	CJNE A,#11,MNOZ; SPRAWDZ CZY ODEJMOWANIE
	LCALL LCD_CLR
	MOV A, R1             ;wyświetlanie liczb i znaku operacji oraz znaku =, znaki za pomocą LCALL WRITE_DATA
	LCALL WRITE_HEX
	MOV A, #'-'
	LCALL WRITE_DATA
	MOV A,R2
	LCALL WRITE_HEX
	MOV A, #'='
	LCALL WRITE_DATA
	POP 32H
	POP 31H
	MOV A, 31H  ;przeniesienie pierwszej liczby do akumulatra
	CLR C ;czyszczenie flagi
	SUBB A, 32H  ;dodanie drugiej
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_KEY
	LJMP START

MNOZ:
	CJNE A,#12,DZIEL; SPRAWDZ CZY MNOZENIE
	; WYKONAJ MNOŻENIE
	LCALL LCD_CLR
	MOV A, R1
	LCALL WRITE_HEX
	MOV A, #'*'
	LCALL WRITE_DATA
	MOV A,R2
	LCALL WRITE_HEX
	MOV A, #'='
	LCALL WRITE_DATA
	POP 32H
	POP 31H
	MOV A,31H
	MOV B,32H
	MUL AB  ;mnozenie
	MOV R3,A  ;A - wyższe bity bardziej znaczące
	MOV R4,B  ;B- niższe mniej znaczće
	MOV A,R4  ;najpierw wyśiwetlamy niższe
	LCALL WRITE_HEX
	MOV A,R3   ;potem wyższe
	LCALL WRITE_HEX
	LCALL WAIT_KEY
	LJMP START

DZIEL:  ;błąd
	CJNE A,#13,TO_START; SPRAWDZ CZY DZIELNEIE
	; WYKONAJ DZIELENIE I ZAPISZ WYNIK
 	LCALL LCD_CLR
 	MOV A, R1
 	LCALL WRITE_HEX
 	MOV A, #'/'
 	LCALL WRITE_DATA
 	MOV A,R2
 	LCALL WRITE_HEX
 	MOV A, #'='
 	LCALL WRITE_DATA
	POP 32H
	POP 31H
	MOV A,31H
	MOV B,32H
	DIV AB		;w A całośći, a w B reszta z dzielenai (format wyśiwtlania np. 20/6 = 3_2/6)
	MOV R3,A
	MOV R4,B
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#'_' ; JEST DZIELENIE
	LCALL WRITE_DATA
	MOV A,R4
	LCALL TO_BCD
	LCALL WRITE_HEX
	MOV A,#'/' ; JEST DZIELENIE
	LCALL WRITE_DATA
	MOV A,R2
	LCALL TO_BCD
	LCALL WRITE_HEX
	LCALL WAIT_KEY
	LJMP START



STOP:			;nie wykonuj innych dzia�a�
	LJMP	STOP	;- pozosta� w p�tli STOP
	NOP
TO_START:
	LJMP START
TO_BCD:
	;ZAMIANA NA BCD -POCZ�TEK
	MOV B,#10; DZIELNIK
	DIV AB; WYDZIELAMY CYFRE DZIESIATEK
	SWAP	A
	ORL A,B; DODAJEMY CYFR� JEDNO�CI
	;ZAMIANA NA BCD -KONIEC
	RET
	NOP
