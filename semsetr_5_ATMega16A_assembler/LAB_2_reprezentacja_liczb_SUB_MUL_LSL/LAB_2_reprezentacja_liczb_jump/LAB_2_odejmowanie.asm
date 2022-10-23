.nolist // komentarz
.include "m16def.inc" ; komentarz
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp 0x0030 ;skok do adresu 0x0030
// wektory przerwañ
.org 0x0030
// odejmowanie
ldi r16, 20
ldi r17, 101
sub r16, r17 //w konwencji u2 - liczby ujemne jako negacja liczby +1 (wynik 
// odejmowania jest zapisywany jako suma 20 i negacji 101 -> 256 - 101 = 155
//Je¿eli w wyniku otrzymamy 0 to zapali siê flaga Z.
nop
jmp PC
