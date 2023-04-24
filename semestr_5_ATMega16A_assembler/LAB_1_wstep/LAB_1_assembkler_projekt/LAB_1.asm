.nolist
.include "m16def.inc" // file with mnemonic names like RAMEND = 0x045F
.list
.listmac
.device ATmega16 // microprocessor name
.cseg
.org 0x0000 // starting address
// Commands below are executed in one clock cycle.
ldi R16, 255 //Store value 255 in register R16.
ldi R17, 1 //Store value 1 in register R17
add R16, R17 //Add values in registers R16 and R17. The result will be store in the register on the left side (R16)
//Jmp is execute in two cycles - this command informs us that the program has ended.
jmp PC

