// ----------------------------
// klawiatura 4x4
//-----------------------------
.nolist ; komentarz
.include "m16def.inc"
.list
.listmac
.device ATmega16
// definicja stałych
.equ c_0 = 0b11000000
.equ c_1 = 0b11111001
.equ c_2 = 0b10100100
.equ c_3 = 0b10110000
.equ c_4 = 0b10011001
.equ c_5 = 0b10010010
.equ c_6 = 0b10000010
.equ c_7 = 0b11111000
.equ c_8 = 0b10000000
.equ c_9 = 0b10010000
.equ c_A = 0b10001000
.equ c_B = 0b10000011
.equ c_C = 0b11000110
.equ c_D = 0b10100001
.equ c_E = 0b10000110
.equ c_F = 0b10001110
.cseg
.org 0x0000
jmp 0x0030
;wektory przerwań
.org 0x0030
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
; ustawienie portu A 7-4
; wejścia, 3-0 wyjścia
ldi r16, 0b00001111
out DDRA, r16
; ustawienie portu B
ldi r16, 0b11111111
out DDRB, r16
out PORTB, r16 ;wygaszenie
;wszystkich segmentów
MAIN:
//WIERSZ 1
ldi r16, 0b11111110
out PORTA, r16
call JAKI_PRZYCISK
//WIERSZ 2
ldi r16, 0b11111101
out PORTA, r16
call JAKI_PRZYCISK
//WIERSZ 3
ldi r16, 0b11111011
out PORTA, r16
call JAKI_PRZYCISK
// WIERSZ 4
ldi r16, 0b11110111
out PORTA, r16
call JAKI_PRZYCISK
jmp MAIN
.org 0x0100
JAKI_PRZYCISK:
in r17, PINA
;spr. przycisków wiersza 1
cpi r17, 0b11101110
breq KEY_0 ;TAK
;NIE
cpi r17, 0b11011110
breq KEY_1 ;TAK
;NIE
cpi r17, 0b10111110
breq KEY_2 ;TAK
;NIE
cpi r17, 0b01111110
breq KEY_3 ;TAK
;NIE
;spr. przycisków wiersza 2
cpi r17, 0b11101101
breq KEY_4 ;TAK
;NIE
cpi r17, 0b11011101
breq KEY_5 ;TAK
;NIE
cpi r17, 0b10111101
breq KEY_6 ;TAK
;NIE
cpi r17, 0b01111101
breq KEY_7 ;TAK
;NIE
;spr. przycisków wiersza 3
cpi r17, 0b11101011
breq KEY_8 ;TAK
;NIE
cpi r17, 0b11011011
breq KEY_9 ;TAK
;NIE
cpi r17, 0b10111011
breq KEY_A ;TAK
;NIE
cpi r17, 0b01111011
breq KEY_B ;TAK
;NIE
;spr. przycisków wiersza 4
cpi r17, 0b11100111
breq KEY_C ;TAK
;NIE
cpi r17, 0b11010111
breq KEY_D ;TAK
;NIE
cpi r17, 0b10110111
breq KEY_E ;TAK
;NIE
cpi r17, 0b01110111
breq KEY_F ;TAK
;NIE
ldi r16, 0b11111111
out PORTB, r16 ;wygaszenie wszystkich segmentów
ret
KEY_0:
ldi r16, c_0
out PORTB, r16
ret
KEY_1:
ldi r16, c_1
out PORTB, r16
ret
KEY_2:
ldi r16, c_2
out PORTB, r16
ret
KEY_3:
ldi r16, c_3
out PORTB, r16
ret
KEY_4:
ldi r16, c_4
out PORTB, r16
ret
KEY_5:
ldi r16, c_5
out PORTB, r16
ret
KEY_6:
ldi r16, c_6
out PORTB, r16
ret
KEY_7:
ldi r16, c_7
out PORTB, r16
ret
KEY_8:
ldi r16, c_8
out PORTB, r16
ret
KEY_9:
ldi r16, c_9
out PORTB, r16
ret
KEY_A:
ldi r16, c_A
out PORTB, r16
ret
KEY_B:
ldi r16, c_B
out PORTB, r16
ret
KEY_C:
ldi r16, c_C
out PORTB, r16
ret
KEY_D:
ldi r16, c_D
out PORTB, r16
ret
KEY_E:
ldi r16, c_E
out PORTB, r16
ret
KEY_F:
ldi r16, c_F
out PORTB, r16
ret
