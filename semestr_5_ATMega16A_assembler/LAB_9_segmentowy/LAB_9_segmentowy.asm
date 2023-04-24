.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
;poni�ej opisane symbole - segment zapalamy '1' - stanem wysokim
.equ c_0=0b11111100
.equ c_1=0b01100000
.equ c_2=0b11011010
.equ c_3=0b11110010
.equ c_4=0b01100110
.equ c_5=0b10110110
.equ c_6=0b10111110
.equ c_7=0b11100000
.equ c_8=0b11111110
.equ c_9=0b11110110
.equ c_A=0b11101110
.equ c_B=0b00111110
.equ c_C=0b10011100
.equ c_D=0b01111010
.equ c_E=0b10011110
.equ c_F=0b10001110
.equ c_H=0b01101110
.equ c_L=0b00011100
.equ c_P=0b11001110
.org 0x0000
jmp START
;wektory przerwa�
.org 0x0030
START:
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
;ustawienie portu B jako wyj�cia
ldi r16, 0b11111111 ;do resetru R16 wpisujmy same '1'
out DDRB, r16 ;za pomoc� tego rejsetru ustawiamy port B jako wyj�cie

MAIN:
ldi r17, c_0   ;zapisujemy w rejestrze R17 warto�� kt�r� chcemy wy�wietli�
out portB, r17 ;wysy�amy warto�� z rejstru R17 na port B, wy�wietlamy j� na wy�wietlaczu ('0') 
call delay_1s  ;sekunda op�nienia, �eby zobaczy� wynik
;dalej wykonujemy to samo dla wsztrkich pozosta�ych warto�ci z sekwencjii
ldi r17, c_1 
out portB,r17
call delay_1s
ldi r17, c_2
out portB,r17
call delay_1s
ldi r17, c_3
out portB,r17
call delay_1s
ldi r17, c_4
out portB,r17
call delay_1s
ldi r17, c_5
out portB,r17
call delay_1s
ldi r17, c_6
out portB,r17
call delay_1s
ldi r17, c_7
out portB,r17
call delay_1s
ldi r17, c_8
out portB,r17
call delay_1s
ldi r17, c_9
out portB,r17
call delay_1s
ldi r17, c_A
out portB,r17
call delay_1s
ldi r17, c_B
out portB,r17
call delay_1s
ldi r17, c_C
out portB,r17
call delay_1s
ldi r17, c_D
out portB,r17
call delay_1s
ldi r17, c_E
out portB,r17
call delay_1s
ldi r17, c_F
out portB,r17
call delay_1s
ldi r17, c_H
out portB,r17
call delay_1s
ldi r17, c_L
out portB,r17
call delay_1s
ldi r17, c_P
out portB,r17
call delay_1s
jmp MAIN ;wracamy do etykiety MAIN i powtarzamy sekwencj�

;op�nienie 1 sekunda
DELAY_1s:
NOP
NOP
ldi R22, 21
ldi R23, 75
ldi R24, 188
OP_1s:
dec R24
brne op_1s
dec R23
brne op_1s
dec R22
brne op_1s
ret

