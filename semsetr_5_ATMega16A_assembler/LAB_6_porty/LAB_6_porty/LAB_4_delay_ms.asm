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


call LOAD_ms
JMP PC

LOAD_ms:
NOP
ldi R18,6
ldi R19, 46
OP_1ms:
dec R19
brne op_1ms
dec R18
brne op_1ms
ret
