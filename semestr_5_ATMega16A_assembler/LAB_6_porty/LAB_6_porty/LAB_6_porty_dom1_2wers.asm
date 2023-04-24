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
ldi R23, 8
MASKAL:
rol r16
out PORTB, r16
;call DELAY_1s
dec R23
breq MAIN2
JMP MASKAL
MAIN2:
ldi R22, 8
MASKAR:
ror r16
out PORTB, r16
;call DELAY_1s
dec R22
breq MAIN
JMP MASKAR


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



