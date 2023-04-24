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
ldi r16, 10
ldi r17, 20
call DODAJ
ldi r16, 50
ldi r17, 60
call DODAJ //nie wraca w dobre miejsce ze wzgl�du na brak inicjalizacji wska�nika stosu, stos ustawia sie domy�lne w 0xFFFF, a tam nic nie ma
jmp PC
//---koniec g��wnego programu---
// --- podprogram ---
.org 0x0100
DODAJ:
add r16, r17
sub r16, r17
mul r16, r17
ret
