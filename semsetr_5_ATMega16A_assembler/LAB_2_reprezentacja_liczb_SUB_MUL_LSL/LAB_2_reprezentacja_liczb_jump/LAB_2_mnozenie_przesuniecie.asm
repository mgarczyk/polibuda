.nolist // komentarz
.include "m16def.inc" ; komentarz
.list
.listmac
.device ATmega16
.cseg
.org 0x0000
jmp 0x0030 ;skok do adresu 0x0030
// wektory przerwa�
.org 0x0030
// Mno�enie przez 5 wykorzystuj�c przesuni�ce bitowe (logiczne) w lewo.
//Wiemy �e << przesuni�cie bitowe w lewo (LSL) o jedn� pozycj� 
//jest r�wnoznczne z mno�eniem danej warto�ci przez 2.
//Zatem mno�enie liczby a x 5 mo�na opisa� jako mno�enie a x 4 + a,
//czyli 2 przesuni�cia w lewo i jedno dodanie mno�nej. 
ldi r16, 5
mov r17, r16
lsl r16
lsl r16
add r16, r17 // po odj�ciu mamy wynik
jmp PC
