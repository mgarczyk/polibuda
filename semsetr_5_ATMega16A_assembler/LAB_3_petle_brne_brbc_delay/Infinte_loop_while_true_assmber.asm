.nolist // komentarz - While (true){} implementation. Infinite loop.
.include "m16def.inc" ; komentarz
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START 
.org 0x0030
START:
Loop_Count: ldi r16, 10
dec r16
brne Loop_Count
nop
jmp PC
