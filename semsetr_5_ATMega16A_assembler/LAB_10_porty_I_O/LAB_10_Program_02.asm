// ------------------------------
// wykrycie kombinacji przycisków
//-------------------------------
// ....

// ----------------------------
// test port�w in-out
//-----------------------------
.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
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
; ustawienie portu B jako wyj�cia
ldi r16, 0b11111111
out DDRB, r16
; ustawienie portu A jako wej�cia
ldi r16, 0b00000000
out DDRA, r16
ldi R16, 0b11111111
out PORTA, R16
MAIN:
in r16, PINA
cpi r16, 0b01111110 ;nstrukcja CPI porównuje zawartość rejestru ze stałą i ustawia znacznik Z=1 (gdy równe)
breq WZOR1 ;BREQ sprawdza znacznik Z, jeżeli Z=1 skacze do etykiety, w przeciwnym razie  przechodzi dalej do kolejnej instrukcji
cpi r16, 0b11100111
breq WZOR2
ldi r18, 0b11111111 ;jeżeli WZOR1 i WZOR2 nie są wybrane wyświetlana jest ta wartość
out PORTB, r18
jmp MAIN
WZOR1: ; gdy wybrany WZOR1
ldi r18, 0b11110000 ;zapala 4 młodsze diody
out PORTB, r18
jmp MAIN
WZOR2: ;gdy wybrany WZOR2
ldi r18, 0b00001111 ;zapala 4 starsze diody LED
out PORTB, r18
jmp MAIN





