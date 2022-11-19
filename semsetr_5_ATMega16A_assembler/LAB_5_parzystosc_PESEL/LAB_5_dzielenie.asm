// ~ nag³ówek (dyrektywy)
.nolist // komentarz
.include "m16def.inc" ; komentarz
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
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
MAIN:
ldi R31,1
ldi R30,1

call DZIELENIE
jmp PC
// podprogram dzielenia
.org 0x0100
DZIELENIE:
ldi r29, 255
LICZ_DALEJ:
inc r29 ;r29 -> wynik dzielenia
sbiw r31:r30, 8  /// zmiana 8 na dowolna wartosc z przedzialu 1;63
brpl LICZ_DALEJ
adiw r31:r30, 8 ;r30 -> reszta
ret
