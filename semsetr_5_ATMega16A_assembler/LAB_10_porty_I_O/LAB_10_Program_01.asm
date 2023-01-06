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
in r16, PINA
out PORTB, r16
jmp MAIN
