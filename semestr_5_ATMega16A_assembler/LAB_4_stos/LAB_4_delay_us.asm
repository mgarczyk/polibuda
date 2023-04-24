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


call LOAD_us
JMP PC

LOAD_us:
ldi R18,130
OP_100us:
dec R18
brne op_100us
NOP
NOP
ret
