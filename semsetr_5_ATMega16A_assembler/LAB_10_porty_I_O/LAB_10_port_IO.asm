.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
;stale programowe do wyswietlania znak�w na wy�wietlaacz
.equ c_0=0b11111100
.equ c_1=0b01100000
.equ c_2=0b11011010
.equ c_3=0b11110010
.equ c_4=0b01100110
.equ c_5=0b10110110
.equ c_6=0b10111110
.equ c_7=0b11100000
.equ c_8=0b11111110
jmp START
;wektory przerwan
.org 0x0030
START:
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
; ustawienie portu B jako wyj�cia
ldi r16, 0b11111111
out DDRB, r16
; ustawienie portu A jako wej�cia
ldi r16, 0b00000000
; inicjalizacja rezystor�w PULL_UP
out DDRA, r16
ldi R16, 0b11111111
out PORTA, R16
;Pętla główna - sprawdzamy pin po pinie, aż trafiamy na pin na którym jest 0, przycisk wciśnięty
;Wtedy do R16 wpsiujemy numer tego pinu i wysy�amy go na PORTB (na wy�wietlacz)
MAIN:
SBIS PINA,0;sprawdzamy czy PINA jest ustawiony (1)
ldi R16, c_0;je�eli tak pomijamy nast�pn� instrukcj�, 
;dopiero gdy trafimy na PIN nieustawiony (0) do R16 zaostanie przypisany jego numer
SBIS PINA,1
ldi R16, c_1
SBIS PINA,2
ldi R16, c_2
SBIS PINA,3
ldi R16, c_3
SBIS PINA,4
ldi R16, c_4
SBIS PINA,5
ldi R16, c_5
SBIS PINA,6
ldi R16, c_6
SBIS PINA,7
ldi R16, c_7
out PORTB, r16
call delay_1s
jmp MAIN;powtarzamy 


;op�nienie
delay_1s:
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
