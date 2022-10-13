.nolist
.include "m16def.inc" // file with mnemonic names of type RAMEND = 0x045F
.list
.listmac
.device ATmega16 // microprocessor name
.cseg
.org 0x0000 // starting address
//The development environment zeros all memory cells, 
//in reality there are 0xFFFF (only ones) before.
ldi R16, 255
ldi R17, 1
add R16, R17 //the result is written to the register on the left
// the above commands are executed in one clock beat (one 16bit memory cell)
jmp PC
//jmp occupies 2 cells - this command informs us that the program has ended.
E1 :nop
nop
jmp E1

//W mapie pamiêci (Pierwsza pzycja nazwa rozkazu, 2 i 4 pozycja oœmio bitowo (2 pierwsze 4 bity, 4 drugie bity), 3 pozycja numer rejestru.
