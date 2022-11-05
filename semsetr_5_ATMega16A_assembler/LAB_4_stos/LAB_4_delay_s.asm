// ~ poprzednia czêœæ programu
.nolist // podprogram
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START ;skok do etykiety 
;START (adres 0x0030)
// wektory przerwañ
.org 0x0030
START:
ldi r16, LOW(RAMEND) 
out SPL, r16 
ldi r17, HIGH(RAMEND) 
out SPH, r17 


call LOAD_s
JMP PC

LOAD_s:
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
