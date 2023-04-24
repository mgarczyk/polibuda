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
ldi r16, 9 ;a
ldi r17, 7 ;b
ldi r18, 0 ;c
ldi r19, 5 ;d
ldi r20, 2 ;e
ldi r21, 5 ;f
ldi r22, 1 ;g
ldi r23, 2 ;h
ldi r24, 3 ;i
ldi r25, 4 ;j
ldi r26, 3
ldi r27, 7
ldi r28, 9
ldi r30,0 ;wynik
ldi r31,0
mul r16, r28 ;a*9
add r30, r0
mul r17, r27 ;b*7
add r30, r0
adc r31, r1
mul r18, r26 ;c*3
add r30, r0
adc r31, r1
add r30, r19 ;d
adc r31, r1
mul r20, r28 ;e*9
add r30, r0
adc r31, r1
mul r21, r27 ;f*7
add r30, r0
adc r31, r1
mul r22, r26 ;g*3
add r30, r0
adc r31, r1
add r30, r23 ;h
adc r31, r1
mul r24, r28 ;i*9
add r30, r0
adc r31, r1
mul r25, r27 ;j*7
add r30, r0
adc r31, r1
call DZIELENIE
jmp PC
// podprogram dzielenia
.org 0x0100
DZIELENIE:
ldi r29, 255
LICZ_DALEJ:
inc r29 ;r29 -> wynik dzielenia
sbiw r31:r30, 10
brpl LICZ_DALEJ
adiw r31:r30, 10 ;r30 -> reszta
ret
