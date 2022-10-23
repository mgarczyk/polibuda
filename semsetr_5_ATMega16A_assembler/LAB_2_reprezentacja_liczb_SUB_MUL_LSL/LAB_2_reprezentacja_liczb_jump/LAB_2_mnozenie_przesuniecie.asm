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
// Mno¿enie przez 5 wykorzystuj¹c przesuniêce bitowe (logiczne) w lewo.
//Wiemy ¿e << przesuniêcie bitowe w lewo (LSL) o jedn¹ pozycjê 
//jest równoznczne z mno¿eniem danej wartoœci przez 2.
//Zatem mno¿enie liczby a x 5 mo¿na opisaæ jako mno¿enie a x 4 + a,
//czyli 2 przesuniêcia w lewo i jedno dodanie mno¿nej. 
ldi r16, 5
mov r17, r16
lsl r16
lsl r16
add r16, r17 // po odjêciu mamy wynik
jmp PC
