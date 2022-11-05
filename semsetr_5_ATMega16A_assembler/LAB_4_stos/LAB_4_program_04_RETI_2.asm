// ~ poprzednia cz�� programu
.nolist // podprogram
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START ;skok do etykiety 
;START (adres 0x0030)
// wektory przerwa�
.org 0x0030
START:
//Adresy bezwzgl�dne
//ldi r16, 0x5F
//out SPL, r16
//ldi r17, 0x04
//out SPH, r17
//Bardziej ludzko to samo - nazwami
ldi r16, LOW(RAMEND) // dolne 8 bit�w adresu RAMEND - 0x045F (5F)
out SPL, r16 //przypisanie dolnej cz�sci RAMEND do dolnego wska�nika stosu (SPL)
ldi r17, HIGH(RAMEND) // g�rne 8 bit�w (04)
out SPH, r17 //przypisanie dolnej cz�sci RAMEND do g�rnego wska�nika stosu (SPH)
jmp PC




// ~ dalsza cz�� programu
