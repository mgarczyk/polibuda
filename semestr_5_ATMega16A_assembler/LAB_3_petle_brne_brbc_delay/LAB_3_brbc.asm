.nolist // komentarz - For loop implementation in AVR assembler for(int i=10; i>=0; i--)
.include "m16def.inc" ; komentarz
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START
.org 0x0030
START:
ldi r16, 10
Loop_Count: 
dec r16
brbc 1, Loop_Count
nop
jmp PC
