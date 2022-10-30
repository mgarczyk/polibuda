//Program that implements one second delay.
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
ldi R16, 127
ldi R17, 127
add R16, R17
ldi r16, 255
ldi r17, 255
ldi R18, 255
Loop_Count:
dec r16
brne Loop_Count
dec r17
brne Loop_Count
dec R18
brne Loop_Count
nop
jmp PC
