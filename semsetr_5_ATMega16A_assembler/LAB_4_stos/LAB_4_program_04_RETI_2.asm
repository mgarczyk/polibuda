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
//Adresy bezwzglêdne
//ldi r16, 0x5F
//out SPL, r16
//ldi r17, 0x04
//out SPH, r17
//Bardziej ludzko to samo - nazwami
ldi r16, LOW(RAMEND) // dolne 8 bitów adresu RAMEND - 0x045F (5F)
out SPL, r16 //przypisanie dolnej czêsci RAMEND do dolnego wskaŸnika stosu (SPL)
ldi r17, HIGH(RAMEND) // górne 8 bitów (04)
out SPH, r17 //przypisanie dolnej czêsci RAMEND do górnego wskaŸnika stosu (SPH)
jmp PC




// ~ dalsza czêœæ programu
