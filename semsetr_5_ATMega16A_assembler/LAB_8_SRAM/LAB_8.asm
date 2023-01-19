.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16

.cseg
.org 0x0000
jmp START

.org 0x0030
START:

MAIN:
ldi r16, 0b11111111
out DDRB, r16


ldi r30, low(0x0060) ;wskaünik Z
ldi r31, high(0x0060)
ldi r16,85
ldi r17,255
ldi r25,0b01111111
ldi r26,0b11111110
 
SRAM_loop:
st Z+, r16
ld R19, Z
cpc R16,R19
brcs PRAWA
out PORTB, R25
call delay_1s
JMP ET
PRAWA:
out PORTB, R26
call delay_1s
ET:
dec r17
brne SRAM_loop
nop




SRAM_loop1:
st Z+, r16
ld R19, Z
Inc R19
cpc R16,R19
brcs PRAWA1
out PORTB, R25
call delay_1s
JMP ET1
PRAWA1:
out PORTB, R26
call delay_1s
ET1:
dec r17
brne SRAM_loop1
nop



DELAY_1s:
NOP
NOP
ldi R22, 2
;ldi R23, 75
;ldi R24, 188
OP_1s:
;dec R24
;brne op_1s
;dec R23
;brne op_1s
dec R22
brne op_1s
ret

jmp MAIN
