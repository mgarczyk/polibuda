.nolist
.include "m16def.inc"
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp START
;wektory przerwan
.org 0x0030
START:
;ustawienie stosu
ldi r16, high(RAMEND) ;0x04
out SPH, r16
ldi r16, low(RAMEND) ;0x5f
out SPL, r16
;ustawienie portu B jako wyjœcia
ldi r16, 0b11111111
out DDRB, r16



;Uwaga! Diody zapalamy zerem
MAIN:
ldi R17, 0b11100111 ;bazowe pocz¹tkowe ustawienie diód (2 - poœrodku)
out PORTB, R17 ;zapalenie ich
call delay_1s  ;utrzymanie przez sekunde
;liczniki pêtli
ldi R19,3
ldi R21,4  

;rozszerzanie do zewn¹trz
ROZSZ:
ldi R20,0b11111111 ;dodatkowy rejestr, s³i¿¹cy do utrzymania prawid³owej wartoœæi C
MOV R18, R17 	    ;kopia rejstru (wykonamy 2 operacje ROL i ROR - potrzebujemy kopiê)
ROL R20 ;ustawienie flagi cary na 1 przez przesuwanie odzielnego rejestru dla prawidlowego dzialania ROL R17 ;rozsuwanie w celu zapalania zewnêtrznych diód
ROL R17 ;przesuwamy w lewo, z prawej wsuwamy C=1 by nie zapalaæ niechcianych diód, wysuwamy 1 do carry
ROR R18 ;dalej przessuwamy w prawo, wsuwaj¹c jedynkê z carry.
AND R17,R18 ; 11000011 ;operacja AND na R17 i R18 pozwala uzyskaæ prawid³ow¹ wartoœæ maski, zapalaj¹cej diody któe chcemy
out PORTB, R17 ;zapalamy
call DELAY_1s ;trzymamy
dec R19 ;zmniejszamy  licznik
brne ROZSZ ;albo powtarzamy gdy Z!=0, albo zaczynamy zwê¿aæ

;zwê¿anie do œrodka
ZWEZ:
ldi R20,0b11111111 ;w carry potrzebujemy 1, ¿eby wy³¹czaæ diody
ROR R20 ;C=1 uzysujemy poprzez przesuwanie oœmiu jedynek
ROL R18 ;przesuwamy w lewo (wsuwamy jedynke z prawej),wysuwamy zero C=0
ROR R20 ;znowu ustawiamy C=1
ROR R17 ;przesuwamy w prawo (wsuwamy jedynke z lewej)
OR R17,R18 ;wykonujemy operacjê OR by maska zawiera³a prawid³owe wartoœci
out PORTB,R17
call delay_1s
dec R21
brne ZWEZ
JMP MAIN ;powrót na pocz¹tek




;opóŸnienie 1s
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



