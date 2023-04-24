// ----------------------------
// sterowanie swiatlami
//-----------------------------
.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
rjmp START
;wektory przerwan
.org 0x0030
START:
;ustawienie stosu
ldi r16, low(RAMEND)
out SPL, r16
ldi r16, high(RAMEND)
out SPH, r16
; ustawienie linii I/O
ldi r16, 0b11111111
out DDRB, r16
MAIN:
;zezwolenie na jazde w pionie, brak zezwolenia w poziomie
ldi r16, 0b10011001
out PORTB, r16
call DELAY
call DELAY
call DELAY
call DELAY
call DELAY
;zezwolenie na jazde w poziomie, brak zezwolenia w pionie
ldi r16, 0b01100110
out PORTB, r16
call DELAY
call DELAY
call DELAY
call DELAY
call DELAY
jmp MAIN

DELAY:
NOP
NOP
ldi R22, 21
ldi R23, 75
ldi R24, 188
OP_1s:
dec R24
brne op_1s
dec R23
brne op_1s
dec R22
brne op_1s
ret
