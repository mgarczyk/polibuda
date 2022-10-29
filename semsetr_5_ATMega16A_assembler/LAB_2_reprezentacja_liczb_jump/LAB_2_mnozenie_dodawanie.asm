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
//Wykonamy mno¿enie (x 5) przez dodawanie  (np. 4*5 = 4+4+4+4+4), zatem je¿eli n to mno¿nik. to potrzebujemy n-1 operacji dodawania, 
//by wykonaæ zadane mno¿enie. Czyli u nas 4 operacje dodwania.
ldi r16, 5 //do rejestru r16 przypisujemy mno¿n¹
mov r17, r16 //kopia mno¿nej, wykorzystywana w mechanizmie mno¿enia przez dodawanie
add r16, r17 //dodajemy pierwszy raz i potem jeszcze n-2 razy
add r16, r17
add r16, r17
add r16, r17 //w tym momencie wynik mno¿enia przez 4 jest w naszym rejestrze R16
jmp PC
