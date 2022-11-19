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
ldi r16, 0b10011011
ldi r20, 0 ;wynik sumowania
ldi r21, 9 ;licznik bitów
DALEJ:
dec r21
breq KONIEC
ror r16
brcc DALEJ ;jest 0
;jest 1
inc r20 ;dodaj 1 do r20
jmp DALEJ
KONIEC:
jmp PC
