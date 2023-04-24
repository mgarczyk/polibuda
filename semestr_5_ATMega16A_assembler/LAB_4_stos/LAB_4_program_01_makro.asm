.nolist // makro
.include "m16def.inc"
.list
.listmac
.device ATmega16
.macro DODAWANIE
add r16, r17
add R16, R17
.endmacro
.cseg
.org 0x0000
jmp START ;skok do etykiety 
;START (adres 0x0030)
// wektory przerwañ
.org 0x0030
START:
ldi r16, 10
ldi r17, 20
DODAWANIE
ldi r16, 30
ldi r17, 40
DODAWANIE
jmp PC
