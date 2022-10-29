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
clr r18
clr r19
ldi r16, 100
ldi r17, 200
add r16, r17 // 8 bitów 255 maks, 200 + 100 = 300, i w R16 jest zapsane 300 - 256 = 44 (od wyniku odejmujemy)
adc r18, r19 //do rejsetru R18 zapisujemy wartoœæ bitu przenieniesienia (C)
//flaga C carry, 'gaœnie' po u¿yciu instrunkcji ADC
jmp PC
