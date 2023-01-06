// ------------------------------
// Numer przycisku
//-------------------------------
// ....

// ----------------------------
// test portów in-out
//-----------------------------
.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START
;wektory przerwań
.org 0x0030
START:
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
; ustawienie portu B jako wyjścia
ldi r16, 0b11111111
out DDRB, r16
; ustawienie portu A jako wejścia
ldi r16, 0b00000000
out DDRA, r16
ldi R16, 0b11111111
out PORTA, R16
MAIN:
ldi r18, 0b11111111 ;wstępnie do r18 wpisany wzór wygaszający wszystkie diody
sbis PINA, 0 ;testowany bit 0 w rejestrze PINA
ldi r18, 0b11111110
sbis PINA, 1 ;testowany bit 1 w rejestrze PINA
ldi r18, 0b11111100
sbis PINA, 2 ;instrukcja SBIS estuje wybrany bit. Jeżeli warunek jest spełniony (wykryto "1") pomija kolejną instrukcję, jeżeli
;warunek nie jestspełniony (wykryto"0") nie pomijakolejnej instrukcji.
sbis PINA, 3
ldi r18, 0b11110000
sbis PINA, 4
ldi r18, 0b11100000
sbis PINA, 5
ldi r18, 0b11000000
sbis PINA, 6
ldi r18, 0b10000000
sbis PINA, 7
ldi r18, 0b00000000
out PORTB, r18 ;"zapalenie" diod LED kombinacją zapisaną w r18
jmp MAIN







