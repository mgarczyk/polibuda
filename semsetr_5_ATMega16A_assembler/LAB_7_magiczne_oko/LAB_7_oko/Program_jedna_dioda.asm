.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START
;wektory przerwañ
.org 0x0030
START:
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
;ustawienie portu B jako wyjœcia
ldi r16, 0b11111111
out DDRB, r16
MAIN:
ldi r16, 0b00000000
out PORTB, r16
;CALL DELAY_1s
ldi r16, 0b11111111
out PORTB, r16
;CALL DELAY_1s
jmp MAIN


DELAY_1s:
NOP
NOP
ldi R18, 21
ldi R19, 75
ldi R20, 188
OP_1s:
dec R20
brne op_1s
dec R19
brne op_1s
dec R18
brne op_1s
ret


