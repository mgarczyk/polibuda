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
call RED_LIGHT
call YELLOW_LIGHT
call GREEN_LIGHT
jmp MAIN
; podprogramy
.org 0x0100

RED_LIGHT:
cbi PORTB, 0
call DELAY_3s
sbi PORTB, 0
ret

YELLOW_LIGHT:
cbi PORTB, 1
call DELAY_3s
sbi PORTB, 1
ret

GREEN_LIGHT:
cbi PORTB, 2
call DELAY_3s
sbi PORTB, 2
ret

DELAY_3s:
NOP
NOP
ldi R22, 63
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

;podprogram 0.5s opóŸnienia
DELAY_05s:
ldi r16, 95
ldi r17, 38
ldi r18, 11
LOOP_COUNT2:
dec r16
brne LOOP_COUNT2
dec r17
brne LOOP_COUNT2
dec r18
brne LOOP_COUNT2
ret
