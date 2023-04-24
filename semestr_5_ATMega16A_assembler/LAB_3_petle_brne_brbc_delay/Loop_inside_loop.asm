//Loop inside another loop.
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
ldi r16, 255
ldi r17, 5
Loop_Count:
dec r16
brne Loop_Count
dec r17
brne Loop_Count
nop
jmp PC
